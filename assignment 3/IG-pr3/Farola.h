#pragma once
#include "objetocomp3d.h"
#include "Cilindro.h"
#include "Esfera.h"
class Farola :
	public ObjetoComp3D
{
private:
	
public:
	Farola(GLfloat h,GLfloat rCil,GLfloat rSph);
	~Farola(void);
};

