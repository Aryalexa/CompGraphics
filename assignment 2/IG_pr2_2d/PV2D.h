#ifndef PV2D_H
#define PV2D_H
// WINDOWS
#include <Windows.h>
#include <gl/GL.h>

// APPLE
//#include "screencasts.h"


class PV2D
{
private:
	GLfloat x, y;
	int pv;

public:
	PV2D(GLfloat x, GLfloat y, int pv);
	~PV2D();

	GLfloat getX(), getY();
};
#endif /* PV2D_H */
