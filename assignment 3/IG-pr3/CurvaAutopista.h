#pragma once
#include "malla.h"
class CurvaAutopista :
	public Malla
{
private:
	int n;		//numero de veces en que se divide la parte circular 
	GLfloat rIn;	// es el radio interno del anillo
	GLfloat rEx;	// es el radio externo
	GLfloat h;		// altura de la figura
	GLfloat angulo;		// grados en radianes de la curva
public:
	CurvaAutopista(GLfloat radioInt, GLfloat radioExt, GLfloat angulo, GLfloat altura);
	~CurvaAutopista(void);
};

