
// WINDOWS
#include <Windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

// APPLE
//#include "screencasts.h"
///////////////////////////////////


#include "Quesito.h"
#include "MontanaRusa.h"
#include "Coche.h"


#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)


// Viewport size
int WIDTH = 500, HEIGHT = 500;

// Viewing frustum parameters
GLdouble xRight = 10, xLeft = -xRight, yTop = 10, yBot = -yTop, N = 1, F = 1000;

// Camera parameters
GLdouble eyeX = 100.0, eyeY = 100.0, eyeZ = 100.0;
GLdouble lookX = 0.0, lookY = 0.0, lookZ = 0.0;
GLdouble upX = 0, upY = 1, upZ = 0;

/* DEC CONTRUCCIONES */
Quesito* q;
MontanaRusa* mr;
Coche* cc;

/*  Various global state */
int toggleAxes = 1;   /* toggle axes on and off */

GLfloat rotate_x = 0;
GLfloat rotate_y = 0;
GLfloat rotate_z = 0;
GLfloat t = 0; // coche


void initGL() {
	glClearColor(0.6f, 0.7f, 0.8f, 1.0);
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);
	//glMaterialf(GL_BACK, GL_SHININESS, 0.1f);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	/* INI CONTRUCCIONES */
	// buildSceneObjects();
	q = new Quesito(20,3,2,6);
	mr = new MontanaRusa(8,50);
	cc = new Coche();


	// Camera set up
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

	// Frustum set up
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xLeft, xRight, yBot, yTop, N, F);

	// Viewport set up
	glViewport(0, 0, WIDTH, HEIGHT);

	// Light0
	glEnable(GL_LIGHT0);
	GLfloat d[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	GLfloat a[] = { 0.3f, 0.3f, 0.3f, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat p[] = { 25.0, 25.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, p);
}

void drawAxes(){
	// Drawing axes
	if (toggleAxes) {
		GLfloat len = 20;

		glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);// rojo X
		glVertex3f(0, 0, 0);
		glVertex3f(len, 0, 0);

		glColor3f(0.0, 1.0, 0.0);// verde Y
		glVertex3f(0, 0, 0);
		glVertex3f(0, len, 0);

		glColor3f(0.0, 0.0, 1.0);// azul Z
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, len);
		glEnd();

	}
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//*********************** D R A W ***************************
	drawAxes();
	/*  Set View Angle */
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glRotatef(rotate_x, 1.0, 0.0, 0.0); /*ADDED*/
		glRotatef(rotate_y, 0.0, 1.0, 0.0); /*ADDED*/
		glRotatef(rotate_z, 0.0, 0.0, 1.0); /*ADDED*/


		//q->dibuja();				// dibuja un queso
		//q->dibujaNquesitos();		//dibuja N quesitos
		glPushMatrix();
		glScalef(2.0, 2.0, 2.0);

		glColor3f(1.0, 0.6, 0.0);	// (naranja)
		mr->dibuja();				//dibuja monta�a rusa
		cc->dibuja(mr->matrizFrenet(t),t);
		glPopMatrix();



	glPopMatrix();


	glFlush();
	glutSwapBuffers();
}

//reshape
void resize(int newWidth, int newHeight) {
	WIDTH = newWidth;
	HEIGHT = newHeight;
	GLdouble RatioViewPort = (float)WIDTH / (float)HEIGHT;
	glViewport(0, 0, WIDTH, HEIGHT);

	GLdouble SVAWidth = xRight - xLeft;
	GLdouble SVAHeight = yTop - yBot;
	GLdouble SVARatio = SVAWidth / SVAHeight;
	if (SVARatio >= RatioViewPort) {
		GLdouble newHeight = SVAWidth / RatioViewPort;
		GLdouble yMiddle = (yBot + yTop) / 2.0;
		yTop = yMiddle + newHeight / 2.0;
		yBot = yMiddle - newHeight / 2.0;
	}
	else {
		GLdouble newWidth = SVAHeight*RatioViewPort;
		GLdouble xMiddle = (xLeft + xRight) / 2.0;
		xRight = xMiddle + newWidth / 2.0;
		xLeft = xMiddle - newWidth / 2.0;
	}


	// project
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xLeft, xRight, yBot, yTop, N, F);

}

void key(unsigned char key, int x, int y){
	bool need_redisplay = true;

	switch (key) {
	case 27:  /* Escape key */
		//continue_in_main_loop = false; // (**)
		// Freeglut's sentence for stopping glut's main loop (*)
		//exit(0); //APPLE
		glutLeaveMainLoop(); //WINDOWS
		break;
	case 'e':
		toggleAxes = 1 - toggleAxes; break;
	case 'a': //<  /*ADDED*/
		rotate_x -= 5; break;
	case 's': //>  /*ADDED*/
		rotate_x += 5; break;
	case 'q': //v  /*ADDED*/
		rotate_y -= 5; break;
	case 'w': //^  /*ADDED*/
		rotate_y += 5; break;
	case 'z': //v  /*ADDED*/
		rotate_z -= 5; break;
	case 'x': //^  /*ADDED*/
		rotate_z += 5; break;
	case 'l':
		q->setLines(true);
		mr->setLines(true); break;
	case 'f':
		q->setLines(false);
		mr->setLines(false); break;
	case 'n':
		q->toggleNormales();
		mr->toggleNormales(); break;
	case 'r':	//run
		t=(t+0.1); break;
	case 'R':	//run
		t=(t-0.1); break;
	default:
		need_redisplay = false;
		break;

	}



	if (need_redisplay)
		glutPostRedisplay();
}



int main(int argc, char *argv[]){
	cout << "Starting console..." << endl;

	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");

	// Callback registration
	glutReshapeFunc(resize);//1
	glutKeyboardFunc(key);//2
	glutDisplayFunc(display);//3

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION); //WINDOWS

	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop();

	// We would never reach this point using classic glut
	system("PAUSE");

	return 0;
}
