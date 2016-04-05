#include "Malla.h"



Malla::Malla(int numVertices, PV3D** vertice, int numNormales, PV3D** normal, int numCaras, Cara** cara)
{
	this->numVertices = numVertices;
	this->vertice = vertice;
	this->numNormales = numNormales; //=numCaras, frecuentemente
	this->normal = normal;
	this->numCaras = numCaras;
	this->cara = cara;
}

Malla::Malla()
{
}

Malla::~Malla()
{
}

void Malla::dibuja() {

	for (int i = 0; i<numCaras; i++) {
		glLineWidth(1.0);
		if (lines) glBegin( GL_LINE_LOOP );
		else glBegin( GL_POLYGON );
		for (int j = 0; j< cara[i]->getNumeroVertices(); j++) { //PINTAR CARA
			int iN = cara[i]->getIndiceNormal(j);
			int iV = cara[i]->getIndiceVertice(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			//Si hubiera coordenadas de textura, aquí se suministrarían
			//las coordenadas de textura del vértice j con glTexColor2f(…);

			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
		
	}
	//////
	dibujaNormales();
}




PV3D* Malla::calculoVectorNormalPorNewell(Cara* c){
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat z = 0.0;

	PV3D* vertActual;
	PV3D* vertSig;

	for (int i=0; i < c->getNumeroVertices(); i++){
		vertActual = vertice[c->getIndiceVertice(i)];
		vertSig = vertice[c->getIndiceVertice((i + 1) % c->getNumeroVertices())];
		x += (vertActual->getY() - vertSig->getY())*
			 (vertActual->getZ() + vertSig->getZ());
		y += (vertActual->getZ() - vertSig->getZ())*
			 (vertActual->getX() + vertSig->getX());
		z += (vertActual->getX() - vertSig->getX())*
			 (vertActual->getY() + vertSig->getY());
	}

	PV3D* n = new PV3D(x, y, z, 0);
	n->normaliza();
	return n;
}

void Malla::setLines(bool b){
	lines = b;
}
void Malla::toggleNormales(){
	normales = !normales;
}
void Malla::dibujaNormales(){
	if (normales)
		for (int i = 0; i < numCaras; i++) {

			int num = cara[i]->getNumeroVertices();
			PV3D* v = vertice[cara[i]->getIndiceVertice(0)];// vertice 0
			PV3D** vv = new PV3D*[num - 1];
			for (int j = 1; j < num; j++)
				vv[j - 1] = vertice[cara[i]->getIndiceVertice(j)];// vertices 1..N-1

			/// 1.calcular punto medio
			PV3D* p = v->puntoIntermN(vv, num); //num = 1+len(vv)
			// 2.vector normal
			PV3D* n = normal[cara[i]->getIndiceNormal(0)];

			glLineWidth(1.0);
			glBegin(GL_LINES);
			//glColor3f(0.0, 0.0, 0.0);
			glVertex3f(p->getX(), p->getY(), p->getZ());
			glVertex3f(p->getX()+n->getX(), p->getY()+n->getY(), p->getZ()+n->getZ());
			glEnd();
		}

}
