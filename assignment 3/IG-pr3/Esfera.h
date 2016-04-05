#pragma once
#include "objetocuadrico.h"
class Esfera :
	public ObjetoCuadrico
{
private:
	GLfloat r;
public:
	Esfera(GLfloat r);
	~Esfera(void);
	void dibuja();
};

