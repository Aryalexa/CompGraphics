#pragma once
#include "objetocomp3d.h"
#include "Chasis.h"
#include "Ficha.h"
#include "Faro.h"
class Coche :
	public ObjetoComp3D
{
public:
	Coche(GLfloat carX, GLfloat camino, int carOpen, int veces);
	~Coche(void);
};

