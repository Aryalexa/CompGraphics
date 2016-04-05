#include "ObjetoCuadrico.h"


ObjetoCuadrico::ObjetoCuadrico(void)
{

	qobj = gluNewQuadric(); 
	gluQuadricTexture(qobj,true);
	lines = false;
	slices = 30;
	stacks = 30;
}


ObjetoCuadrico::~ObjetoCuadrico(void)
{
}
