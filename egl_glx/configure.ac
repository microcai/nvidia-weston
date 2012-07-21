dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(egl_glx, 1.0)
AC_PROG_CC

AC_CANONICAL_SYSTEM

dnl Initialize automake
AM_INIT_AUTOMAKE

AC_PROG_RANLIB

dnl this allows us specify individual liking flags for each target
AM_PROG_CC_C_O 
AC_PROG_CXX
AC_PROG_CXX_C_O

dnl Initialize Libtool
LT_INIT

AC_CHECK_LIB(GL,glXGetProcAddress)

AC_CHECK_LIB(wayland-client,wl_display_connect)


dnl Check if Libtool is present
dnl Libtool is used for building share libraries 
AC_PROG_LIBTOOL

AC_CONFIG_FILES(Makefile
                example/Makefile                	
                libEGL/Makefile
                libEGL/platform/Makefile
		)
AC_OUTPUT
