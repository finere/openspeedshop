################################################################################
# Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
# Copyright (c) 2006-2009 Krell Institute.  All Rights Reserved.
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


################################################################################
# Check for Dyninst (http://www.dyninst.org)
# This is only used for configuring for the dyninst tests
################################################################################

AC_DEFUN([AC_PKG_DYNINST], [

    AC_ARG_WITH(dyninst,
                AC_HELP_STRING([--with-dyninst=DIR],
                               [Dyninst installation @<:@/usr@:>@]),
                dyninst_dir=$withval, dyninst_dir="/usr")

    DYNINST_CPPFLAGS="-I$dyninst_dir/include/dyninst"
    DYNINST_CPPFLAGS="$DYNINST_CPPFLAGS -DUSE_STL_VECTOR -DIBM_BPATCH_COMPAT"
    DYNINST_LIBS="-ldyninstAPI -lcommon -lsymtabAPI"
    DYNINST_DIR="$dyninst_dir"
    echo "host is $host"
	case "$host" in
        x86_64-*-linux* | x86_64-redhat-linux-gnu)
		DYNINST_LDFLAGS="-L$dyninst_dir/lib64"
		;;
	*)
		DYNINST_LDFLAGS="-L$dyninst_dir/lib"
		;;
	esac

    AC_LANG_PUSH(C++)
    AC_REQUIRE_CPP

    dyninst_saved_CPPFLAGS=$CPPFLAGS
    dyninst_saved_LDFLAGS=$LDFLAGS

    CPPFLAGS="$CPPFLAGS $DYNINST_CPPFLAGS"
    LDFLAGS="$CXXFLAGS $DYNINST_LDFLAGS $DYNINST_LIBS -liberty -ldl $LIBDWARF_LDFLAGS $LIBDWARF_LIBS"

    AC_MSG_CHECKING([for Dyninst API library and headers])

    AC_LINK_IFELSE(AC_LANG_PROGRAM([[
	#include <BPatch.h>
        ]], [[
	BPatch bpatch();
        ]]), AC_MSG_RESULT(yes), [ AC_MSG_RESULT(no)
        AC_MSG_FAILURE(cannot locate Dyninst API library and/or headers.) ]
    )

    CPPFLAGS=$dyninst_saved_CPPFLAGS
    LDFLAGS=$dyninst_saved_LDFLAGS

    AC_LANG_POP(C++)

    AC_SUBST(DYNINST_CPPFLAGS)
    AC_SUBST(DYNINST_LDFLAGS)
    AC_SUBST(DYNINST_LIBS)
    AC_SUBST(DYNINST_DIR)

    AC_DEFINE(HAVE_DYNINST, 1, [Define to 1 if you have Dyninst.])

])


################################################################################
# Check for libdwarf (http://www.reality.sgiweb.org/davea/dwarf.html)
################################################################################

AC_DEFUN([AC_PKG_LIBDWARF], [

    AC_ARG_WITH(libdwarf,
                AC_HELP_STRING([--with-libdwarf=DIR],
                               [libdwarf installation @<:@/usr@:>@]),
                libdwarf_dir=$withval, libdwarf_dir="/usr")

    found_libdwarf=0

    LIBDWARF_CPPFLAGS="-I$libdwarf_dir/$abi_libdir/libdwarf/include"
    LIBDWARF_LDFLAGS="-L$libdwarf_dir/$abi_libdir/libdwarf/$abi_libdir"
    LIBDWARF_LIBS="-ldwarf"

    libdwarf_saved_CPPFLAGS=$CPPFLAGS
    libdwarf_saved_LDFLAGS=$LDFLAGS

    CPPFLAGS="$CPPFLAGS $LIBDWARF_CPPFLAGS"
    LDFLAGS="$LDFLAGS $LIBDWARF_LDFLAGS $LIBDWARF_LIBS -lelf -lpthread"

    AC_MSG_CHECKING([for libdwarf library and headers])

    AC_LINK_IFELSE(AC_LANG_PROGRAM([[
        #include <dwarf.h>
        ]], [[
        if (DW_ID_up_case != DW_ID_down_case) {
           int mycase = DW_ID_up_case;
        }
        ]]), [ found_libdwarf=1 ], [ found_libdwarf=0 ])

    if test $found_libdwarf -eq 1; then
        AC_MSG_RESULT(yes)
        AM_CONDITIONAL(HAVE_LIBDWARF, true)
        AC_DEFINE(HAVE_LIBDWARF, 1, [Define to 1 if you have LIBDWARF.])
    else
# Try again with the traditional path instead
         found_libdwarf=0
         LIBDWARF_CPPFLAGS="-I$libdwarf_dir/include"
         LIBDWARF_LDFLAGS="-L$libdwarf_dir/$abi_libdir"

         CPPFLAGS="$CPPFLAGS $LIBDWARF_CPPFLAGS"
         LDFLAGS="$LDFLAGS $LIBDWARF_LDFLAGS $LIBDWARF_LIBS -lelf -lpthread"

         AC_MSG_CHECKING([for libdwarf library and headers])

         AC_LINK_IFELSE(AC_LANG_PROGRAM([[
             #include <dwarf.h>
             ]], [[
             if (DW_ID_up_case != DW_ID_down_case) {
                int mycase = DW_ID_up_case;
             }
             ]]), [ found_libdwarf=1

             ], [ found_libdwarf=0 ])

         if test $found_libdwarf -eq 1; then
             AC_MSG_RESULT(yes)
             AM_CONDITIONAL(HAVE_LIBDWARF, true)
             AC_DEFINE(HAVE_LIBDWARF, 1, [Define to 1 if you have LIBDWARF.])
         else
             AC_MSG_RESULT(no)
             AM_CONDITIONAL(HAVE_LIBDWARF, false)
             AC_DEFINE(HAVE_LIBDWARF, 0, [Define to 0 if you do not have LIBDWARF.])
             LIBDWARF_CPPFLAGS=""
             LIBDWARF_LDFLAGS=""
             LIBDWARF_LIBS=""
         fi
    fi

    CPPFLAGS=$libdwarf_saved_CPPFLAGS LDFLAGS=$libdwarf_saved_LDFLAGS

    AC_SUBST(LIBDWARF_CPPFLAGS)
    AC_SUBST(LIBDWARF_LDFLAGS)
    AC_SUBST(LIBDWARF_LIBS)

])
