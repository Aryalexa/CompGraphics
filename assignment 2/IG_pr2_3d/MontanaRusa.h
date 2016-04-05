#pragma once
#include "Malla.h"
class MontanaRusa :
	public Malla
{
private:

	int nP; //numero de lados del poligono que aproxima la circunferencia
	int nQ; //numero de rodajas que forma el tubo

	int nPuntosPerfil;	//n�mero de puntos en el perfil original
	PV3D** perfil;		//perfil original en el plano XY

	void crearPerfil();

	PV3D* vTangente(GLfloat t);
	PV3D* vBinormal(GLfloat t);
	PV3D* vNormal(GLfloat t);
	void crearMalla4();
	void crearMalla3();

public:
	MontanaRusa(int nP, int nQ);
	~MontanaRusa();
	PV3D* curva(GLfloat t);
	GLfloat* matrizFrenet(GLfloat t);

};
