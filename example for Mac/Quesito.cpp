#include "Quesito.h"

const GLfloat PI = 3.14159;
Quesito::Quesito(int nQ, GLfloat r, GLfloat h, int N){

	this->nQ = nQ;	//numero de veces en que se divide la parte circular, numero de vertices a la misma altura
	this->r = r;	//es el radio
	this->h = h;	//es la altura.
	this->N = N;	//caen n quesos en un circulo


	int m = 3;						//número de puntos en el perfil original
	PV3D** perfil = new PV3D*[m];	//perfil original en el plano XY
	
	/** Construir perfil; **/
	perfil[0] = new PV3D(r, 0.0, 0.0, 1); //(abajo)
	perfil[1] = new PV3D(r, h, 0.0, 1);
	perfil[2] = new PV3D(0.0, h, 0.0, 1); //(arriba)
	

	int n = nQ;						//número de rotaciones
	
	//Tamaños de los arrays
	numVertices = n*m + 1;
	numCaras = (n-1)*(m-1) + 2;
	numNormales = numCaras;			//una normal por cara

	//Creación de los arrays
	vertice = new PV3D*[numVertices];
	normal = new PV3D*[numNormales];
	cara = new Cara*[numCaras];
	
	//Colocar el perfil original en la tabla de vertices
	for (int j = 0; j<m; j++) 
		vertice[j] = perfil[j]->clona();

	// 1.Vertices de la malla
	for (int i = 1; i<n; i++){ //generar el perfil i-ésimo
		double theta = i *(2*PI/(N)) / (double)n; //TODO
		double c = cos(theta);
		double s = sin(theta);
		for (int j = 0; j<m; j++) { //recorrer perfil
			int indice = i*m + j; //vertice j del perfil i
			//Transformar el punto j-ésimo del perfil original
			double x = c*perfil[j]->getX() + s*perfil[j]->getZ();
			double z = -s*perfil[j]->getX() + c*perfil[j]->getZ();
			PV3D* p = new PV3D(x, perfil[j]->getY(), z, 1);
			vertice[indice] = p;
		} //for
	} //for
	vertice[numVertices - 1] = new PV3D(0.0, 0.0, 0.0, 1);

	// 2.Construcción de las caras y normales
	int indiceCara = 0;
	for (int i = 0; i<n-1; i++){ //unir el perfil i-ésimo con el (i+1)%n-ésimo
		for (int j = 0; j<m-1; j++) { //esquina inferior-izquierda de una cara
			// indiceCara = i*(m-1) + j;
			int indice = i*m + j;
			VerticeNormal** vn = new VerticeNormal*[4];
			vn[0] = new VerticeNormal(indice, indiceCara);
			vn[1] = new VerticeNormal((indice + m) % numVertices, indiceCara);
			vn[2] = new VerticeNormal((indice + 1 + m) % numVertices, indiceCara);
			vn[3] = new VerticeNormal(indice + 1, indiceCara);
			cara[indiceCara] = new Cara(4, vn);

			PV3D* n = calculoVectorNormalPorNewell(cara[indiceCara]); //Newell
			normal[indiceCara] = n;
			indiceCara++;
		} //for
	} //for

	VerticeNormal** vn_1 = new VerticeNormal*[4];
	vn_1[0] = new VerticeNormal(0, numCaras - 2);
	vn_1[1] = new VerticeNormal(1, numCaras - 2);
	vn_1[2] = new VerticeNormal(2, numCaras - 2);
	vn_1[3] = new VerticeNormal(numVertices - 1, numCaras - 2);
	cara[numCaras-2] = new Cara(4, vn_1);

	PV3D* n1 = calculoVectorNormalPorNewell(cara[numCaras - 2]); //Newell
	normal[numCaras-2] = n1;

	VerticeNormal** vn_2 = new VerticeNormal*[4];
	vn_2[0] = new VerticeNormal(numVertices - 4, numCaras - 1);
	vn_2[3] = new VerticeNormal(numVertices - 3, numCaras - 1);
	vn_2[2] = new VerticeNormal(numVertices - 2, numCaras - 1);
	vn_2[1] = new VerticeNormal(numVertices - 1, numCaras - 1);
	cara[numCaras - 1] = new Cara(4, vn_2);

	PV3D* n2 = calculoVectorNormalPorNewell(cara[numCaras - 1]); //Newell
	normal[numCaras - 1] = n2;

	

}

void Quesito::dibujaNquesitos(){

	glMatrixMode(GL_MODELVIEW);
	for (int i = 0; i < N; i++){
		glPushMatrix();
		glRotatef((360 / N)*i, 0.0, 1.0, 0.0);
		if (N <= 6){
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
		dibuja();
		glPopMatrix();
	}

}