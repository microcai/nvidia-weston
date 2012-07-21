
AM_CPPFLAGS = -fPIC

noinst_LIBRARIES = libEGL_platform.a

#######################################
# Build information for each library

#source code from mesa

# Sources for libEGL
libEGL_platform_a_SOURCES = EGLX11Display.h EGLX11Display.cpp

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libEGL_platform_a_CPPFLAGS = -I$(top_srcdir)/include -I$(srcdir)/..

