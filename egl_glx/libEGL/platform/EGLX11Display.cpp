/*
 * EGLX11Display.cpp
 *
 *  Created on: 2012-7-20
 *      Author: cai
 */
#include <stdio.h>
#include <GL/glx.h>

#include "EGLSurface.h"
#include "EGLX11Display.h"

EGLX11Display::EGLX11Display(EGLNativeDisplayType display_id)
{
	this->platformtype = _EGL_PLATFORM_X11;
	this->disp = display_id;
}

EGLX11Display::~EGLX11Display()
{
	// TODO Auto-generated destructor stub
}

EGLBoolean EGLX11Display::eglChooseConfig(const EGLint *attrib_list, EGLConfig *configs, EGLint config_size,EGLint *num_config)
{
	this->config = glXGetFBConfigs(disp,DefaultScreen(disp),num_config);
	return EGL_TRUE;
}

EGLContext EGLX11Display::eglCreateContext(EGLConfig config,EGLContext share_context,const EGLint *attrib_list)
{
	GLXContext	glshare=0;

	int elements;

	printf("glXCreateNewContext\n");

	GLXContext ctx = glXCreateNewContext(disp,this->config[0],GLX_RGBA_TYPE,glshare,1);

	return new _EGLContext(ctx);
}

static int eglattr2glx(EGLint attr)
{
	switch (attr) {
		case EGL_WIDTH:
			return GLX_PBUFFER_WIDTH;
			break;
		case EGL_HEIGHT:
			return GLX_PBUFFER_HEIGHT;
		case EGL_NONE:
			return GLX_NONE;
		default:
			return attr;
	}
}

static int concert_attr(const EGLint *attrib_list,EGLint *converted)
{
	int i =0;
	converted[i] = GLX_NONE;

	while(attrib_list && attrib_list[i]!=EGL_NONE){
		converted[i] = eglattr2glx(attrib_list[i]);
		converted[i+1] = attrib_list[i+1];
		i+=2;
	}
	converted[i] = GLX_NONE;
	return i;
}

EGLSurface EGLX11Display::eglCreatePbufferSurface(EGLConfig config, const EGLint *attrib_list)
{
	GLXFBConfig	*glconfig;

	EGLint	converted[100];

	int elements;

	glconfig = glXGetFBConfigs(disp,0,&elements);

	elements = concert_attr(attrib_list,converted);

	return new _EGLSurface(glXCreatePbuffer(disp,glconfig[0],converted));
}

EGLSurface EGLX11Display::eglCreateWindowSurface(EGLConfig config,EGLNativeWindowType win,const EGLint *attrib_list)
{
	int converted[100];

	concert_attr(attrib_list, converted);

	GLXDrawable glxdrawable = glXCreateWindow(disp, this->config[0], win,
			attrib_list ? converted : NULL);

	return new _EGLSurface(glxdrawable);
}


EGLBoolean EGLX11Display::eglMakeCurrent(_EGLSurface *_draw,_EGLSurface *_read, _EGLContext *_ctx)
{
	GLXDrawable draw = 0;
	GLXDrawable read = 0;
	GLXContext  ctx = 0;

	if(_draw)
		draw = *_draw;
	if(_read)
		read = * _read;
	if(_ctx)
		ctx = *_ctx;

	glXWaitX();

	return glXMakeContextCurrent(disp,draw,read,ctx);
}

EGLBoolean EGLX11Display::eglSwapBuffers(_EGLSurface *surface)
{
	glXSwapBuffers(disp,*surface);
	return EGL_TRUE;
}
