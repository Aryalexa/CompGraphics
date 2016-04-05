#pragma once
#include "objetocomp3d.h"
#include "Tablero.h"
#include "CurvaAutopista.h"
class Autopista :
	public ObjetoComp3D
{
public:
	Autopista(int ancho, int alto, int largo);
	Autopista(int ancho, int alto, int largo, Color *color);
	~Autopista(void);
};

