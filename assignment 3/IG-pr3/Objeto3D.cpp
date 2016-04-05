#include "Objeto3D.h"



Objeto3D::Objeto3D(void)
{
	mT = new TAfin();
	color = new Color(0.7,0.7,0.7);
	//sus derivados deben hacer la llamada al base
}

Objeto3D::Objeto3D(Color *c)
{
	mT = new TAfin();
	color = c;
	//sus derivados deben hacer la llamada al base
}


Objeto3D::~Objeto3D(void)
{
}

void Objeto3D::dibuja(){
}

GLfloat* Objeto3D::getMatrizAfin(){
	return mT->getMatrizAfin();
}
TAfin* Objeto3D::getTAfin(){
	return mT;
}

void Objeto3D::traslada(PV3D* v){
	mT->traslada(v);
}
void Objeto3D::escala(PV3D* x){
	mT->escala(x);
}
void Objeto3D::rota(GLfloat a, PV3D* v){
	mT->rota(a, v);
}


void Objeto3D::setColor(GLfloat r, GLfloat g, GLfloat b){
	color->setColors(r, g, b);
}
void Objeto3D::colorea(){
	glColor3f(color->getR(), color->getG(), color->getB());
}
GLfloat Objeto3D::getRed(){
	return color->getR();
}
GLfloat Objeto3D::getGreen(){
	return color->getG();
}
GLfloat Objeto3D::getBlue(){
	return color->getB();
}