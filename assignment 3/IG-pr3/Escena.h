#pragma once
#include "objetocomp3d.h"

#include "Coche.h"
#include "Autopista.h"
#include "Farola.h"

// coche
// autopista
// farola
class Escena :
	public ObjetoComp3D
{
private:
	int anchoAut;
	int altoAut;
	int largoAut;
	GLfloat carX; // posicion coche
	GLfloat carZ; // posicion coche
	GLfloat camino; // para el giro de ruedas
public:
	Escena(GLfloat carAng, GLfloat mov, int carOpen, int vecesPuerta);
	~Escena(void);
	GLfloat* setCar(GLfloat carAng, GLfloat mov, int carOpen, int vecesPuerta);
};

