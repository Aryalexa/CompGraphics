#include "Coche.h"

const GLfloat PI = 3.141592;

Coche::Coche(GLfloat carAng, GLfloat camino, int carOpen, int veces)
{
	/** 
	* TODO : usar carOpen (puertas abiertas (1) o cerradas(0))
	* carX, carZ : la posicion del coche nos dira la rotacion de la ruedas
	*/
	 

	GLfloat radioR = 2; // de las ruedas
	GLfloat alturaR = 2; // de las ruedas
	GLfloat ancho = 8;// x
	GLfloat alto = 4;// y
	GLfloat largo = 16;// z
	GLfloat anchPuerta = ancho/20;
	int VECES = 8;
	GLfloat angPuertaAbierta = 60/(VECES-1);
	
	
	// chasis

	Chasis *ch = new Chasis(); // el chasis no incluye puertas
	ch->setTexture(1);
	ch->traslada(new PV3D(0, alto/5 + radioR*2, 0, 1)); // no lo tiene chasis
	ch->escala(new PV3D(ancho, alto*1.5, largo, 0)); // no lo tiene chasis
	ch->setColor(0,0.6,0.9); // azul claro

	// puertas

	Cubo *puerta1 = new Cubo();
	// v movimiento progresivo
	puerta1->traslada(new PV3D((ancho+anchPuerta)/2,0,largo/4,1));// vuelve +z/2
	if(veces>=0) puerta1->rota(-(veces*angPuertaAbierta), new PV3D(0,1,0,0)); //gira -60
	puerta1->traslada(new PV3D(-(ancho+anchPuerta)/2,0,-largo/4,1));//-z/2
	// ^ movimiento
	puerta1->traslada(new PV3D((ancho+anchPuerta)/2, alto/5+radioR*2, 0, 1));// x positivo
	puerta1->escala(new PV3D(anchPuerta, alto*1.5, largo/2,0));
	puerta1->setColor(0,0.6,0.9); // azul claro
	

	Cubo *puerta2 = new Cubo();
	// v movimiento progresivo
	puerta2->traslada(new PV3D(-(ancho+anchPuerta)/2,0,largo/4,1));// vuelve +z/2
	if(veces>=0) puerta2->rota((veces*angPuertaAbierta), new PV3D(0,1,0,0)); //gira -60
	puerta2->traslada(new PV3D((ancho+anchPuerta)/2,0,-largo/4,1));//-z/2
	// ^ movimiento
	puerta2->traslada(new PV3D(-(ancho+anchPuerta)/2, alto/5+radioR*2, 0, 1));// x negativo
	puerta2->escala(new PV3D(anchPuerta, alto*1.5, largo/2,0));
	puerta2->setColor(0,0.6,0.9); // azul claro

	// faros

	Faro *faro1 = new Faro(0,radioR/2.5, radioR/1.9, alturaR/4);//(1,2,1);
	faro1->traslada(new PV3D(1.5*ancho/5, radioR*2, largo/2, 1)); // x positivo
	
	Faro *faro2 = new Faro(1,radioR/2.5, radioR/1.9, alturaR/4);//(1,2,1);
	faro2->traslada(new PV3D(-1.5*ancho/5, radioR*2, largo/2, 1)); // x negativo


	// ruedas

	Ficha *r1 = new Ficha(radioR,alturaR,6);
	r1->traslada(new PV3D(-2*ancho/6, -alto/2+radioR*2, -ancho/2,1));
	r1->rota(90,new PV3D(0,0,1,0));
	r1->rota(camino*180/radioR, new PV3D(0,-1,0,0)); // rodar
	r1->setColor(1,0,0); // rojo

	Ficha *r2 = new Ficha(radioR,alturaR,6);
	r2->traslada(new PV3D(2*ancho/6, -alto/2+radioR*2, -ancho/2,1));
	r2->rota(90*3,new PV3D(0,0,1,0));
	r2->rota(camino*180/radioR, new PV3D(0,1,0,0)); // rodar
	r2->setColor(0,1,1); // turquesa

	Ficha *r3 = new Ficha(radioR,alturaR,6);
	r3->traslada(new PV3D(-2*ancho/6, -alto/2+radioR*2, ancho/2,1));
	r3->rota(90,new PV3D(0,0,1,0)); 
	r3->rota(camino*180/radioR, new PV3D(0,-1,0,0)); // rodar
	r3->setColor(1,0,1); // rosa

	Ficha *r4 = new Ficha(radioR,alturaR,6);
	r4->traslada(new PV3D(2*ancho/6, -alto/2+radioR*2, ancho/2,1));
	r4->rota(90*3,new PV3D(0,0,1,0));
	r4->rota(camino*180/radioR, new PV3D(0,1,0,0)); // rodar
	r4->setColor(1,1,0); // amarillo



	//////////////////////////////


	numHijos = 9;
	hijos = new Objeto3D*[numHijos];

	hijos[0] = ch;
	hijos[1] = r1;
	hijos[2] = r2;
	hijos[3] = r3;
	hijos[4] = r4;
	hijos[5] = faro1;
	hijos[6] = faro2;
	hijos[7] = puerta1;
	hijos[8] = puerta2;

	
	
}


Coche::~Coche(void)
{
}
