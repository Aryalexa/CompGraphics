#include "Ficha.h"

const int N = 6;			//numero de quesos
const GLfloat esp = 0.00000005;	//espacio entre los quesos (en radianes)

Ficha::Ficha(int nQ, GLfloat r, GLfloat h)
{
	this->nQ = nQ;	//numero de veces en que se divide la parte circular, numero de vertices a la misma altura (de un queso)
	this->r = r;	//es el radio
	this->h = h;	//es la altura.


	crearPerfil();

	nRot = nQ;						//n�mero de rotaciones de un queso
	//N*nRot	=> numero de rotaciones total
	//nRot*nPuntosPerfil => numero de puntos por queso, sin contar el 0,0,0

	//Tama�os de los arrays
	numVertices = N*nRot*nPuntosPerfil + 1; //un punto (0,0,0) para construir las caras
	numCaras = N * ((nRot - 1)*(nPuntosPerfil - 1) + 2); //dos laterales por queso
	numNormales = numCaras;			//una normal por cara

	//Creaci�n de los arrays
	vertice = new PV3D*[numVertices];
	normal = new PV3D*[numNormales];
	cara = new Cara*[numCaras];


	//crearQueso(0);
	//pensar como hacerlo, crear`puntos de un queso y rotarlo 6 veces


	for (int i = 0; i < N; i++)
		crearQueso(i);


}


Ficha::~Ficha()
{
}

void Ficha::crearPerfil(){
	nPuntosPerfil = 3;						//n�mero de puntos en el perfil original
	perfil = new PV3D*[nPuntosPerfil];	//perfil original en el plano XY

	/** Construir perfil; **/
	perfil[0] = new PV3D(r, 0.0, 0.0, 1); //(abajo)
	perfil[1] = new PV3D(r, h, 0.0, 1);
	perfil[2] = new PV3D(0.0, h, 0.0, 1); //(arriba)
}


void Ficha::crearQueso(int indQueso){

	int nPuntosQueso = nPuntosPerfil*nRot;
	int nCarasQueso = (nRot - 1)*(nPuntosPerfil - 1) + 2;

	/******************* Vertices de la malla ******************/

	//Colocar el perfil rotado como la primera 'capa' de vertices del queso
	for (int j = 0; j < nPuntosPerfil; j++){
		double theta = (2 * 3.14 / N) * indQueso;
		double c = cos(theta);
		double s = sin(theta);
		double x = c*perfil[j]->getX() + s*perfil[j]->getZ();
		double z = -s*perfil[j]->getX() + c*perfil[j]->getZ();
		PV3D* p = new PV3D(x, perfil[j]->getY(), z, 1);
		vertice[indQueso*nPuntosQueso + j] = p;
	}


	for (int i = 1; i<nRot; i++){ //generar el perfil i-�simo
		double theta = (2*3.14 / N) * indQueso + i *(2*3.14 / N - esp) / (double)nRot;
		double c = cos(theta);
		double s = sin(theta);
		for (int j = 0; j<nPuntosPerfil; j++) { //recorrer perfil
			int indice = indQueso*nPuntosQueso + i*nPuntosPerfil + j; //vertice j del perfil i del queso indQueso
			//Transformar el punto j-�simo del perfil original
			double x = c*perfil[j]->getX() + s*perfil[j]->getZ();
			double z = -s*perfil[j]->getX() + c*perfil[j]->getZ();
			PV3D* p = new PV3D(x, perfil[j]->getY(), z, 1);
			vertice[indice] = p;
		} //for
	} //for
	vertice[numVertices - 1] = new PV3D(0.0, 0.0, 0.0, 1);

	/********** Construcci�n de las caras y normales ***********/
	//caras y normales del perfil
	int indiceCara = indQueso*nCarasQueso;
	for (int i = 0; i<nRot - 1; i++){ //unir el perfil i-�simo con el (i+1)%n-�simo
		for (int j = 0; j<nPuntosPerfil - 1; j++) { //esquina inferior-izquierda de una cara
			// indiceCara = i*(m-1) + j;
			int indice = indQueso*nPuntosQueso + i*nPuntosPerfil + j; //vertice j del perfil i del queso indQueso
			VerticeNormal** vn = new VerticeNormal*[4];
			vn[0] = new VerticeNormal(indice, indiceCara);
			vn[1] = new VerticeNormal((indice + nPuntosPerfil) % numVertices, indiceCara);
			vn[2] = new VerticeNormal((indice + 1 + nPuntosPerfil) % numVertices, indiceCara);
			vn[3] = new VerticeNormal(indice + 1, indiceCara);
			cara[indiceCara] = new Cara(4, vn);

			PV3D* n = calculoVectorNormalPorNewell(cara[indiceCara]); //Newell
			normal[indiceCara] = n;
			indiceCara++;
		} //for
	} //for

	//caras y normales laterales

	VerticeNormal** vn_1 = new VerticeNormal*[4];
	vn_1[0] = new VerticeNormal(indQueso*nPuntosQueso + 0, indiceCara);
	vn_1[1] = new VerticeNormal(indQueso*nPuntosQueso + 1, indiceCara);
	vn_1[2] = new VerticeNormal(indQueso*nPuntosQueso + 2, indiceCara);
	vn_1[3] = new VerticeNormal(numVertices - 1, indiceCara);
	cara[indiceCara] = new Cara(4, vn_1);

	PV3D* n1 = calculoVectorNormalPorNewell(cara[indiceCara]); //Newell
	normal[indiceCara] = n1;

	indiceCara++;

	VerticeNormal** vn_2 = new VerticeNormal*[4];
	vn_2[0] = new VerticeNormal((indQueso + 1)*nPuntosQueso - 3, indiceCara);
	vn_2[1] = new VerticeNormal((indQueso + 1)*nPuntosQueso - 2, indiceCara);
	vn_2[2] = new VerticeNormal((indQueso + 1)*nPuntosQueso - 1, indiceCara);
	vn_2[3] = new VerticeNormal(numVertices - 1, indiceCara);
	cara[indiceCara] = new Cara(4, vn_2);

	PV3D* n2 = calculoVectorNormalPorNewell(cara[indiceCara]); //Newell
	normal[indiceCara] = n2;

}

void Ficha::dibuja() {

	int nCarasQueso = (nRot - 1)*(nPuntosPerfil - 1) + 2;


	//int iN = cara[0]->getNumeroVertices();// getIndiceNormal(1);
	//int iV = cara[0]->getIndiceVertice(1);
	for (int i = 0; i<numCaras; i++) {
		glLineWidth(1.0);
		if (lines) glBegin( GL_LINE_LOOP );
		else glBegin( GL_POLYGON );
		for (int j = 0; j< this->cara[i]->getNumeroVertices(); j++) { //PINTAR CARA
			int iN = cara[i]->getIndiceNormal(j);
			int iV = cara[i]->getIndiceVertice(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			//Si hubiera coordenadas de textura, aqu� se suministrar�an
			//las coordenadas de textura del v�rtice j con glTexCoor2f(�);




			if (N == 6){
				if (nCarasQueso * 0 <= i && i < nCarasQueso * 1)
					glColor3f(0.5, 0.0, 1.0);	//marron
				else if (nCarasQueso * 1 <= i && i < nCarasQueso * 2)
					glColor3f(0.0, 1.0, 0.0);	//verde
				else if (nCarasQueso * 2 <= i && i < nCarasQueso * 3)
					glColor3f(1.0, 0.0, 1.0);	//rosa
				else if (nCarasQueso * 3 <= i && i < nCarasQueso * 4)
					glColor3f(1.0, 1.0, 0.0);	//amarillo
				else if (nCarasQueso * 4 <= i && i < nCarasQueso * 5)
					glColor3f(1.0, 0.6, 0.0);	//naranja
				else if (nCarasQueso * 5 <= i && i < nCarasQueso * 6)
					glColor3f(0.0, 1.0, 1.0);	//celeste
			}
			else {
				for (int k = 0; k < N; k++)
					if (nCarasQueso*k<=i && i<nCarasQueso*(k+1.1) ) //queso 1
						glColor3f(0.0, 1.0/(k+1), 0.0);
			}


			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
	}
}
