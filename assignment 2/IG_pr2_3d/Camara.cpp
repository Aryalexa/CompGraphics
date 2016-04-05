#include "Camara.h"

#include <iostream>
using namespace std;

const GLdouble PI = 3.141592;
GLdouble incGiro = 0.05;
GLdouble incMov = PI * 0.5/180.0 ;
const GLfloat CTE = 20; /* realcion entre f(verdaderofactorzoom) y factZ(~1) */
GLfloat f;

Camara::Camara(PV3D *eye, PV3D *look, PV3D *up)
{

	this->eye = eye->clona();
	this->look = look->clona();
	this->up = up->clona();
	actualizaCoordCam();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye->getX(), eye->getY(), eye->getZ(), look->getX(), look->getY(), look->getZ(), up->getX(), up->getY(), up->getZ());


	factZ = 1;
	f=factZ*CTE;
	WIDTH= 500;
	HEIGHT= 500;

	right = 10;
	left = -right;
	top = 10;
	bottom = -top;
	ne = 1;
	fa = 1000;

	aspect = (right-left)/(top-bottom);
	fovy = 25; // arctan(   (right-left)/2   / N  ) = arctan (10 / 1)

	setProyOrt();
	


}


Camara::~Camara(){
}

void Camara::actualizaCoordCam(){
	n = new PV3D(eye->getX()-look->getX(), eye->getY()-look->getY(), eye->getZ()-look->getZ(), 0);
	n->normaliza();
	u = up->productoVectorial(n);
	u->normaliza();
	v = n->productoVectorial(u);
}
/////////////////////////////                P R O Y E C C I O N                  ///////////////////////////////////////
void Camara::setProyOrt(){
	pr_Ort = true;
	pr_Per = false;
	setVolumenVista();
}

void Camara::setProyPers(){
	pr_Per = true;
	pr_Ort = false;
	setVolumenVista();
}

void Camara::setVolumenVista(){
	// Frustum set up

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (pr_Ort)
		glOrtho(left, right, bottom, top, ne, fa);
	else {
		//glFrustum(left, right, bottom, top, ne, fa);
		gluPerspective(fovy, aspect, ne, fa);
	}

}
//////////////////////////////////////              Z O O M                //////////////////////////////////////////////

void Camara::zoomIn(){
	if (pr_Ort) {f+=0.4; factZ = f/CTE;}
	else fovy--;
	zoom();
}
void Camara::zoomOut(){
	if (pr_Ort) {f-=0.4; factZ = f/CTE; }
	else fovy++;
	zoom();
}
void Camara::zoom(){
	if (pr_Ort){
		GLdouble w = WIDTH / f;
		GLdouble h = HEIGHT / f;


		GLdouble yMiddle =( bottom+top )/2.0;
		GLdouble xMiddle= ( left+right )/2.0;

		left =   xMiddle - w / 2.0;
		right =  xMiddle + w / 2.0;
		bottom = yMiddle - h / 2.0;
		top =	 yMiddle + h / 2.0;
	}

	setVolumenVista();
}

////////////////////////////               D E S P L A Z A M I E N T O                 //////////////////////////////////
void Camara::desplazamiento(int up, int down, int ri, int le){ //up = 1 o 0
	GLdouble U = 1/factZ;
	if (pr_Ort){
		if (le){ left -= U;		right -= U; }
		if (ri){ left += U;		right += U; }
		if (up){ top += U;		bottom += U; }
		if (down){ top -= U;		bottom -= U; }
	}
	
	setVolumenVista();
	/*glMatrixMode(GL_PROJECTION); glLoadIdentity(); glOrtho(xLeft, xRight, yBot, yTop, N, F);*/
}

/////////////////////////////                     C A M A R A                       ///////////////////////////////////////

void Camara::recorridoEje(GLfloat x, GLfloat y, GLfloat z){
	PV3D * t = new PV3D(x, y, z, 0);
	t->normaliza();

	GLdouble eyeX = eye->getX() + t->getX();
	GLdouble eyeY = eye->getY() + t->getY();
	GLdouble eyeZ = eye->getZ() + t->getZ();

	eye = new PV3D(eyeX, eyeY, eyeZ, 1);
	actualizaCoordCam();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye->getX(), eye->getY(), eye->getZ(), look->getX(), look->getY(), look->getZ(), up->getX(), up->getY(), up->getZ());
	
}

void Camara::giraX(){
	PV3D *p = new PV3D(0.0, eye->getY(), eye->getZ(), 0);
	PV3D *pY = new PV3D(0.0, 1.0, 0.0, 0);
	GLdouble r = p->getNorma();
	GLdouble aux = acos(p->productoEscalar(pY) / (r*pY->getNorma()));
	GLdouble a = (eye->getZ()>0)? aux : PI+(PI-aux);
	a += incGiro;

	eye = new PV3D(eye->getX(), r*cos(a), r*sin(a), 1);
	giraCam();
}

void Camara::giraY(){
	PV3D *p = new PV3D(eye->getX(), 0.0, eye->getZ(),0);
	PV3D *pZ = new PV3D(0.0, 0.0, 1.0, 0);
	GLdouble r = p->getNorma();
	GLdouble aux = acos(p->productoEscalar(pZ) / (r*pZ->getNorma()));
	GLdouble a = (eye->getX()>0)? aux : PI+(PI-aux);
	a += incGiro;

	eye = new PV3D(r*sin(a), eye->getY(), r*cos(a), 1);
	giraCam();
}

void Camara::giraZ(){
	PV3D *p = new PV3D(eye->getX(), eye->getY(), 0.0, 0);
	PV3D *pX = new PV3D(1.0, 0.0, 0.0, 0);
	GLdouble r = p->getNorma();
	GLdouble aux = acos(p->productoEscalar(pX) / (r*pX->getNorma()));
	GLdouble a = (eye->getY()>0)? aux : PI+(PI-aux);
	a += incGiro;

	eye = new PV3D(r*cos(a), r*sin(a), eye->getZ(), 1);
	giraCam();
}

void Camara::giraCam(){
	actualizaCoordCam();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye->getX(), eye->getY(), eye->getZ(), look->getX(), look->getY(), look->getZ(), up->getX(), up->getY(), up->getZ());
}


void Camara::roll(int sentido){
	// rotacion respecto al eje N
	GLfloat* mM = new GLfloat[16]; // matriz de vista
	GLdouble b = (sentido>0)? incMov/factZ : -incMov/factZ;
	mM[0] = cos(b);		mM[4] = -sin(b);	mM[8]  = 0;		mM[12] = 0;	
	mM[1] = sin(b);		mM[5] = cos(b);		mM[9]  = 0;		mM[13] = 0;
	mM[2] = 0;			mM[6] = 0;			mM[10] = 1;		mM[14] = 0;
	mM[3] = 0;			mM[7] = 0;			mM[11] = 0;		mM[15] = 1;

	//cout<< "-------------GIRO 15 grados (N)" << endl;
	modifVista2(mM);

}

void Camara::yaw(int sentido){
	// rotacion respecto al eje V
	GLfloat* mM = new GLfloat[16]; // matriz de vista
	GLdouble b = (sentido>0)? incMov/factZ : -incMov/factZ;
	mM[0] = cos(b);		mM[4] = 0;		mM[8]  = -sin(b);	mM[12] = 0;	
	mM[1] = 0;			mM[5] = 1;		mM[9]  = 0;			mM[13] = 0;
	mM[2] = sin(b);		mM[6] = 0;		mM[10] = cos(b);	mM[14] = 0;
	mM[3] = 0;			mM[7] = 0;		mM[11] = 0;			mM[15] = 1;
	//cout<< "-------------GIRO 15 grados (V)" << endl;
	modifVista2(mM);
}

void Camara::pitch(int sentido){
	// rotacion respecto al eje U
	GLfloat* mM = new GLfloat[16]; // matriz de vista
	GLdouble b = (sentido>0)? incMov/factZ : -incMov/factZ;
	mM[0] = 1;		mM[4] = 0;			mM[8]  = 0;			mM[12] = 0;	
	mM[1] = 0;		mM[5] = cos(b);		mM[9]  = -sin(b);	mM[13] = 0;
	mM[2] = 0;		mM[6] = sin(b);		mM[10] = cos(b);	mM[14] = 0;
	mM[3] = 0;		mM[7] = 0;			mM[11] = 0;			mM[15] = 1;
	//cout<< "-------------GIRO 15 grados (U)" << endl;
	modifVista2(mM);
}
void Camara::modifVista2(GLfloat *mU1){
	
	// MV modelview
	GLfloat mv[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mv);

	/*
	// V = inv(mU1) 
	GLfloat* V = new GLfloat[16];// globales -> camara'
	PV3D* e = new PV3D(mU1[12], mU1[13],mU1[14], 1);
	V[0] = mU1[0];		V[4] = mU1[1];		V[8]  = mU1[2];		V[12] = -e->productoEscalar(new PV3D(mU1[0], mU1[1],mU1[2], 0));	
	V[1] = mU1[4];		V[5] = mU1[5];		V[9]  = mU1[6];		V[13] = -e->productoEscalar(new PV3D(mU1[4], mU1[5],mU1[6], 0));
	V[2] = mU1[8];		V[6] = mU1[9];		V[10] = mU1[10];	V[14] = -e->productoEscalar(new PV3D(mU1[8], mU1[9],mU1[10], 0));
	V[3] = 0;			V[7] = 0;			V[11] = 0;			V[15] = 1;
	*/
	
	// nuevaV = MV * inv(mM)
	GLfloat* nuevaV = mul(mU1, mv); 


	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(nuevaV);

}
void Camara::modifVista(GLfloat *mM){
	GLfloat* mU = new GLfloat[16]; // camara -> globales
	mU[0] = u->getX();	mU[4] = v->getX();	mU[8]  = n->getX();	mU[12] = eye->getX();
	mU[1] = u->getY();	mU[5] = v->getY();	mU[9]  = n->getY();	mU[13] = eye->getY();
	mU[2] = u->getZ();	mU[6] = v->getZ();	mU[10] = n->getZ();	mU[14] = eye->getZ();
	mU[3] = 0;			mU[7] = 0;			mU[11] = 0;			mU[15] = 1;

	/*
		cout<< "Matriz (u,v,n,e)..." << endl;
		cout<< mU[0] << " " << mU[4] << " " << mU[8] << " " << mU[12]  << endl;
		cout<< mU[1] << " " << mU[5] << " " << mU[9] << " " << mU[13]  << endl;
		cout<< mU[2] << " " << mU[6] << " " << mU[10] << " " << mU[14]  << endl;
		cout<< mU[3] << " " << mU[7] << " " << mU[11] << " " << mU[15]  << endl;
		cout<< "  ...  " << endl;
	*/

	GLfloat Id[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, Id);

	//GLfloat* Id = mul(invOri, mU);
	/*
	cout<< "modelview..." << endl;
	cout<< Id[0] << " " << Id[4] << " " << Id[8] << " " << Id[12]  << endl;
	cout<< Id[1] << " " << Id[5] << " " << Id[9] << " " << Id[13]  << endl;
	cout<< Id[2] << " " << Id[6] << " " << Id[10] << " " << Id[14]  << endl;
	cout<< Id[3] << " " << Id[7] << " " << Id[11] << " " << Id[15]  << endl;
	cout<< "  ...  " << endl;
	*/

	/*
	GLfloat* mV = new GLfloat[16]; // matriz CAM->GL
	mV[0] = u->getX();	mV[4] = u->getY();	mV[8]  = u->getZ();	mV[12] = -eye->productoEscalar(u);	
	mV[1] = v->getX();	mV[5] = v->getY();	mV[9]  = v->getZ();	mV[13] = -eye->productoEscalar(v);
	mV[2] = n->getX();	mV[6] = n->getY();	mV[10] = n->getZ();	mV[14] = -eye->productoEscalar(n);
	mV[3] = 0;			mV[7] = 0;			mV[11] = 0;			mV[15] = 1;
	*/
	// 0. U , camara -> globales

	// 1. U' = M U 
	GLfloat* mU1 = mul(mM, mU); // camara' -> globales
	u = new PV3D(mU1[0], mU1[1],mU1[2], 0);
	v = new PV3D(mU1[4], mU1[5],mU1[6], 0);
	n = new PV3D(mU1[8], mU1[9],mU1[10], 0);
	
	// 2. V' = inv (U')
	GLfloat* V = new GLfloat[16];// globales -> camara'
	PV3D* e = new PV3D(mU1[12], mU1[13],mU1[14], 1);
	V[0] = mU1[0];/**/	V[4] = mU1[1];/**/	V[8]  = mU1[2];/**/	V[12] = -e->productoEscalar(new PV3D(mU1[0], mU1[1],mU1[2], 0));	
	V[1] = mU1[4];		V[5] = mU1[5];		V[9]  = mU1[6];		V[13] = -e->productoEscalar(new PV3D(mU1[4], mU1[5],mU1[6], 0));
	V[2] = mU1[8];		V[6] = mU1[9];		V[10] = mU1[10];	V[14] = -e->productoEscalar(new PV3D(mU1[8], mU1[9],mU1[10], 0));
	V[3] = 0;			V[7] = 0;			V[11] = 0;			V[15] = 1;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(V);

}

GLfloat* Camara::mul(GLfloat *a, GLfloat *b){
	GLfloat* c = new GLfloat[16];
	for (int k=0; k<16; k++)
		c[k] = 0;

	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
			for (int k=0; k<4; k++)
				c[4*j+i] += a[4*k+i]*b[4*j+k];
	
	return c;
}

void Camara::lateral(){
	eye = new PV3D(100.0, 0.0, 0.0, 1);
	up = new PV3D(0.0, 1.0, 0.0, 0);
	giraCam();
}

void Camara::frontal(){
	eye = new PV3D(0.0, 0.0, 100.0, 1);
	up = new PV3D(0.0, 1.0, 0.0, 0);
	giraCam();
}

void Camara::cenital(){
	eye = new PV3D(0.0, 100.0, 0.0, 1);
	up = new PV3D(1.0, 0.0, 0.0, 0);
	giraCam();
}

void Camara::esquina(){
	eye = new PV3D(100.0, 100.0, 100.0, 1);
	up = new PV3D(0.0, 1.0, 0.0, 0);
	giraCam();
}

