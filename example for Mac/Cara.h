#pragma once

#include "VerticeNormal.h"
class Cara
{
private:
	int numVertices;
	VerticeNormal** arrayVN;
public:
	Cara(int numVertices, VerticeNormal** arrayVN);
	~Cara();
	int getNumeroVertices();
	int getIndiceNormal(int vert);
	int getIndiceVertice(int vert);
};

