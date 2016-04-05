#pragma once
#include "objeto3d.h"
class ObjetoComp3D :
	public Objeto3D
{
protected:
	int numHijos;
	Objeto3D** hijos;

public:

	ObjetoComp3D(void);
	~ObjetoComp3D(void);
	void dibuja();
	void setColor(GLfloat r, GLfloat g, GLfloat b);
};

