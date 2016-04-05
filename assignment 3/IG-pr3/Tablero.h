#pragma once
#include "objetocomp3d.h"
#include "Cubo.h"

class Tablero :
	public ObjetoComp3D
{
private:

public:
	Tablero(int dimX, int dimY, int dimZ);
	~Tablero(void);
};

