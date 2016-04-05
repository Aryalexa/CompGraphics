#include "Coche.h"

const GLfloat tam = 0.8;

GLfloat radioR = 0.2; // de las ruedas
GLfloat alturaR = 0.2; // de las ruedas
int slices = 7;
int stacks = 3;

Coche::Coche()
{
	qobj = gluNewQuadric();
	f = new Ficha(slices,radioR,alturaR);
}


Coche::~Coche()
{
}



void Coche::dibuja(GLfloat* m){
	GLfloat ancho = 0.8;// x
	GLfloat alto = 0.4;// y
	GLfloat largo = 1.6;// z


	//TODO

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		glMultMatrixf(m);
		glScalef(tam, tam, tam);
		//if () glRotatef(45,1,0,0);
		glRotatef(180,1,0,0);

		/// ** COCHE ***


		glColor3f(0.0,0.4,1.0); //verde

		glPushMatrix(); // *** arriba
			glTranslatef(0, alto, 0);
			glScalef(ancho, alto, largo/2);
			glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix(); // *** abajo
			glScalef(ancho, alto, largo);
			glutSolidCube(1.0);
		glPopMatrix();


		glColor3f(0.0,0.7,0.3);	// (azul)


		/// ** Rueda 1 **
		glPushMatrix();

			glTranslatef(2*ancho/5, -alto/2, ancho/2);
			//glutSolidCylinder(radioR, alturaR, slices, stacks);
			glRotatef(90,0,1,0);
			gluQuadricDrawStyle(qobj, GLU_FILL);
			gluCylinder(qobj, radioR, radioR, alturaR, slices, stacks);

			glPushMatrix(); // tapa 1
				//glTranslatef(0.2, 0, 0);
				gluQuadricDrawStyle(qobj, GLU_FILL);
				gluCylinder(qobj, 0, radioR, 0, slices, stacks);
			glPopMatrix();
			glPushMatrix(); // tapa 2
				glTranslatef(0, 0, 0.2);
				gluQuadricDrawStyle(qobj, GLU_FILL);
				gluCylinder(qobj, 0, radioR, 0, slices, stacks);
			glPopMatrix();

		glPopMatrix();

		/// ** Rueda 2 **
		glPushMatrix();

			glTranslatef(-3*ancho/5, -alto/2, ancho/2);
			//glutSolidCylinder(radioR, alturaR, slices, stacks);
			glRotatef(90,0,1,0);
			gluQuadricDrawStyle(qobj, GLU_FILL);
			gluCylinder(qobj, radioR, radioR, alturaR, slices, stacks);

			glPushMatrix(); // tapa 1
				//glTranslatef(0.2, 0, 0);
				gluQuadricDrawStyle(qobj, GLU_FILL);
				gluCylinder(qobj, 0, radioR, 0, slices, stacks);
			glPopMatrix();
			glPushMatrix(); // tapa 2
				glTranslatef(0, 0, 0.2);
				gluQuadricDrawStyle(qobj, GLU_FILL);
				gluCylinder(qobj, 0, radioR, 0, slices, stacks);
			glPopMatrix();

		glPopMatrix();

		/// ** Rueda 3 **
		glPushMatrix();
			glTranslatef(-2*ancho/5, -alto/2, -ancho/2);
			glRotatef(90,0,0,1);
			f->dibuja();
		glPopMatrix();

		/// ** Rueda 3 **
		glPushMatrix();
			glTranslatef(2*ancho/5, -alto/2, -ancho/2);
			glRotatef(90*3,0,0,1);
			f->dibuja();
		glPopMatrix();
		/// **

	glPopMatrix();
}
