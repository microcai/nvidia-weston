/*
 * EGLContext.h
 *
 *  Created on: 2012-7-20
 *      Author: cai
 */

#ifndef EGLCONTEXT_H_
#define EGLCONTEXT_H_

#include <GL/glx.h>

class _EGLContext
{
private:
	GLXContext glxcontext;
public:
	operator GLXContext(){return glxcontext;};
public:
	_EGLContext(GLXContext glxcontext);
	virtual ~_EGLContext();
};

#endif /* EGLCONTEXT_H_ */
