/*
 * EGLDisplay.h
 *
 *  Created on: 2012-7-20
 *      Author: cai
 */

#ifndef EGLDISPLAY_H_
#define EGLDISPLAY_H_

#include "egldisplay.h"

#include "EGLContext.h"
#include "EGLSurface.h"

class _EGLDisplay
{
	operator Display* (){return disp;};

public: // data
	_EGLPlatformType platformtype;
	Display *disp;
public:
	//virtuals
	virtual EGLBoolean eglChooseConfig(const EGLint *attrib_list, EGLConfig *configs, EGLint config_size,EGLint *num_config)=0;
	virtual EGLContext eglCreateContext(EGLConfig config,EGLContext share_context,const EGLint *attrib_list) = 0;
	virtual EGLSurface eglCreatePbufferSurface(EGLConfig config, const EGLint *attrib_list) = 0;
	virtual EGLBoolean eglMakeCurrent(_EGLSurface *draw,_EGLSurface *read, _EGLContext* ctx)=0;
	virtual EGLSurface eglCreateWindowSurface(EGLConfig config,EGLNativeWindowType win,const EGLint *attrib_list)=0;
	virtual EGLBoolean eglSwapBuffers(_EGLSurface *surface)=0;

public:
	operator			EGLDisplay(){return static_cast<EGLDisplay>(this);};
	_EGLDisplay();
	virtual ~_EGLDisplay();
};

#endif /* EGLDISPLAY_H_ */
