#pragma once
#include "objeto3d.h"
class ObjetoCuadrico :
	public Objeto3D
{
private:
	
protected:
	GLUquadricObj *qobj;
	bool lines;
	int slices;
	int stacks;
public:
	ObjetoCuadrico(void);
	~ObjetoCuadrico(void);
};

