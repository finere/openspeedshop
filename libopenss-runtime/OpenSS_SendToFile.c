/*******************************************************************************
** Copyright (c) 2008 William Hachfeld. All Rights Reserved.
** Copyright (c) 2009 The Krell Institute. All Rights Reserved.
**
** This library is free software; you can redistribute it and/or modify it under
** the terms of the GNU Lesser General Public License as published by the Free
** Software Foundation; either version 2.1 of the License, or (at your option)
** any later version.
**
** This library is distributed in the hope that it will be useful, but WITHOUT
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
** details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this library; if not, write to the Free Software Foundation, Inc.,
** 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*******************************************************************************/

/** @file
 *
 * Definition of the OpenSS_SetSendToFile() and OpenSS_SendToFile() functions.
 *
 */

#include "Assert.h"
#include "RuntimeAPI.h"

#include <dlfcn.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>



/** Type defining the items stored in thread-local storage. */
typedef struct {

    /** Path of the file to which data should be written. **/
    char path[PATH_MAX];

} TLS;

#ifdef USE_EXPLICIT_TLS

/**
 * Thread-local storage key.
 *
 * Key used for looking up our thread-local storage. This key <em>must</em>
 * be globally unique across the entire Open|SpeedShop code base.
 */
static const uint32_t TLSKey = 0xFEEDBEEF;

#else

/** Thread-local storage. */
static __thread TLS the_tls;

#endif



/**
 * Set the "send-to" file.
 *
 * Set the name of the file to which subsequent OpenSS_SendToFile() calls will
 * write their data. The name is not specified directly. It is derived from the
 * unique identifier of the collector writing the data, the identifier of the
 * process/thread making the call, the process' executable name, and a suffix
 * provided by the caller. Insures that the specified file exists.
 *
 * @param unique_id    Unique identifier of the collector writing data.
 * @param suffix       File suffix to be used.
 *
 * @ingroup RuntimeAPI
 */
void OpenSS_SetSendToFile(OpenSS_DataHeader* header,
			  const char* unique_id, const char* suffix)
{
    const char* executable_path = NULL;
    char* openss_rawdata_dir = NULL;
    char dir_path[PATH_MAX];
    int fd;

    /* Access our thread-local storage */
#ifdef USE_EXPLICIT_TLS
    TLS* tls = malloc(sizeof(TLS));
    Assert(tls != NULL);
    OpenSS_SetTLS(TLSKey, tls);
#else
    TLS* tls = &the_tls;
#endif
    Assert(tls != NULL);
    
    /* Check preconditions */
    Assert(unique_id != NULL);
    Assert(suffix != NULL);

    /* Get our executable path */
    executable_path = OpenSS_GetExecutablePath();
    
    /* Create the directory path containing the file and the file itself */
    /* We need to add the hostname to the directory path and not just the pid.
     * e.g. openss-rawdata-host-pid rather than openss-rawdata-pid.
     * This is due to some mpi implementations allowing a pid to be the same
     * for multiple ranks as long as those ranks exist on different hosts.
     * Seen on hyperion with mvapich.
     */

    if ( (getenv("OPENSS_DEBUG_COLLECTOR") != NULL)) {
	fprintf(stderr,"OpenSS_SetSendToFile creating directory for raw data files, using header->host=%s, and header->pid\n", header->host, header->pid);
    }

    openss_rawdata_dir = getenv("OPENSS_RAWDATA_DIR");
    sprintf(dir_path, "%s/openss-rawdata-%s-%d",
	    (openss_rawdata_dir != NULL) ? openss_rawdata_dir : "/tmp",
	     header->host,header->pid);
    if(header->posix_tid == NULL) {
	sprintf(tls->path, "%s/%s-%d", dir_path, basename(executable_path), header->pid);
	sprintf(tls->path, "%s.%s", tls->path, suffix);
    } else {
	sprintf(tls->path, "%s/%s-%d-%llu", dir_path, basename(executable_path),
		header->pid,(uint64_t)header->posix_tid);
	sprintf(tls->path, "%s.%s", tls->path, suffix);
    }


    if ( (getenv("OPENSS_DEBUG_COLLECTOR") != NULL)) {
	fprintf(stderr,"OpenSS_SetSendToFile ready for %s\n",tls->path);
    }

    /* Insure the directory path to contain the file exists */
    struct stat st;
    if(stat(dir_path,&st) != 0) {
	mkdir(dir_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }

    //fprintf(stderr,"OpenSS_SetSendToFile assumes tls->path %s\n", tls->path);
    /* Insure the file itself exists */
    fd = open(tls->path, O_CREAT | O_APPEND,
	      S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    //fprintf(stderr,"OpenSS_SetSendToFile get FD %d\n", fd);
    if(fd >= 0)
	close(fd);
}



/**
 * Send performance data to a file.
 *
 * Sends performance data to the current "send-to" file previously specified by
 * OpenSS_SetSendToFile(). Any header generation and data encoding is performed
 * by the caller. Here the data is treated purely as a buffer of bytes to be
 * sent.
 *
 * @param size    Size of the data to be sent (in bytes).
 * @param data    Pointer to the data to be sent.
 * @return        Integer "1" if succeeded or "0" if failed.
 *
 * @ingroup RuntimeAPI
 */
int OpenSS_SendToFile(const unsigned size, const void* data)
{
    unsigned encoded_size;
    char buffer[8]; /* Large enough to encode one 32-bit unsigned integer */
    XDR xdrs;
    int fd;

    /* Access our thread-local storage */
#ifdef USE_EXPLICIT_TLS
    TLS* tls = OpenSS_GetTLS(TLSKey);
#else
    TLS* tls = &the_tls;
#endif
    Assert(tls != NULL);
    
    /* Create an XDR stream using the encoding buffer */
    xdrmem_create(&xdrs, buffer, sizeof(buffer), XDR_ENCODE);

    /* Encode the size of the data to be sent */
    Assert(xdr_u_int(&xdrs, (void*)&size) == TRUE);

    /* Get the encoded size */
    encoded_size = xdr_getpos(&xdrs);
    
    /* Close the XDR stream */
    xdr_destroy(&xdrs);

    /* Open the file for writing */
    Assert((fd = open(tls->path, O_WRONLY | O_APPEND)) >= 0);

    /* Write the size of the data to be sent */
    Assert(write(fd, buffer, encoded_size) == encoded_size);
    
    /* Write the data */
    Assert(write(fd, data, size) == size);

    /* Flush the data to disk. We could also test for fsyncdata
     * and use that as our fsync vi a #define.
     */
    Assert(fsync(fd) == 0);
    
    /* Close the file */
    Assert(close(fd) == 0);

    /* Indicate success to the caller */
    return 1;
}
