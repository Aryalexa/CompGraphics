#include "VerticeNormal.h"

VerticeNormal::VerticeNormal(){
}

VerticeNormal::VerticeNormal(int indiceVertice, int indiceNormal)
{
	this->indiceVertice = indiceVertice;
	this->indiceNormal = indiceNormal;
}


VerticeNormal::~VerticeNormal()
{
}

int VerticeNormal::getIndiceVertice(){
	return this->indiceVertice;
}

int VerticeNormal::getIndiceNormal(){
	return this->indiceNormal;
}