#pragma once
#include "PV3D.h"

// WINDOWS
#include <gl/GLU.h>

// APPLE
//#include "screencasts.h"

#include <cmath>

class Camara
{
private:
	// Orientacion & sist coord de camara
	PV3D *eye, *look, *up, *u, *v, *n;

	// Dim de VV
	GLdouble left, right, top, bottom, ne, fa, fovy, aspect;

	int WIDTH, HEIGHT;

	bool pr_Ort;
	bool pr_Per;
	void setVolumenVista();
	
	
	GLdouble factZ;
	

	void actualizaCoordCam();
	void giraCam();
	void modifVista(GLfloat *mM);
	void modifVista2(GLfloat *mM);
	GLfloat* mul(GLfloat *a, GLfloat *b);

public:
	Camara(PV3D *eye, PV3D *look, PV3D *up);
	~Camara();
	

	void setProyOrt();
	void setProyPers();
	
	void zoomIn();
	void zoomOut();
	void zoom();
	
	void desplazamiento(int up, int down, int ri, int le);

	void recorridoEje(GLfloat x, GLfloat y, GLfloat z);

	void giraX();
	void giraY();
	void giraZ();

	void roll(int sentido);
	void yaw(int sentido);
	void pitch(int sentido);

	void lateral();
	void frontal();
	void cenital();
	void esquina();

	
};

