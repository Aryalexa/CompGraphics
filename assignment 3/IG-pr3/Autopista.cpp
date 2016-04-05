#include "Autopista.h"

const GLfloat PI = 3.141592653589;
Autopista::Autopista(int x, int y, int z)
{
	Tablero* tab1 = new Tablero(x, y, z);
	Tablero* tab2 = new Tablero(x, y, z);

	tab1->traslada(new PV3D(-(x*0.55), -0.5, 0, 1));
	tab2->traslada(new PV3D(  x*0.55 , -0.5, 0, 1));


	GLfloat esp = 0.1 * x;

	CurvaAutopista* curva1 = new CurvaAutopista(esp/2, esp/2+x, PI, y);
	curva1->traslada(new PV3D(0,-1,-z/2,1)); // z negativa


	CurvaAutopista* curva2 = new CurvaAutopista(esp/2, esp/2+x, PI, y);
	curva2->traslada(new PV3D(0,-1,z/2,1)); // z positiva
	curva2->rota(180, new PV3D(1,0,0,0));

	////////////////

	numHijos = 4;
	hijos = new Objeto3D*[numHijos];

	hijos[0] = tab1;
	hijos[1] = tab2;
	hijos[2] = curva1;
	hijos[3] = curva2;
}

Autopista::Autopista(int x, int y, int z, Color* c)
{
	Tablero* tab1 = new Tablero(x, y, z);
	Tablero* tab2 = new Tablero(x, y, z);

	tab1->traslada(new PV3D(-(x*0.55), -0.5, 0, 1));
	tab2->traslada(new PV3D(  x*0.55 , -0.5, 0, 1));
	
	tab1->setColor(c->getR(), c->getG(), c->getB()); // color
	tab2->setColor(c->getR(), c->getG(), c->getB());

	///////////////////////

	GLfloat esp = 0.1 * x;

	CurvaAutopista* curva1 = new CurvaAutopista(esp/2, esp/2+x, PI, y);
	curva1->traslada(new PV3D(0,-1,-z/2,1)); // z negativa


	CurvaAutopista* curva2 = new CurvaAutopista(esp/2, esp/2+x, PI, y);
	curva2->traslada(new PV3D(0,0,z/2,1)); // z positiva
	curva2->rota(180, new PV3D(1,0,0,0));

	curva1->setColor(c->getR(), c->getG(), c->getB()); // color
	curva2->setColor(c->getR(), c->getG(), c->getB());

	////////////////

	numHijos = 4;
	hijos = new Objeto3D*[numHijos];

	hijos[0] = tab1;
	hijos[1] = tab2;
	hijos[2] = curva1;
	hijos[3] = curva2;
}


Autopista::~Autopista(void)
{
}
