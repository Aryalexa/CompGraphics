#include "Cilindro.h"

Cilindro::Cilindro(){
	ObjetoCuadrico::ObjetoCuadrico();
}

Cilindro::Cilindro(GLfloat rBase, GLfloat rTop, GLfloat altura){
	ObjetoCuadrico::ObjetoCuadrico();
	this->r = rBase;
	this->R = rTop;
	this->h = altura;
}

Cilindro::~Cilindro(void)
{
	
}


void Cilindro::dibuja(){

	if (lines) 
		gluQuadricDrawStyle(qobj, GLU_LINE);
	else 
		gluQuadricDrawStyle(qobj, GLU_FILL);

	gluCylinder(qobj, r, R, h, slices, stacks);
}