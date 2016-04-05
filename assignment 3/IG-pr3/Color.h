#pragma once
// WINDOWS
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

// APPLE
//#include "screencasts.h"

class Color
{
private:
	GLfloat red;
	GLfloat green;
	GLfloat blue;
public:
	Color(void);
	Color(GLfloat r, GLfloat g, GLfloat b);
	~Color(void);
	void setColors(GLfloat r, GLfloat g, GLfloat b);
	GLfloat getR();
	GLfloat getG();
	GLfloat getB();

};

