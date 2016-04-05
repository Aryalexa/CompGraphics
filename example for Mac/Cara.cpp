#include "Cara.h"


Cara::Cara(int numVertices, VerticeNormal** arrayVN)
{
	this->numVertices = numVertices;
	this->arrayVN = arrayVN;
}


Cara::~Cara()
{
}

int Cara::getNumeroVertices(){
	return this->numVertices;
}
int Cara::getIndiceNormal(int ind){
	return this->arrayVN[ind]->getIndiceNormal();
}
int Cara::getIndiceVertice(int ind){
	return this->arrayVN[ind]->getIndiceVertice();
}
