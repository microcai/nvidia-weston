/*
 * egldisplay.h
 *
 *  Created on: 2012-7-20
 *      Author: cai
 */

#pragma once

#include "egltypedefs.h"

enum _egl_platform_type {
   _EGL_PLATFORM_X11 ,
   _EGL_PLATFORM_WAYLAND,

   _EGL_INVALID_PLATFORM = -1,

};
typedef enum _egl_platform_type _EGLPlatformType;

_EGLPlatformType _eglGetNativePlatform(EGLNativeDisplayType nativeDisplay);
