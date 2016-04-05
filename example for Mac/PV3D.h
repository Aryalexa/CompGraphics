#ifndef PV3D_H
#define PV3D_H
/* //WINDOWS
#include <Windows.h>

#include <gl/GL.h>
*/
// APPLE
#include "screencasts.h"

#include <cmath>

class PV3D
{
private:
	GLfloat x, y, z;
	int pv;
public:
	PV3D(GLfloat x, GLfloat y, GLfloat z, int pv);
	~PV3D();

	void normaliza();
	PV3D* clona();
	GLfloat productoEscalar(PV3D* v);
	PV3D* productoVectorial(PV3D* v);
	GLfloat getX(), getY(), getZ();
	PV3D* puntoInterm4(PV3D* p1, PV3D* p2, PV3D*p3);
	PV3D* puntoIntermN(PV3D** p, int N);
};
#endif /* PV3D_H */
