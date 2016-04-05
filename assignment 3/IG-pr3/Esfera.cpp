#include "Esfera.h"


Esfera::Esfera(GLfloat radio)
{
	ObjetoCuadrico::ObjetoCuadrico();
	r = radio;
	//lines=true;
}


Esfera::~Esfera(void)
{
	
}

void Esfera::dibuja(){
	if (lines) 
		gluQuadricDrawStyle(qobj, GLU_LINE); 
	else 
		gluQuadricDrawStyle(qobj, GLU_FILL); 

	glEnable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,1);

	gluSphere(qobj,r,slices,stacks);

	glDisable(GL_TEXTURE_2D);
}