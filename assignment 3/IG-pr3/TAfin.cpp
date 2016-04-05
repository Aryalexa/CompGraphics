#include "TAfin.h"


TAfin::TAfin(void)
{
	m = new GLfloat[16];

	// guardat la identidad
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glPopMatrix();
}

TAfin::TAfin(GLfloat* mm){
	m = mm;
}


TAfin::~TAfin(void)
{
}

void TAfin::postmultipica(GLfloat* m1){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadMatrixf(m); // carga m como la matrix actual
		glMultMatrixf(m1); // postmultiplica por m1
		glGetFloatv(GL_MODELVIEW_MATRIX, m); // resultado en m
	glPopMatrix();
}

void TAfin::traslada(PV3D* v){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glTranslatef(v->getX(), v->getY(), v->getZ());
		GLfloat m1[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	glPopMatrix();
	postmultipica(m1);
}
void TAfin::escala(PV3D* x){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glScalef(x->getX(), x->getY(), x->getZ());
		GLfloat m1[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	glPopMatrix();
	postmultipica(m1);
}
void TAfin::rota(GLfloat a, PV3D* v){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glRotatef(a, v->getX(), v->getY(), v->getZ());
		GLfloat m1[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	glPopMatrix();
	postmultipica(m1);
}

GLfloat* TAfin::getMatrizAfin(){
	return m;
}