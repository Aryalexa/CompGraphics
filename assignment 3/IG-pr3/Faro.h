#pragma once
#include "Cilindro.h"
class Faro :
	public Cilindro
{
private:
	int pos; //izq o derecha (0 o 1)
	GLfloat alpha; // grados
	GLfloat eps;
public:
	Faro(int pos, GLfloat r, GLfloat R, GLfloat h);
	~Faro();
	void dibuja();
};

