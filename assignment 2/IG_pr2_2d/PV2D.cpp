#include "PV2D.h"



PV2D::PV2D(GLfloat x, GLfloat y, int pv){
	this->x = x;
	this->y = y;
	this->pv = pv; //1=> punto. 0=>vector
}


PV2D::~PV2D(){}

GLfloat PV2D::getX(){
	return x;

}


GLfloat PV2D::getY(){
	return y;
}
