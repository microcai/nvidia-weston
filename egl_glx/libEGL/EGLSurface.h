/*
 * EGLSurface.h
 *
 *  Created on: 2012-7-20
 *      Author: cai
 */

#ifndef EGLSURFACE_H_
#define EGLSURFACE_H_

#include <EGL/egl.h>
#include <GL/glx.h>

class _EGLSurface
{
private:
	GLXDrawable	glxdraw;
public:
	operator EGLSurface(){return static_cast<EGLSurface>(this);};
	operator GLXDrawable(){return this->glxdraw;};
	_EGLSurface(GLXDrawable draw);
	virtual ~_EGLSurface();
};
/*
_EGLSurface operator  = ( EGLSurface s )
{
	return static_cast<_EGLSurface>(s);
}
*/
#endif /* EGLSURFACE_H_ */
