#include "Escena.h"


const GLfloat PI = 3.141592653589;

Escena::Escena(GLfloat carAng, GLfloat mov, int carOpen, int vecesPuerta)
{
	
	// *** AUTOPISTA
	anchoAut = 12;
	altoAut = 1;
	largoAut = 100;

	Autopista *ap = new Autopista(anchoAut,altoAut,largoAut, new Color(0.3,0.3,0.3));
	// ap->setColor(1,1,1); // el color no funciona con setcolor, hemos hecho un nuevo contructor para este tipo de objetos
	


	// *** COCHE
	
	carX = mov*sin(carAng*PI/180);
	carZ = mov*cos(carAng*PI/180);
	camino = 0;

	Coche *car =  new Coche(carAng, camino, carOpen, vecesPuerta); // carX y carZ para el firo de ruedas
	car->traslada(new PV3D(carX,0,carZ,1)); // movimiento
	car->traslada(new PV3D((0.25+0.05)*anchoAut,0,0,1)); // posicion
	car->escala(new PV3D(0.4,0.4,0.4,0));
	car->rota(carAng, new PV3D(0,1,0,0)); // giro
	
	
	


	// *** FAROLAS
	GLfloat espFarola = 0.1*anchoAut;
	//Farola *f1 = new Farola(11*espFarola,0.1*espFarola,0.5*espFarola);

	// array de farolas equiespaciadas
	int numF = 7;
	GLfloat esp = largoAut/(numF*1.0);
	Farola **f = new Farola*[numF];
	for (int i = 0; i<numF;i++){
		f[i] = new Farola(11*espFarola,0.07*espFarola,0.5*espFarola);
		f[i]->traslada(new PV3D(0,0,-numF/2*esp+i*esp,1));
	}
	
	///////////////

	// pruebas

	Esfera *sph = new Esfera(5);
	sph->setColor(1.0, 0.6, 0.0); // naranja
	int num = 10;
	sph->traslada(new PV3D(-num, num, -num,1));

	////////////////////

	numHijos = 3+numF;
	hijos = new Objeto3D*[numHijos];

	hijos[0] = car;
	hijos[1] = ap;
	for (int i = 0; i<numF;i++){
		hijos[2+i] = f[i];
	}
	hijos[numHijos-1] = sph;
}


Escena::~Escena(void)
{
}

GLfloat* Escena::setCar(GLfloat carAng, GLfloat mov, int carOpen, int vecesPuerta){

	// devuelve la matriz de transformacion del coche
	GLfloat x = mov*sin(carAng*PI/180);
	GLfloat z = mov*cos(carAng*PI/180);

	carX += x;
	carZ += z;
	camino += mov;
	// *** COCHE
	Coche *car =  new Coche(carAng, camino, carOpen, vecesPuerta); // carX y carZ para el firo de ruedas
	car->traslada(new PV3D(carX,0,carZ,1)); // movimiento
	car->traslada(new PV3D((0.25+0.05)*anchoAut,0,0,1)); // posicion
	car->escala(new PV3D(0.4,0.4,0.4,0));
	car->rota(carAng, new PV3D(0,1,0,0));
	
	
	
	
	

	hijos[0] = car;
	GLfloat* mm = hijos[0]->getMatrizAfin();

	return mm;
}