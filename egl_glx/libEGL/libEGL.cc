
#define EGL_EGLEXT_PROTOTYPES

#include <stdlib.h>
#include <string.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

#include "egldisplay.h"
#include "EGLContext.h"

#include "platform/EGLX11Display.h"

EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay(EGLNativeDisplayType display_id)
{
	_EGLPlatformType platform = 	_eglGetNativePlatform(display_id);

	switch (platform) {
		case _EGL_PLATFORM_X11:
			return new EGLX11Display(display_id);
			break;
		case _EGL_PLATFORM_WAYLAND:
			return NULL; // not impl
			break;
		default:
			return NULL;
	}

}

EGLAPI EGLBoolean EGLAPIENTRY eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
	return EGL_TRUE;
}

EGLAPI EGLBoolean EGLAPIENTRY eglBindAPI(EGLenum api)
{
	if(api&EGL_OPENGL_API)
		return EGL_TRUE;
	if(api & EGL_OPENGL_ES_API)
		return EGL_TRUE;
	return EGL_FALSE;
}

EGLAPI EGLBoolean EGLAPIENTRY eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list,
			   EGLConfig *configs, EGLint config_size,
			   EGLint *num_config)
{
	return ((_EGLDisplay*)dpy)->eglChooseConfig(attrib_list,configs,config_size,num_config);
}

EGLAPI EGLContext EGLAPIENTRY eglCreateContext(EGLDisplay dpy, EGLConfig config,
		EGLContext share_context, const EGLint *attrib_list)
{
	return ((_EGLDisplay*)dpy)->eglCreateContext(config,share_context,attrib_list);
}

EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface(EGLDisplay dpy,EGLConfig config, const EGLint *attrib_list)
{
	return ((_EGLDisplay*)dpy)->eglCreatePbufferSurface(config,attrib_list);
}

EGLAPI EGLSurface EGLAPIENTRY eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config,EGLNativeWindowType win,const EGLint *attrib_list)
{
	return ((_EGLDisplay*)dpy)->eglCreateWindowSurface(config,win,attrib_list);
}

EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
//	glXDestroyWindow(disp,surface)
	return EGL_TRUE;
}


EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent(EGLDisplay dpy, EGLSurface draw,EGLSurface read, EGLContext ctx)
{
	return ((_EGLDisplay*)dpy)->eglMakeCurrent(static_cast<_EGLSurface*>(draw),static_cast<_EGLSurface*>(read),static_cast<_EGLContext*>(ctx));
}

EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
	return ((_EGLDisplay*)dpy)->eglSwapBuffers(static_cast<_EGLSurface*>(surface));
}

EGLAPI const char * EGLAPIENTRY eglQueryString(EGLDisplay dpy, EGLint name)
{
	switch (name) {
		case EGL_VERSION:
			return "2.0";
		case EGL_VENDOR:
			return "EGL_GLX";
		case EGL_CLIENT_APIS:
			return "2.0";
		case EGL_EXTENSIONS:
			return "eglBindWaylandDisplayWL";
		default:
			return NULL;
	}
}

#define	PROC(x) { #x , (__eglMustCastToProperFunctionPointerType)x   },

static struct  _eglProcs{
	const char * procname;
	__eglMustCastToProperFunctionPointerType addr;
}eglProcs[]={
		PROC(eglBindWaylandDisplayWL)
		PROC(eglUnbindWaylandDisplayWL)
		PROC(eglQueryWaylandBufferWL)
		NULL
};


EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY eglGetProcAddress(const char *procname)
{
	// libGL 找不到的才找自己
	void (*address)();
	address = glXGetProcAddress((GLubyte*)procname);
	if(!address)
	{
		struct  _eglProcs* eglprocs = eglProcs;
		while(eglprocs->addr)
		{
			if(!strcmp(procname,eglprocs->procname))
				return eglprocs->addr;
			eglprocs ++;
		}
	}

	return (__eglMustCastToProperFunctionPointerType)address;
}

EGLAPI EGLBoolean EGLAPIENTRY eglTerminate(EGLDisplay dpy)
{
	return EGL_TRUE;
}

EGLAPI EGLBoolean EGLAPIENTRY eglReleaseThread(void)
{
	return EGL_TRUE;
}

EGLAPI EGLBoolean EGLAPIENTRY eglBindWaylandDisplayWL(EGLDisplay dpy, struct wl_display *display)
{

}


EGLAPI EGLBoolean EGLAPIENTRY eglUnbindWaylandDisplayWL(EGLDisplay dpy, struct wl_display *display)
{

}

EGLAPI EGLBoolean EGLAPIENTRY eglQueryWaylandBufferWL(EGLDisplay dpy, struct wl_buffer *buffer, EGLint attribute, EGLint *value)
{

}
