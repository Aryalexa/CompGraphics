#pragma once

#include "PV3D.h"
#include "Cara.h"

// WINDOWS
#include <gl/GL.h>
#include <gl/GLU.h>


#include <Windows.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>

// APPLE
//#include "screencasts.h"

#include "Objeto3D.h"

using namespace std;


class Malla :
	public Objeto3D
{
protected:
	int numVertices;
	PV3D** vertice;
	int numNormales; //=numCaras, frecuentemente
	PV3D** normal;
	int numCaras;
	Cara** cara;
	bool lines;
	bool normales;
	void dibujaNormales();

	GLuint textura;

public:
	Malla();
	Malla(int numVertices, PV3D** vertice, int numNormales, PV3D** normal, int numCaras, Cara** cara);
	~Malla();
	void dibuja();
	PV3D* calculoVectorNormalPorNewell(Cara* c);
	void setLines(bool b);
	void toggleNormales();
	void setTexture(GLuint tex);
};
