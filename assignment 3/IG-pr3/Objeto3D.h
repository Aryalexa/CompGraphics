#pragma once
// WINDOWS
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

// APPLE
//#include "screencasts.h"
///////////////////////////////////

#include "TAfin.h"
#include "Color.h"


class Objeto3D
{	
protected:
	TAfin* mT;
	Color* color;
public:
	
	Objeto3D(void);
	Objeto3D(Color *color);
	~Objeto3D(void);

	virtual void dibuja(); // metodo virtual!
	
	GLfloat* getMatrizAfin();
	TAfin* getTAfin();

	void traslada(PV3D* v);
	void escala(PV3D* x);
	void rota(GLfloat a, PV3D* v);

	void setColor(GLfloat r, GLfloat g, GLfloat b);
	void colorea();
	GLfloat getRed();
	GLfloat getGreen();
	GLfloat getBlue();
};

