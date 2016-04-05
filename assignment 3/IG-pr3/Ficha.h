#pragma once
#include "objetocomp3d.h"
#include "Quesito.h"
class Ficha :
	public ObjetoComp3D
{
public:
	Ficha(GLfloat r, GLfloat h, int N);
	~Ficha(void);
	void setColor(GLfloat r, GLfloat g, GLfloat b);
};

