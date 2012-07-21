/*
 * EGLX11Display.h
 *
 *  Created on: 2012-7-20
 *      Author: cai
 */

#ifndef EGLX11DISPLAY_H_
#define EGLX11DISPLAY_H_

#include <EGL/egl.h>

#include "EGLDisplay.h"

class EGLX11Display: public _EGLDisplay
{
private:
	GLXFBConfig*config;
public:
	EGLBoolean eglChooseConfig(const EGLint *attrib_list, EGLConfig *configs, EGLint config_size,EGLint *num_config);
	EGLContext eglCreateContext(EGLConfig config,EGLContext share_context,const EGLint *attrib_list);
	EGLSurface eglCreatePbufferSurface(EGLConfig config, const EGLint *attrib_list);
	EGLBoolean eglMakeCurrent(_EGLSurface *draw,_EGLSurface *read, _EGLContext *ctx);
	EGLSurface eglCreateWindowSurface(EGLConfig config,EGLNativeWindowType win,const EGLint *attrib_list);
	EGLBoolean eglSwapBuffers(_EGLSurface *surface);
public:
	EGLX11Display(EGLNativeDisplayType display_id);
	virtual ~EGLX11Display();
};

#endif /* EGLX11DISPLAY_H_ */
