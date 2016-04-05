#include "Cubo.h"


Cubo::Cubo()
{
	//Cubo 10x10x10
	//8 vertices
	GLfloat len = 5.0;
	numVertices = 8;
	PV3D** vert = new PV3D*[8]; //cara de abajo en orde + cara de arriba en orden
	vert[0] = new PV3D(0, 0, 0, 1);
	vert[1] = new PV3D(len, 0, 0, 1);
	vert[2] = new PV3D(len, 0, len, 1);
	vert[3] = new PV3D(0, 0, len, 1);
	vert[4] = new PV3D(0, len, 0, 1);
	vert[5] = new PV3D(0, len, len, 1);
	vert[6] = new PV3D(len, len, len, 1);
	vert[7] = new PV3D(len,len, 0, 1);

	numNormales = 6;
	PV3D** norm = new PV3D*[6];
	norm[0] = new PV3D(0, 1, 0, 0);
	norm[1] = new PV3D(0, -1, 0, 0);
	norm[2] = new PV3D(1, 0, 0, 0);
	norm[3] = new PV3D(-1, 0, 0, 0);
	norm[4] = new PV3D(0, 0, 1, 0);
	norm[5] = new PV3D(0, 0, -1, 0);

	numCaras = 6;


	Cara** caracubo = new Cara*[6];
	//cara arriba, normal 0,1,0
	VerticeNormal** vn_0 = new VerticeNormal*[4];
	vn_0[0] = new VerticeNormal(4, 0);
	vn_0[1] = new VerticeNormal(5, 0);
	vn_0[2] = new VerticeNormal(6, 0);
	vn_0[3] = new VerticeNormal(7, 0);
	caracubo[0] = new Cara(4, vn_0);

	//cara abajo, normal 0,-1,0
	VerticeNormal** vn_1 = new VerticeNormal*[4];
	vn_1[0] = new VerticeNormal(0, 1);
	vn_1[1] = new VerticeNormal(1, 1);
	vn_1[2] = new VerticeNormal(2, 1);
	vn_1[3] = new VerticeNormal(3, 1);
	caracubo[1] = new Cara(4, vn_1);

	//cara normal 1,0,0
	VerticeNormal** vn_2 = new VerticeNormal*[4];
	vn_2[0] = new VerticeNormal(1, 2);
	vn_2[1] = new VerticeNormal(7, 2);
	vn_2[2] = new VerticeNormal(6, 2);
	vn_2[3] = new VerticeNormal(2, 2);
	caracubo[2] = new Cara(4, vn_2);

	//cara normal -1,0,0
	VerticeNormal** vn_3 = new VerticeNormal*[4];
	vn_3[0] = new VerticeNormal(0, 3);
	vn_3[1] = new VerticeNormal(3, 3);
	vn_3[2] = new VerticeNormal(5, 3);
	vn_3[3] = new VerticeNormal(4, 3);
	caracubo[3] = new Cara(4, vn_3);

	//cara normal 0,0,1
	VerticeNormal** vn_4 = new VerticeNormal*[4];
	vn_4[0] = new VerticeNormal(2, 4);
	vn_4[1] = new VerticeNormal(6, 4);
	vn_4[2] = new VerticeNormal(5, 4);
	vn_4[3] = new VerticeNormal(3, 4);
	caracubo[4] = new Cara(4, vn_4);

	//cara normal 0,0,-1
	VerticeNormal** vn_5 = new VerticeNormal*[4];
	vn_5[0] = new VerticeNormal(0, 5);
	vn_5[1] = new VerticeNormal(4, 5);
	vn_5[2] = new VerticeNormal(7, 5);
	vn_5[3] = new VerticeNormal(1, 5);
	caracubo[5] = new Cara(4, vn_5);


	vertice = vert;
	normal = norm;
	cara = caracubo;
}


void Cubo::dibuja() {
	// igual que el dibuja de malla pero con los colores


	//int iN = cara[0]->getNumeroVertices();// getIndiceNormalK(1);
	//int iV = cara[0]->getIndiceVertice(1);
	for (int i = 0; i<numCaras; i++) {
		glLineWidth(1.0);
		glBegin(GL_POLYGON); //o glBegin(GL_LINE_LOOP);
		for (int j = 0; j< this->cara[i]->getNumeroVertices(); j++) {//recorrer cara
			int iN = cara[i]->getIndiceNormal(j);
			int iV = cara[i]->getIndiceVertice(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			//Si hubiera coordenadas de textura, aqui se suministraran
			//las coordenadas de textura del vertice j con glTexColor2f(�);


			if (i<2) glColor3f(0.0, 1.0, 0.0); //VERDE Y
			else if (i<4) glColor3f(1.0, 0.0, 0.0); //ROJO X
			else glColor3f(0.0, 0.0, 1.0); //AZUL Z


			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
	}
}



/*
Cubo::Cubo()
{
	//Cubo 10x10x10
	//8 vertices
	numVertices = 4;
	PV3D** vert = new PV3D*[4]; //cara de abajo en orde + cara de arriba en orden
	vert[0] = new PV3D(0, 0, 0, 1);
	vert[1] = new PV3D(10, 0, 0, 1);
	vert[2] = new PV3D(10, 0, 10, 1);
	vert[3] = new PV3D(0, 0, 10, 1);


	numNormales = 1;
	PV3D** norm = new PV3D*[1];
	norm[0] = new PV3D(0, 1, 0, 0);


	numCaras = 1;
	Cara** caracubo = new Cara*[1];

	//cara abajo, nomral 0,-1,0
	VerticeNormal** vn_1 = new VerticeNormal*[4];
	vn_1[0] = new VerticeNormal(0, 0);
	vn_1[1] = new VerticeNormal(1, 0);
	vn_1[2] = new VerticeNormal(2, 0);
	vn_1[3] = new VerticeNormal(3, 0);
	caracubo[0] = new Cara(4, vn_1);



	vertice = vert;
	normal = norm;
	cara = caracubo;
}*/

Cubo::~Cubo()
{
}
