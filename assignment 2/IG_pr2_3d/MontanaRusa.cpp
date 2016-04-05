#include "MontanaRusa.h"
#include <iostream>
using namespace std;


const GLfloat r = 1; //radio del poligono (plano XY) de nP lados
const GLfloat PI = 3.14;

const bool DEBUG = false;

MontanaRusa::MontanaRusa(int nP, int nQ)
{
	this->nP = nP; //numero de lados del poligono que aproxima la circunferencia
	this->nQ = nQ;  //numero de rodajas que forma el tubo //de CORTES!! (rodajas = nQ-1)
	lines = false;
	normales = false;
	crearPerfil();

	// ** MARCO DE FRENET **
	// (N(t), B(t), T(t), C(t)) X = Y

	//crearMalla4(); // caras de 4 vertices
	crearMalla3(); // caras de 3 vertices

}

void MontanaRusa::crearPerfil(){
	nPuntosPerfil = nP;						//n�mero de puntos en el perfil original
	perfil = new PV3D*[nPuntosPerfil];	//perfil original en el plano XY

	/** Construir perfil; **/
	double inc = 2 * PI / nPuntosPerfil;

	for (int i = 0; i < nPuntosPerfil; i++)
		perfil[i] = new PV3D(r*cos(2 * PI - i*inc), r*sin(2 * PI - i*inc), 0, 1); //TODO con (-) ?? SI, para que la parte de crear caras vaya bien
}

void MontanaRusa::crearMalla4(){
	//INICIAR MALLA
	//Tama�os de los arrays
	numVertices = nQ*nPuntosPerfil;
	numCaras = (nQ - 1)*(nPuntosPerfil); // (nQ-1)= num de rodajas
	numNormales = numCaras;			//una normal por cara

	//Creaci�n de los arrays
	vertice = new PV3D*[numVertices];
	normal = new PV3D*[numNormales];
	cara = new Cara*[numCaras];


	//CREAR VERTICES
	//transformar: perfil => cortes
	GLfloat t = 0;
	GLfloat inc = (2)*PI / (nQ - 1);
	for (int i = 0; i < nQ; i++){//numero de cortes
		PV3D* n = vNormal(i*inc); //t = i*inc
		PV3D* b = vBinormal(i*inc);
		PV3D* tg = vTangente(i*inc);
		for (int j = 0; j < nPuntosPerfil; j++){//recorrer perfil i
			GLfloat x = n->getX()*perfil[j]->getX() + b->getX()*perfil[j]->getY() + tg->getX()*perfil[j]->getZ() + curva(t)->getX();
			GLfloat y = n->getY()*perfil[j]->getX() + b->getY()*perfil[j]->getY() + tg->getY()*perfil[j]->getZ() + curva(t)->getY();
			GLfloat z = n->getZ()*perfil[j]->getX() + b->getZ()*perfil[j]->getY() + tg->getZ()*perfil[j]->getZ() + curva(t)->getZ();
			vertice[i* nPuntosPerfil + j] = new PV3D(x, y, z, 1);//vertice j del perfil i
		}
		t += inc;
	}

	//CREAR CARAS Y NORMALES
	int indiceCara = 0;
	for (int i = 0; i<nQ - 1; i++){ //unir el perfil i-�simo con el (i+1)%n-�simo
		for (int j = 0; j<nPuntosPerfil; j++) { //esquina inferior-izquierda de una cara

			int indice = i*nPuntosPerfil + j; //vertice j del perfil i
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
}

void MontanaRusa::crearMalla3(){
	// |\/|
	// |/\|
	// INICIAR MALLA
	// Tama�os de los arrays

	numCaras = 4*(nQ - 1)*(nPuntosPerfil); // (nQ-1)= num de rodajas
	numNormales = numCaras;			// una normal por cara
	numVertices = nQ*nPuntosPerfil + (nQ - 1)*(nPuntosPerfil);

	// Creaci�n de los arrays
	vertice = new PV3D*[numVertices];
	normal = new PV3D*[numNormales];
	cara = new Cara*[numCaras];

	// CREAR VERTICES ***************************************************************************************
	// transformar: perfil => cortes
	// 1. vertices del poligono
	GLfloat t = 0;
	GLfloat inc = (2)*PI / (nQ - 1);

	for (int i = 0; i < nQ; i++){ // numero de cortes
		PV3D* n = vNormal(t); // t = i*inc
		PV3D* b = vBinormal(t);
		PV3D* tg = vTangente(t);
		for (int j = 0; j < nPuntosPerfil; j++){ // recorrer perfil i
			GLfloat x = n->getX()*perfil[j]->getX() + b->getX()*perfil[j]->getY() + tg->getX()*perfil[j]->getZ() + curva(t)->getX();
			GLfloat y = n->getY()*perfil[j]->getX() + b->getY()*perfil[j]->getY() + tg->getY()*perfil[j]->getZ() + curva(t)->getY();
			GLfloat z = n->getZ()*perfil[j]->getX() + b->getZ()*perfil[j]->getY() + tg->getZ()*perfil[j]->getZ() + curva(t)->getZ();
			vertice[i*2*nPuntosPerfil + j] = new PV3D(x, y, z, 1); // vertice j del perfil i
			if(DEBUG) cout << "perfil " << i << "   >>  " << i * 2 * nPuntosPerfil + j << "\n";
		}
		t += inc;
	}
	// 2.vertices puntos intermedios

	for (int i = 0; i < nQ - 1; i++){
		for (int j = 0; j<nPuntosPerfil; j++) { // interm entre perfil i y i+1,

			int downL = i * 2 * nPuntosPerfil + j;
			int downR = (i + 1) * 2 * nPuntosPerfil + j;
			int upR = (i + 1) * 2 * nPuntosPerfil + (j + 1) % nPuntosPerfil;
			int upL = i * 2 * nPuntosPerfil + (j + 1) % nPuntosPerfil;
			int interm = i * 2 * nPuntosPerfil + nPuntosPerfil +j;

			PV3D** v = new PV3D*[4];
			v[0] = vertice[downL]; // esquina inferior-izquierda de una cara
			v[1] = vertice[downR];
			v[2] = vertice[upR];
			v[3] = vertice[upL];
			if (DEBUG) cout << "intermedio entre los perfiles " << i << " y " << i + 1 << "     " << j << "\n";
			// calcular intermedio[j] entre perfil i y i+1,
			PV3D* p = v[0]->puntoIntermN(v, 5);//puntoInterm4(v[1], v[2], v[3]);
			// guardar
			vertice[interm] = p;

		} // for
	}
	if (DEBUG) cout << "termina los vertices\n";

	// CREAR CARAS Y NORMALES *********************************************************************************
	int indiceCara = 0;
	for (int i = 0; i<nQ - 1; i++){ //unir el perfil i-�simo con el (i+1)-�simo con 4 triangulos
		if (DEBUG) cout << "dibuja triangulos entre perfiles" << i << " y " << i + 1 << "\n";
		for (int j = 0; j<nPuntosPerfil; j++) {

			int downL = i * 2 * nPuntosPerfil + j;
			int downR = (i + 1) * 2 * nPuntosPerfil + j;
			int upR = (i + 1) * 2 * nPuntosPerfil + (j + 1) % nPuntosPerfil;
			int upL = i * 2 * nPuntosPerfil + (j + 1) % nPuntosPerfil;
			int interm = i * 2 * nPuntosPerfil + nPuntosPerfil+j;


			//crear triangulo 0 (^)
			VerticeNormal** vn_0 = new VerticeNormal*[3];
			vn_0[0] = new VerticeNormal(upL, indiceCara);
			vn_0[1] = new VerticeNormal(interm, indiceCara);
			vn_0[2] = new VerticeNormal(upR, indiceCara);
			cara[indiceCara] = new Cara(3, vn_0); // cara
			PV3D* n_0 = calculoVectorNormalPorNewell(cara[indiceCara]); //Newell
			normal[indiceCara] = n_0; //normal
			indiceCara++;
			if (DEBUG) cout << "     T-0\n";

			//crear triangulo 1 (<)
			VerticeNormal** vn_1 = new VerticeNormal*[3];
			vn_1[0] = new VerticeNormal(upL, indiceCara);
			vn_1[1] = new VerticeNormal(downL, indiceCara);
			vn_1[2] = new VerticeNormal(interm, indiceCara);
			cara[indiceCara] = new Cara(3, vn_1);
			PV3D* n_1 = calculoVectorNormalPorNewell(cara[indiceCara]); //Newell
			normal[indiceCara] = n_1;
			indiceCara++;
			if (DEBUG) cout << "     T-1\n";

			//crear triangulo 2 (v)
			VerticeNormal** vn_2 = new VerticeNormal*[3];
			vn_2[0] = new VerticeNormal(downL, indiceCara);
			vn_2[1] = new VerticeNormal(downR, indiceCara);
			vn_2[2] = new VerticeNormal(interm, indiceCara);
			cara[indiceCara] = new Cara(3, vn_2);
			PV3D* n_2 = calculoVectorNormalPorNewell(cara[indiceCara]); //Newell
			normal[indiceCara] = n_2;
			indiceCara++;
			if (DEBUG) cout << "     T-2\n";

			//crear triangulo 3 (>)
			VerticeNormal** vn_3 = new VerticeNormal*[3];
			vn_3[0] = new VerticeNormal(downR, indiceCara);
			vn_3[1] = new VerticeNormal(upR, indiceCara);
			vn_3[2] = new VerticeNormal(interm, indiceCara);
			cara[indiceCara] = new Cara(3, vn_3);
			PV3D* n_3 = calculoVectorNormalPorNewell(cara[indiceCara]); //Newell
			normal[indiceCara] = n_3;
			indiceCara++;
			if (DEBUG) cout << "     T-3\n";
		} //for
	} //for
}


MontanaRusa::~MontanaRusa(){}


PV3D* MontanaRusa::curva(GLfloat t){
	//t esta en radianes!!!
	return new PV3D(3 * cos(t), 3 * sin(2 * t), 3 * sin(t), 1);
}

PV3D* MontanaRusa::vTangente(GLfloat t){
	PV3D* deriv1 = new PV3D(-3 * sin(t), 6 * cos(2 * t), 3 * cos(t), 0);
	deriv1->normaliza();
	return deriv1;
}

PV3D* MontanaRusa::vBinormal(GLfloat t){
	PV3D* deriv1 = new PV3D(-3 * sin(t), 6 * cos(2 * t), 3 * cos(t), 0);
	PV3D* deriv2 = new PV3D(-3 * cos(t), -12 * sin(2 * t), -3 * sin(t), 0);

	PV3D* bin = deriv1->productoVectorial(deriv2);
	bin->normaliza();

	return bin;
}

PV3D* MontanaRusa::vNormal(GLfloat t){
	PV3D* bin = vBinormal(t);
	PV3D* tang = vTangente(t);

	PV3D* norm = bin->productoVectorial(tang);
	norm->normaliza();

	return norm;
}
GLfloat* MontanaRusa::matrizFrenet(GLfloat t){
	GLfloat* m = new GLfloat[16];
	m[0]= vNormal(t)->getX();
	m[1]= vNormal(t)->getY();
	m[2]= vNormal(t)->getZ();
	m[3]= 0;
	m[4]= vBinormal(t)->getX();
	m[5]= vBinormal(t)->getY();
	m[6]= vBinormal(t)->getZ();
	m[7]= 0;
	m[8]= vTangente(t)->getX();
	m[9]= vTangente(t)->getY();
	m[10]= vTangente(t)->getZ();
	m[11]= 0;
	m[12]= curva(t)->getX();
	m[13]= curva(t)->getY();
	m[14]= curva(t)->getZ();
	m[15]= 1;
	return m;
}
