#include "ObjetoComp3D.h"




ObjetoComp3D::ObjetoComp3D(void)
{
}


ObjetoComp3D::~ObjetoComp3D(void)
{
}


void ObjetoComp3D::dibuja(){
	for (int i=0; i<numHijos; i++){
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glMultMatrixf(hijos[i]->getMatrizAfin()); // cambia matriz
			hijos[i]->colorea();
			hijos[i]->dibuja();
		glPopMatrix();
	}
}

void ObjetoComp3D::setColor(GLfloat r, GLfloat g, GLfloat b){
	for (int i=0; i<numHijos; i++)
		hijos[i]->setColor(r, g, b);
}