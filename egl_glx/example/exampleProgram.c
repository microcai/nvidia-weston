/*
 ============================================================================
 Name        : exampleProgram.c
 Author      : microcai
 Version     :
 Copyright   : GPL
 Description : Uses shared library to print greeting
               To run the resulting executable the LD_LIBRARY_PATH must be
               set to ${project_loc}/libEGL/.libs
               Alternatively, libtool creates a wrapper shell script in the
               build directory of this program which can be used to run it.
               Here the script will be called exampleProgram.
 ============================================================================
 */

#include "libEGL.h"

int main(void) {
  eglGetDisplay(0);
  return 0;
}
