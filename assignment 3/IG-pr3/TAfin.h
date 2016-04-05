#pragma once

#include "PV3D.h"
class TAfin
{

private:
	// matrix 4x4
	GLfloat* m; // por columnas!
	
public:
	TAfin(void);
	TAfin(GLfloat* m);
	~TAfin(void);

	void traslada(PV3D* v);
	void escala(PV3D* x);
	void rota(GLfloat a, PV3D* v);

	void postmultipica(GLfloat* m1);

	GLfloat* getMatrizAfin();
};

