/**
 * VampirTrace
 * http://www.tu-dresden.de/zih/vampirtrace
 *
 * Copyright (c) 2005-2007, ZIH, TU Dresden, Federal Republic of Germany
 *
 * Copyright (c) 1998-2005, Forschungszentrum Juelich GmbH, Federal
 * Republic of Germany
 *
 * See the file COPYRIGHT in the package base directory for details
 **/

#ifndef _VT_PFORM_H
#define _VT_PFORM_H

#ifdef __cplusplus
#   define EXTERN extern "C" 
#else
#   define EXTERN extern 
#endif

#include "vt_inttypes.h"

/* platform specific initialization */
EXTERN void   vt_pform_init();

/* directory of global file system  */
EXTERN char*  vt_pform_gdir();

/* directory of local file system  */
EXTERN char*  vt_pform_ldir();

/* is a global clock provided ? */
EXTERN int    vt_pform_is_gclock();

/* clock resolution */
EXTERN uint64_t vt_pform_clockres();

/* local or global wall-clock time */
EXTERN uint64_t vt_pform_wtime();

/* unique numeric SMP-node identifier */
EXTERN long   vt_pform_node_id();

/* unique string SMP-node identifier */
EXTERN char*  vt_pform_node_name();

/* number of CPUs */
EXTERN int    vt_pform_num_cpus();

#endif




