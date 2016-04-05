#include "Lapiz.h"

const GLdouble PI = 3.141592;
const bool PINTAR = true;

Lapiz::Lapiz(){
	pos = new PV2D(0.0, 0.0, 1);
	dir = 0;
}

Lapiz::Lapiz(PV2D* pos, GLdouble dir){
	this->pos = pos;
	this->dir = dir;
}


Lapiz::~Lapiz(){}

PV2D* Lapiz::getPos(){
	return pos;
}

GLdouble Lapiz::getDir(){
	return dir;
}

void Lapiz::moveTo(PV2D* p, bool draw){
	if(draw){
		glBegin( GL_LINES ) ;
		glVertex2d(pos->getX(), pos->getY());
		glVertex2d(p->getX(), p->getY());
		glEnd() ;
	}
	pos = p;
}

void Lapiz::turnTo(GLdouble a){
	dir = a;
}

void Lapiz::turn(GLdouble a){
	dir += a;
}

void Lapiz::forward(GLdouble dist, bool draw){
	GLfloat x = pos->getX() + dist*cos(dir);
	GLfloat y = pos->getY() + dist*sin(dir);
	
	if(draw){
		glBegin( GL_LINES ) ;
		glVertex2d(pos->getX(), pos->getY());
		glVertex2d(x, y);
		glEnd() ;
	}

	pos = new PV2D(x, y, 1);
}

void Lapiz::dibujaRectangulo(PV2D* o, GLdouble b, GLdouble h){

	moveTo(o, !PINTAR);
	turnTo(0);

	forward(b, PINTAR);
	turn(PI/2);
	forward(h, PINTAR);
	turn(PI/2);
	forward(b, PINTAR);
	turn(PI/2);
	forward(h, PINTAR);

}

void Lapiz::dibujaArco(PV2D* c, GLdouble r, GLdouble a, GLdouble b){
	int N = 50;
	GLdouble bi = b/N; //TODO double??
	GLdouble B = (PI-bi)/2;
	GLdouble _B = PI- B;
	GLdouble ci = 2*r*cos(B);

	moveTo(c,!PINTAR);
	turnTo(a);

	forward(r,!PINTAR);
	turn(_B);

	for(int i=0; i<N; i++){
		forward(ci,PINTAR);
		turn(bi);
	}
}