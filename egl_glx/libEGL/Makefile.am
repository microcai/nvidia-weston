
SUBDIRS =  platform
#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libEGL.la libGLESv2.la
# Sources for libGLESv2
libGLESv2_la_SOURCES = dumy.c
libGLESv2_la_LDFLAGS = -version-info 2:0:0

#######################################
# Build information for each library

#source code from mesa
SOURCES_MESA = egldisplay.cc egldisplay.h egllog.cc egllog.h eglstring.cc eglstring.h

libEGL_la_DEPENDENCIES = platform/libEGL_platform.a

# Sources for libEGL
libEGL_la_SOURCES = EGLDisplay.h EGLDisplay.cpp \
						EGLContext.h EGLContext.cpp \
						EGLSurface.h EGLSurface.cpp \
						libEGL.cc $(SOURCES_MESA)

libEGL_la_LIBADD  = platform/libEGL_platform.a
# Linker options libTestProgram
libEGL_la_LDFLAGS = -version-info 1:0:0

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libEGL_la_CPPFLAGS = -I$(top_srcdir)/include

