// WINDOWS
#include <Windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>

// APPLE
//#include "screencasts.h"


#include "PV3D.h"
#include "Ficha.h"

class Coche
{
private:
	GLUquadricObj *qobj;
	Ficha* f;
	void dibuja(GLfloat t);

public:
	Coche();
	~Coche();
	void dibuja(GLfloat* m, GLfloat t);
	
};
