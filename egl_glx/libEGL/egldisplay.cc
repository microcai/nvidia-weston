
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>

#include "egllog.h"
#include "egldisplay.h"

/**
 * Map egl-platforms names to platform types.
 */
#define _EGL_NUM_PLATFORMS 2
static const struct {
   _EGLPlatformType platform;
   const char *name;
} egl_platforms[_EGL_NUM_PLATFORMS] = {
   { _EGL_PLATFORM_X11, "x11" },
   { _EGL_PLATFORM_WAYLAND, "wayland" },
};



/**
 * Return the native platform by parsing EGL_PLATFORM.
 */
static _EGLPlatformType
_eglGetNativePlatformFromEnv(void)
{
   _EGLPlatformType plat = _EGL_INVALID_PLATFORM;
   const char *plat_name;
   EGLint i;

   plat_name = getenv("EGL_PLATFORM");
   /* try deprecated env variable */
   if (!plat_name || !plat_name[0])
      plat_name = getenv("EGL_DISPLAY");
   if (!plat_name || !plat_name[0])
      return _EGL_INVALID_PLATFORM;

   for (i = 0; i < _EGL_NUM_PLATFORMS; i++) {
      if (strcmp(egl_platforms[i].name, plat_name) == 0) {
         plat = egl_platforms[i].platform;
         break;
      }
   }

   return plat;
}



/**
 * Perform validity checks on a generic pointer.
 */
static EGLBoolean
_eglPointerIsDereferencable(void *p)
{
   uintptr_t addr = (uintptr_t) p;
   unsigned char valid = 0;
   const long page_size = getpagesize();

   if (p == NULL)
      return EGL_FALSE;

   /* align addr to page_size */
   addr &= ~(page_size - 1);

   if (mincore((void *) addr, page_size, &valid) < 0) {
      _eglLog(_EGL_DEBUG, "mincore failed: %m");
      return EGL_FALSE;
   }
   return (valid & 0x01) == 0x01;
}


/**
 * Try detecting native platform with the help of native display characteristcs.
 */
static _EGLPlatformType
_eglNativePlatformDetectNativeDisplay(EGLNativeDisplayType nativeDisplay)
{
#ifdef HAVE_FBDEV_PLATFORM
   struct stat buf;
#endif

   if (nativeDisplay == EGL_DEFAULT_DISPLAY)
      return _EGL_INVALID_PLATFORM;

   if (_eglPointerIsDereferencable(nativeDisplay)) {
      void *first_pointer = *(void **) nativeDisplay;

      (void) first_pointer; /* silence unused var warning */

      /* wl_display is a wl_proxy, which is a wl_object.
       * wl_object's first element points to the interfacetype. */
      if (first_pointer == &wl_display_interface)
         return _EGL_PLATFORM_WAYLAND;


      /* If not matched to any other platform, fallback to x11. */
      return _EGL_PLATFORM_X11;
   }

   return _EGL_INVALID_PLATFORM;
}


/**
 * Return the native platform.  It is the platform of the EGL native types.
 */
_EGLPlatformType
_eglGetNativePlatform(EGLNativeDisplayType nativeDisplay)
{
   static _EGLPlatformType native_platform = _EGL_INVALID_PLATFORM;
   const char *detection_method = NULL;

   if (native_platform == _EGL_INVALID_PLATFORM) {
      native_platform = _eglGetNativePlatformFromEnv();
      detection_method = "environment overwrite";
      if (native_platform == _EGL_INVALID_PLATFORM) {
         native_platform = _eglNativePlatformDetectNativeDisplay(nativeDisplay);
         detection_method = "autodetected";
         if (native_platform == _EGL_INVALID_PLATFORM) {
            native_platform = _EGL_INVALID_PLATFORM;
            detection_method = "build-time configuration";
         }
      }
   }

   if (detection_method != NULL)
      _eglLog(_EGL_DEBUG, "Native platform type: %s (%s)",
              egl_platforms[native_platform].name, detection_method);

   return native_platform;
}
