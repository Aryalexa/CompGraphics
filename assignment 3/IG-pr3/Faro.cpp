#include "Faro.h"


Faro::Faro(int posic, GLfloat rBase, GLfloat rTop, GLfloat altura)
{
	Cilindro::Cilindro();
	r = rBase;
	R = rTop;
	h = altura;

	pos = posic;

	alpha = 35; // grados
	eps = 10; // exponente

}


Faro::~Faro()
{

}


void Faro::dibuja(){

	GLfloat d_e[]={1.0,1.0,1.0,1.0};
	GLfloat a[]={0.3f,0.3f,0.3f,1.0};
	GLfloat p[] = {0, 0.0, -0.6, 1.0}; // posicional
	GLfloat dirEm[] = {0.0,0.0,1.0};

	if (pos){
		//GLfloat pos[] = {5, 0.0, 0, 1.0}; // posicional

		// ** GL_LIGHT3 **
		glLightfv(GL_LIGHT3, GL_DIFFUSE, d_e);
		glLightfv(GL_LIGHT3, GL_AMBIENT, a);
		//glLightfv(GL_LIGHT3, GL_SPECULAR, d_e);
		glLightfv(GL_LIGHT3, GL_POSITION, p);

		//la luz será un foco
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, alpha);
		glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, eps);
		
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dirEm);
	}
	else {
		//GLfloat pos[] = {-5, 0.0, 0, 1.0}; // posicional

		// ** GL_LIGHT4 **
		glLightfv(GL_LIGHT4, GL_DIFFUSE, d_e);
		glLightfv(GL_LIGHT4, GL_AMBIENT, a);
		//glLightfv(GL_LIGHT4, GL_SPECULAR, d_e);
		glLightfv(GL_LIGHT4, GL_POSITION, p);

		//la luz será un foco
		glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, alpha);
		glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, eps);
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dirEm);
	}

	
	//dibuja
	Cilindro::dibuja();
	
}