################################################################################
# Copyright (c) 2012 Argo Navis Technologies. All Rights Reserved.
# Copyright (c) 2012-2015 Krell Institute. All Rights Reserved.
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 59 Temple
# Place, Suite 330, Boston, MA  02111-1307  USA
################################################################################

include(FindPackageHandleStandardArgs)

set(CBTF_KRELL_INSTALLDIR ${CBTF_KRELL_DIR})
set(CBTF_TOOLS_XML ${CBTF_KRELL_DIR}/share/KrellInstitute/xml)

find_program(CBTF_TOOLS_CBTFRUN
    NAMES cbtfrun
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES bin
    )

find_library(CBTF_MESSAGES_COLLECTOR_SHARED_LIBRARY
    NAMES libcbtf-messages-collector.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

GET_FILENAME_COMPONENT(CBTF_KRELL_LIBDIR ${CBTF_MESSAGES_COLLECTOR_SHARED_LIBRARY} PATH )
set(CBTF_TOOLS_COLLECTORS ${CBTF_KRELL_LIBDIR}/KrellInstitute/Collectors)
set(CBTF_TOOLS_COMPONENTS ${CBTF_KRELL_LIBDIR}/KrellInstitute/Components)

mark_as_advanced(
    CBTF_KRELL_INSTALLDIR
    CBTF_TOOLS_XML
    CBTF_TOOLS_CBTFRUN
    CBTF_KRELL_LIBDIR
    CBTF_TOOLS_COLLECTORS
    CBTF_TOOLS_COMPONENTS
    )

find_library(CBTF_MESSAGES_BASE_SHARED_LIBRARY
    NAMES libcbtf-messages-base.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )
  
find_library(CBTF_MESSAGES_BASE_STATIC_LIBRARY
    NAMES libcbtf-messages-base-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )
  
find_library(CBTF_MESSAGES_COLLECTOR_STATIC_LIBRARY
    NAMES libcbtf-messages-collector-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )
  
find_library(CBTF_MESSAGES_EVENTS_SHARED_LIBRARY
    NAMES libcbtf-messages-events.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_MESSAGES_EVENTS_STATIC_LIBRARY
    NAMES libcbtf-messages-events-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_MESSAGES_INSTRUMENTATION_SHARED_LIBRARY
    NAMES libcbtf-messages-instrumentation.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_MESSAGES_INSTRUMENTATION_STATIC_LIBRARY
    NAMES libcbtf-messages-instrumentation-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_MESSAGES_PERFDATA_SHARED_LIBRARY
    NAMES libcbtf-messages-perfdata.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_MESSAGES_PERFDATA_STATIC_LIBRARY
    NAMES libcbtf-messages-perfdata-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_MESSAGES_SYMTAB_SHARED_LIBRARY
    NAMES libcbtf-messages-symtab.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_MESSAGES_SYMTAB_STATIC_LIBRARY
    NAMES libcbtf-messages-symtab-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_MESSAGES_THREAD_SHARED_LIBRARY
    NAMES libcbtf-messages-thread.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_MESSAGES_THREAD_STATIC_LIBRARY
    NAMES libcbtf-messages-thread-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_path(CBTF_MESSAGES_INCLUDE_DIR
    KrellInstitute/Messages/Address.h
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES include
    )

find_package_handle_standard_args(
    CBTF-Messages DEFAULT_MSG
    CBTF_MESSAGES_BASE_SHARED_LIBRARY
    CBTF_MESSAGES_BASE_STATIC_LIBRARY
    CBTF_MESSAGES_COLLECTOR_SHARED_LIBRARY
    CBTF_MESSAGES_COLLECTOR_STATIC_LIBRARY
    CBTF_MESSAGES_EVENTS_SHARED_LIBRARY
    CBTF_MESSAGES_EVENTS_STATIC_LIBRARY
    CBTF_MESSAGES_INSTRUMENTATION_SHARED_LIBRARY
    CBTF_MESSAGES_INSTRUMENTATION_STATIC_LIBRARY
    CBTF_MESSAGES_PERFDATA_SHARED_LIBRARY
    CBTF_MESSAGES_PERFDATA_STATIC_LIBRARY
    CBTF_MESSAGES_SYMTAB_SHARED_LIBRARY
    CBTF_MESSAGES_SYMTAB_STATIC_LIBRARY
    CBTF_MESSAGES_THREAD_SHARED_LIBRARY
    CBTF_MESSAGES_THREAD_STATIC_LIBRARY
    CBTF_MESSAGES_INCLUDE_DIR
    )

set(CBTF_MESSAGES_LIBRARIES
    ${CBTF_MESSAGES_BASE_SHARED_LIBRARY}
    ${CBTF_MESSAGES_COLLECTOR_SHARED_LIBRARY}
    ${CBTF_MESSAGES_EVENTS_SHARED_LIBRARY}
    ${CBTF_MESSAGES_INSTRUMENTATION_SHARED_LIBRARY}
    ${CBTF_MESSAGES_PERFDATA_SHARED_LIBRARY}
    ${CBTF_MESSAGES_SYMTAB_SHARED_LIBRARY}
    ${CBTF_MESSAGES_THREAD_SHARED_LIBRARY}
    )

set(CBTF_MESSAGES_PERFDATA_SHARED_LIBRARIES ${CBTF_MESSAGES_PERFDATA_SHARED_LIBRARY} )

set(CBTF_MESSAGES_INCLUDE_DIRS ${CBTF_MESSAGES_INCLUDE_DIR})

mark_as_advanced(
    CBTF_MESSAGES_BASE_SHARED_LIBRARY
    CBTF_MESSAGES_BASE_STATIC_LIBRARY
    CBTF_MESSAGES_COLLECTOR_SHARED_LIBRARY
    CBTF_MESSAGES_COLLECTOR_STATIC_LIBRARY
    CBTF_MESSAGES_EVENTS_SHARED_LIBRARY
    CBTF_MESSAGES_EVENTS_STATIC_LIBRARY
    CBTF_MESSAGES_INSTRUMENTATION_SHARED_LIBRARY
    CBTF_MESSAGES_INSTRUMENTATION_STATIC_LIBRARY
    CBTF_MESSAGES_PERFDATA_SHARED_LIBRARY
    CBTF_MESSAGES_PERFDATA_STATIC_LIBRARY
    CBTF_MESSAGES_SYMTAB_SHARED_LIBRARY
    CBTF_MESSAGES_SYMTAB_STATIC_LIBRARY
    CBTF_MESSAGES_THREAD_SHARED_LIBRARY
    CBTF_MESSAGES_THREAD_STATIC_LIBRARY
    CBTF_MESSAGES_INCLUDE_DIR
    )


find_library(CBTF_SERVICES_BINUTILS_SHARED_LIBRARY
    NAMES libcbtf-services-binutils.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_BINUTILS_STATIC_LIBRARY
    NAMES libcbtf-services-binutils-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_COLLECTOR_MONITOR_FILEIO_SHARED_LIBRARY
    NAMES libcbtf-services-collector-monitor-fileio.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_COLLECTOR_MONITOR_FILEIO_STATIC_LIBRARY
    NAMES libcbtf-services-collector-monitor-fileio-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_COLLECTOR_MONITOR_MRNET_SHARED_LIBRARY
    NAMES libcbtf-services-collector-monitor-mrnet.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_COLLECTOR_MONITOR_MRNET_STATIC_LIBRARY
    NAMES libcbtf-services-collector-monitor-mrnet-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_COLLECTOR_MONITOR_MRNET_MPI_SHARED_LIBRARY
    NAMES libcbtf-services-collector-monitor-mrnet-mpi.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_COLLECTOR_MONITOR_MRNET_MPI_STATIC_LIBRARY
    NAMES libcbtf-services-collector-monitor-mrnet-mpi-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_COMMON_SHARED_LIBRARY
    NAMES libcbtf-services-common.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_COMMON_STATIC_LIBRARY
    NAMES libcbtf-services-common-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_DATA_SHARED_LIBRARY
    NAMES libcbtf-services-data.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_DATA_STATIC_LIBRARY
    NAMES libcbtf-services-data-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_FILEIO_SHARED_LIBRARY
    NAMES libcbtf-services-fileio.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_FILEIO_STATIC_LIBRARY
    NAMES libcbtf-services-fileio-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_FPE_SHARED_LIBRARY
    NAMES libcbtf-services-fpe.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_FPE_STATIC_LIBRARY
    NAMES libcbtf-services-fpe-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_MONITOR_SHARED_LIBRARY
    NAMES libcbtf-services-monitor.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_MONITOR_STATIC_LIBRARY
    NAMES libcbtf-services-monitor-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_MRNET_SHARED_LIBRARY
    NAMES libcbtf-services-mrnet.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_MRNET_STATIC_LIBRARY
    NAMES libcbtf-services-mrnet-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_OFFLINE_SHARED_LIBRARY
    NAMES libcbtf-services-offline.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_OFFLINE_STATIC_LIBRARY
    NAMES libcbtf-services-offline-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_PAPI_SHARED_LIBRARY
    NAMES libcbtf-services-papi.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_PAPI_STATIC_LIBRARY
    NAMES libcbtf-services-papi-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_SEND_SHARED_LIBRARY
    NAMES libcbtf-services-send.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_SEND_STATIC_LIBRARY
    NAMES libcbtf-services-send-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_TIMER_SHARED_LIBRARY
    NAMES libcbtf-services-timer.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_TIMER_STATIC_LIBRARY
    NAMES libcbtf-services-timer-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_UNWIND_SHARED_LIBRARY
    NAMES libcbtf-services-unwind.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_SERVICES_UNWIND_STATIC_LIBRARY
    NAMES libcbtf-services-unwind-static.a
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_path(CBTF_SERVICES_INCLUDE_DIR
    KrellInstitute/Services/Assert.h
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES include
    )

find_package_handle_standard_args(
    CBTF-Services DEFAULT_MSG
    CBTF_SERVICES_BINUTILS_SHARED_LIBRARY
    CBTF_SERVICES_BINUTILS_STATIC_LIBRARY
    CBTF_SERVICES_COLLECTOR_MONITOR_FILEIO_SHARED_LIBRARY
    CBTF_SERVICES_COLLECTOR_MONITOR_FILEIO_STATIC_LIBRARY
    CBTF_SERVICES_COLLECTOR_MONITOR_MRNET_SHARED_LIBRARY
    CBTF_SERVICES_COLLECTOR_MONITOR_MRNET_STATIC_LIBRARY
    CBTF_SERVICES_COLLECTOR_MONITOR_MRNET_MPI_SHARED_LIBRARY
    CBTF_SERVICES_COLLECTOR_MONITOR_MRNET_MPI_STATIC_LIBRARY
    CBTF_SERVICES_COMMON_SHARED_LIBRARY
    CBTF_SERVICES_COMMON_STATIC_LIBRARY
    CBTF_SERVICES_DATA_SHARED_LIBRARY
    CBTF_SERVICES_DATA_STATIC_LIBRARY
    CBTF_SERVICES_FILEIO_SHARED_LIBRARY
    CBTF_SERVICES_FILEIO_STATIC_LIBRARY
    CBTF_SERVICES_FPE_SHARED_LIBRARY
    CBTF_SERVICES_FPE_STATIC_LIBRARY
    CBTF_SERVICES_MONITOR_SHARED_LIBRARY
    CBTF_SERVICES_MONITOR_STATIC_LIBRARY
    CBTF_SERVICES_MRNET_SHARED_LIBRARY
    CBTF_SERVICES_MRNET_STATIC_LIBRARY
    CBTF_SERVICES_OFFLINE_SHARED_LIBRARY
    CBTF_SERVICES_OFFLINE_STATIC_LIBRARY
    CBTF_SERVICES_PAPI_SHARED_LIBRARY
    CBTF_SERVICES_PAPI_STATIC_LIBRARY
    CBTF_SERVICES_SEND_SHARED_LIBRARY
    CBTF_SERVICES_SEND_STATIC_LIBRARY
    CBTF_SERVICES_TIMER_SHARED_LIBRARY
    CBTF_SERVICES_TIMER_STATIC_LIBRARY
    CBTF_SERVICES_UNWIND_SHARED_LIBRARY
    CBTF_SERVICES_UNWIND_STATIC_LIBRARY
    CBTF_SERVICES_INCLUDE_DIR
    )

set(CBTF_SERVICES_INCLUDE_DIRS ${CBTF_SERVICES_INCLUDE_DIR})

mark_as_advanced(
    CBTF_SERVICES_BINUTILS_SHARED_LIBRARY
    CBTF_SERVICES_BINUTILS_STATIC_LIBRARY
    CBTF_SERVICES_COLLECTOR_MONITOR_FILEIO_SHARED_LIBRARY
    CBTF_SERVICES_COLLECTOR_MONITOR_FILEIO_STATIC_LIBRARY
    CBTF_SERVICES_COLLECTOR_MONITOR_MRNET_SHARED_LIBRARY
    CBTF_SERVICES_COLLECTOR_MONITOR_MRNET_STATIC_LIBRARY
    CBTF_SERVICES_COLLECTOR_MONITOR_MRNET_MPI_SHARED_LIBRARY
    CBTF_SERVICES_COLLECTOR_MONITOR_MRNET_MPI_STATIC_LIBRARY
    CBTF_SERVICES_COMMON_SHARED_LIBRARY
    CBTF_SERVICES_COMMON_STATIC_LIBRARY
    CBTF_SERVICES_DATA_SHARED_LIBRARY
    CBTF_SERVICES_DATA_STATIC_LIBRARY
    CBTF_SERVICES_FILEIO_SHARED_LIBRARY
    CBTF_SERVICES_FILEIO_STATIC_LIBRARY
    CBTF_SERVICES_FPE_SHARED_LIBRARY
    CBTF_SERVICES_FPE_STATIC_LIBRARY
    CBTF_SERVICES_MONITOR_SHARED_LIBRARY
    CBTF_SERVICES_MONITOR_STATIC_LIBRARY
    CBTF_SERVICES_MRNET_SHARED_LIBRARY
    CBTF_SERVICES_MRNET_STATIC_LIBRARY
    CBTF_SERVICES_OFFLINE_SHARED_LIBRARY
    CBTF_SERVICES_OFFLINE_STATIC_LIBRARY
    CBTF_SERVICES_PAPI_SHARED_LIBRARY
    CBTF_SERVICES_PAPI_STATIC_LIBRARY
    CBTF_SERVICES_SEND_SHARED_LIBRARY
    CBTF_SERVICES_SEND_STATIC_LIBRARY
    CBTF_SERVICES_TIMER_SHARED_LIBRARY
    CBTF_SERVICES_TIMER_STATIC_LIBRARY
    CBTF_SERVICES_UNWIND_SHARED_LIBRARY
    CBTF_SERVICES_UNWIND_STATIC_LIBRARY
    CBTF_SERVICES_INCLUDE_DIR
    )

find_library(CBTF_CORE_LIBRARY
    NAMES libcbtf-core.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_path(CBTF_CORE_INCLUDE_DIR
    KrellInstitute/Core/Assert.hpp
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES include
    )

find_library(CBTF_CORE_SYMTABAPI_LIBRARY
    NAMES libcbtf-core-symtabapi.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_CORE_BFD_LIBRARY
    NAMES libcbtf-core-bfd.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_library(CBTF_CORE_MRNET_LIBRARY
    NAMES libcbtf-core-mrnet.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_package_handle_standard_args(
    CBTF-Core DEFAULT_MSG
    CBTF_CORE_LIBRARY CBTF_CORE_INCLUDE_DIR
    )

set(CBTF_CORE_LIBRARIES ${CBTF_CORE_LIBRARY})
set(CBTF_CORE_INCLUDE_DIRS ${CBTF_CORE_INCLUDE_DIR})

mark_as_advanced(CBTF_CORE_LIBRARY CBTF_CORE_INCLUDE_DIR CBTF_CORE_SYMTABAPI_LIBRARY CBTF_CORE_BFD_LIBRARY CBTF_CORE_MRNET_LIBRARY)


find_library(CBTF_MESSAGES_CUDA_SHARED_LIBRARY
    NAMES libcbtf-messages-cuda.so
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES lib lib64
    )

find_path(CBTF_MESSAGES_CUDA_INCLUDE_DIR
    KrellInstitute/Messages/CUDA_data.h
    HINTS ${CBTF_KRELL_DIR} $ENV{CBTF_KRELL_DIR}
    PATH_SUFFIXES include
    )

find_package_handle_standard_args(
    CBTF-Messages DEFAULT_MSG
    CBTF_MESSAGES_CUDA_SHARED_LIBRARY
    CBTF_MESSAGES_CUDA_INCLUDE_DIR
    )

set(CBTF_MESSAGES_CUDA_LIBRARIES
    ${CBTF_MESSAGES_CUDA_SHARED_LIBRARY}
    )

set(CBTF_MESSAGES_CUDA_INCLUDE_DIRS ${CBTF_MESSAGES_CUDA_INCLUDE_DIR})

mark_as_advanced(
    CBTF_MESSAGES_CUDA_SHARED_LIBRARY
    CBTF_MESSAGES_INCLUDE_DIR
    )
