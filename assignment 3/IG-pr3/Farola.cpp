#include "Farola.h"


Farola::Farola(GLfloat h,GLfloat rCil,GLfloat rSph)
{
	
	Cilindro *cil = new Cilindro(rCil, rCil, h-rSph);
	cil->setColor(0,0.5,0);
	cil->rota(-90,new PV3D(1,0,0,0));


	Esfera *sph = new Esfera(rSph);
	sph->setColor(1,1,1);
	sph->traslada(new PV3D(0,h,0,1));
	

	////////////////////

	numHijos = 2;
	hijos = new Objeto3D*[numHijos];

	hijos[0] = cil;
	hijos[1] = sph;
}


Farola::~Farola(void)
{
}
