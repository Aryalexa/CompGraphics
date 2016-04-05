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
		glColor3f(1.0, 5.0, 0.0);
		glVertex2d(pos->getX(), pos->getY());
		glColor3f(0.0, 2.0, 8.0);
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
		glColor3f(4.0, 5.0, 0.0);
		glVertex2d(pos->getX(), pos->getY());
		glColor3f(1.0, 0.0, 7.0);
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

void Lapiz::dibujaPoligono(PV2D* c, GLdouble a, int n, GLdouble l){
	GLdouble bi = 2*PI/n;
	GLdouble B = (PI-bi)/2;
	GLdouble _B = PI- B;
	GLdouble r = (l/2) /(sin(bi/2));

	moveTo(c,!PINTAR);
	turnTo(a);

	forward(r,!PINTAR);
	turn(_B);

	for(int i=0; i<n; i++){
		forward(l,PINTAR);
		turn(bi);
	}
}

void Lapiz::dibujaArco(PV2D* c, GLdouble r, GLdouble a, GLdouble b){
	int N = 50;
	GLdouble bi = b/N; // angulito
	GLdouble B = (PI-bi)/2;
	GLdouble _B = PI- B;
	GLdouble ci = 2*r*cos(B); // ladito

	moveTo(c,!PINTAR);
	turnTo(a);

	forward(r,!PINTAR);
	turn(_B);

	for(int i=0; i<N; i++){
		forward(ci,PINTAR);
		turn(bi);
	}
}

void Lapiz::dibujaEstrellaImpar(PV2D* c, GLdouble a, int n, GLdouble l){
	GLdouble bi = 2*PI/n;
	GLdouble B = (PI-bi)/2;
	GLdouble _B = PI- B;
	GLdouble r = (l/2) /(sin(bi/2));

	moveTo(c,!PINTAR);
	turnTo(a);

	forward(r,!PINTAR);
	turn(_B);

	PV2D *p1,*p2;
	
	for(int i=0; i<n; i++){
		p1 = getPos();
		forward(l,!PINTAR);
		turn(bi);
		forward(l,!PINTAR);
		turn(bi);
		p2 = getPos();
		moveTo(p1,!PINTAR);
		moveTo(p2,PINTAR);
	}
}