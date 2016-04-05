#include "Chasis.h"


Chasis::Chasis(void)
{
	Cubo::Cubo();
	textura = 1;
}


Chasis::~Chasis(void)
{
}

void Chasis::dibuja(){
	
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 }; 
	GLfloat mat_amb[] = {0.25,0.25,0.25,1.0};
	GLfloat mat_dif[] = {0.4,0.4,0.4,1.0};
	GLfloat mat_spec[] = {0.774597,0.774597,0.774597,1.0};

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	//glMaterialf(GL_FRONT, GL_SHININESS, 76.8);
	
	Cubo::dibuja();

	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	//glMaterialf(GL_FRONT, GL_SHININESS, 0);
}
