#pragma once
#include "Malla.h"
class Ficha : //formado por N quesos
	public Malla
{
private:

	int nQ;		//numero de veces en que se divide la parte circular (de un queso) *
	GLfloat r;	//es el radio *
	GLfloat h;	//es la altura. *

	int nPuntosPerfil;	//n�mero de puntos en el perfil original
	PV3D** perfil;		//perfil original en el plano XY

	int nRot; //numero de rotaciones por queso (es lo mismo que nQ, cambiar nQ por nRot en todo y prescindir de nQ????)


	// NOTA: los atributos con * son los que se reciben como parametros en el constructor

	void crearPerfil();
	void crearQueso(int indQueso);

public:
	Ficha(int nQ, GLfloat r, GLfloat h);
	~Ficha();

	void dibuja();
};
