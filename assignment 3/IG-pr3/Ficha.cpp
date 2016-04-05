#include "Ficha.h"


Ficha::Ficha(GLfloat r, GLfloat h, int N)
{
	numHijos = N;
	hijos = new Objeto3D*[numHijos];


	Quesito **q = new Quesito*[numHijos];

	for (int i = 0; i < numHijos; i++){
		q[i] = new Quesito(r,h,N);
		q[i]->rota((360/N)*i, new PV3D(0.0, 1.0, 0.0, 0));
		hijos[i]=q[i];
	}
		
		
		
}

void Ficha::setColor(GLfloat r, GLfloat g, GLfloat b){
	for (int i=0; i<numHijos; i++){
		for (int k = 0; k < numHijos; k++)
				if ( k <= i && i<(k + 1.1) ){ //queso 1
					//glColor3f(0.0, 0.0, 1 - 1.0 / (k + 1));
					hijos[i]->setColor(r- 1.0 / (k + 1), g- 1.0 / (k + 1), b- 1.0 / (k + 1));
				}
	}

	/* color
		if (numHijos <= 6){
			if (i == 0) glColor3f(0.5, 0.0, 1.0);	//marron
			if (i == 1) glColor3f(0.0, 1.0, 0.0);	//verde
			if (i == 2) glColor3f(1.0, 0.0, 1.0);	//rosa
			if (i == 3) glColor3f(1.0, 1.0, 0.0);	//amarillo
			if (i == 4) glColor3f(1.0, 0.6, 0.0);	//naranja
			if (i == 5) glColor3f(0.0, 1.0, 1.0);	//celeste
		}
		else {
			for (int k = 0; k < N; k++)
				if (k <= i && i<(k + 1.1)) //queso 1
					glColor3f(0.0, 0.0, 1 - 1.0 / (k + 1));
		}
		*/
}


Ficha::~Ficha(void)
{
}
