#include "PV3D.h"

PV3D::PV3D(GLfloat x, GLfloat y, GLfloat z, int pv)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->pv = pv; //1=> punto. 0=>vector
}


PV3D::~PV3D()
{
}

void PV3D::normaliza(){
	GLfloat norma = sqrt(x*x + y*y + z*z);
	x = x / norma;
	y = y / norma;
	z = z / norma;
}
GLfloat PV3D::getNorma(){
	return sqrt(x*x + y*y + z*z);
}
PV3D* PV3D::clona(){
	return new PV3D(x, y, z, pv);
}

GLfloat PV3D::productoEscalar(PV3D* v){
	return x*v->x +
		y*v->y +
		z*v->z;
}

PV3D* PV3D::productoVectorial(PV3D* v){
	return new PV3D(y*v->z - z*v->y,
						z*v->x - x*v->z,
						x*v->y - y*v->x, 0);
}

GLfloat PV3D::getX(){
	return x;
}
GLfloat PV3D::getY(){
	return y;
}
GLfloat PV3D::getZ(){
	return z;
}
PV3D* PV3D::puntoInterm4(PV3D* p1, PV3D* p2, PV3D*p3){
	return new PV3D((x + p1->x + p2->x + p3->x)/4,
		(y + p1->y + p2->y + p3->y)/4,
		(z + p1->z + p2->z + p3->z)/4, 1);
}
PV3D* PV3D::puntoIntermN(PV3D** p, int N){
	GLfloat xx = x;
	GLfloat yy = y;
	GLfloat zz = z;
	for(int i=0;i<N-1;i++){
		xx += p[i]->x;
		yy += p[i]->y;
		zz += p[i]->z;
	}

	return new PV3D(xx/N,yy/N,zz/N,1);
}
