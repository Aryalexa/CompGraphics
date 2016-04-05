#pragma once
#include "PV2D.h"
#include <cmath>

class Lapiz
{
private:
	PV2D* pos;
	GLdouble dir; // angulo(radianes) con el eje X
public:
	Lapiz();
	Lapiz(PV2D* pos, GLdouble dir);
	~Lapiz();

	void moveTo(PV2D* p, bool draw);
	void turnTo(GLdouble a);
	PV2D* getPos();
	GLdouble getDir();

	void turn(GLdouble a);
	void forward(GLdouble dist, bool draw);

	void dibujaRectangulo(PV2D* o, GLdouble b, GLdouble h);
	void dibujaPoligono(PV2D* c, GLdouble a, int n, GLdouble l);
	void dibujaArco(PV2D* c, GLdouble r, GLdouble a, GLdouble b);
	void dibujaEstrellaImpar(PV2D* c,GLdouble a, int n, GLdouble l);
};

