#include "Coche.h"

const GLfloat TAM = 0.8;
const GLfloat PI = 3.14159;
const bool DEBUG = false;

GLfloat radioR = 0.2; // de las ruedas
GLfloat alturaR = 0.2; // de las ruedas
int slices = 7;
int stacks = 3;

/* El coche se mueve con 'r' (avanzar) y 'R' (retroceder) */
Coche::Coche()
{
	qobj = gluNewQuadric();
	f = new Ficha(slices,radioR,alturaR);
}


Coche::~Coche()
{
}



void Coche::dibuja(GLfloat* m, GLfloat t){
	
	if (DEBUG) { //recorre una circunferencia de radio r
		GLfloat r = 3;
		m[0] = -cos(t); // vNormal X();
		m[1] = 0; // vNormal Y();
		m[2] = -sin(t); // vNormal Z();
		m[3] = 0;
		m[4] = 0; // vBinormal X();
		m[5] = 1; // vBinormal Y();
		m[6] = 0; // vBinormal Z();
		m[7] = 0;
		m[8] = -sin(t); // vTangente X();
		m[9] = 0;  // vTangente Y();
		m[10] = cos(t); // vTangente Z();
		m[11] = 0;
		m[12] = r*cos(t); // curva(t)->getX();
		m[13] = 0; // curva(t)->getY();
		m[14] = r*sin(t); // curva(t)->getZ();
		m[15] = 1;
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		glMultMatrixf(m);
		glScalef(TAM, TAM, TAM);

		if ((sin(PI/4)<=sin(t) && sin(t)<=sin(PI/2)) ||
			(sin(3*PI / 2) <= sin(t) && sin(t) <= sin(5*PI / 4)))
			glRotatef(20,0,1,0);

		
		if (!DEBUG) glRotatef(180,1,0,0);//ponerlo cabeza abajo para verse mejor en el tubo


		/// ** COCHE ***
		dibuja(t);



	glPopMatrix();
}

void Coche::dibuja(GLfloat t){

	GLfloat ancho = 0.8;// x
	GLfloat alto = 0.4;// y
	GLfloat largo = 2;// z


	glColor3f(0.0, 0.4, 1.0); // (azul)

	glPushMatrix(); // *** arriba
		glTranslatef(0, alto, 0);
		glScalef(ancho, alto, largo / 2);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix(); // *** abajo
		glScalef(ancho, alto, largo);
		glutSolidCube(1.0);
	glPopMatrix();


	glColor3f(0.0, 0.7, 0.3);	// (verde)


	/// ** Rueda 1 **
	glPushMatrix();

		glTranslatef(2 * ancho / 5, -alto / 2, ancho / 2);
		//glutSolidCylinder(radioR, alturaR, slices, stacks);
		glRotatef(90, 0, 1, 0);
		gluQuadricDrawStyle(qobj, GLU_FILL);
		gluCylinder(qobj, radioR, radioR, alturaR, slices, stacks);

		glPushMatrix(); // tapa 1
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

		glTranslatef(-3 * ancho / 5, -alto / 2, ancho / 2);
		//glutSolidCylinder(radioR, alturaR, slices, stacks);
		glRotatef(90, 0, 1, 0);
		gluQuadricDrawStyle(qobj, GLU_FILL);
		gluCylinder(qobj, radioR, radioR, alturaR, slices, stacks);

		glPushMatrix(); // tapa 1
			gluQuadricDrawStyle(qobj, GLU_FILL);
			gluCylinder(qobj, 0, radioR, 0, slices, stacks);
		glPopMatrix();
		glPushMatrix(); // tapa 2
			glTranslatef(0, 0, 0.2);
			gluQuadricDrawStyle(qobj, GLU_FILL);
			gluCylinder(qobj, 0, radioR, 0, slices, stacks);
		glPopMatrix();

	glPopMatrix();

	//
	GLfloat c = t / (2 * PI); // t in [0, ->)
	GLfloat r = t - 2 * PI*c; // r in [0,2PI)
	GLint gr = 360 * r / (2 * PI); // gr in [0,360)
	//

	/// ** Rueda 3 (quesitos) **
	glPushMatrix();
		glTranslatef(-2 * ancho / 5, -alto / 2, -ancho / 2);
		glRotatef(90, 0, 0, 1);
		glRotatef(gr, 0, 1, 0); //rodar
		f->dibuja();
	glPopMatrix();

	/// ** Rueda 4 (quesitos) **
	glPushMatrix();
		glTranslatef(2 * ancho / 5, -alto / 2, -ancho / 2);
		glRotatef(90 * 3, 0, 0, 1);
		glRotatef(gr, 0, 1, 0); //rodar
		f->dibuja();
	glPopMatrix();
	/// **
}
