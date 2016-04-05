#include "Color.h"


Color::Color(void)
{
}

Color::Color(GLfloat r, GLfloat g, GLfloat b){
	red = r;
	green = g;
	blue = b;
}

Color::~Color(void)
{
}

void Color::setColors(GLfloat r, GLfloat g, GLfloat b){
	red = r;
	green = g;
	blue = b;
}
GLfloat Color::getR(){
	return red;
}
GLfloat Color::getG(){
	return green;
}
GLfloat Color::getB(){
	return blue;
}