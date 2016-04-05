#pragma once
#include "objetocuadrico.h"
class Cilindro :
	public ObjetoCuadrico
{
protected:
	GLfloat r;
	GLfloat R;
	GLfloat h;
public:
	Cilindro(void);
	Cilindro(GLfloat r, GLfloat R, GLfloat h);
	~Cilindro(void);
	void dibuja();
};

