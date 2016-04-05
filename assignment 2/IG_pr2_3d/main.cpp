// WINDOWS
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

// APPLE
//#include "screencasts.h"
///////////////////////////////////

#include "MontanaRusa.h"
#include "Camara.h"

#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 500, HEIGHT= 500;

// Viewing frustum parameters
GLdouble xRight=10, xLeft=-xRight, yTop=10, yBot=-yTop, N=1, F=1000;



/* DEC CONTRUCCIONES */
Camara* cam;
MontanaRusa* mr;

/*  Various global state */
int toggleAxes = 1;   /* toggle axes on and off */
int tiles = 0;	 /* toggle tiles on and off */
bool proyOrt = true;
bool proyPer = false;


GLfloat rotate_x = 0;
GLfloat rotate_y = 0;
GLfloat rotate_z = 0;


void buildSceneObjects(){

	// Camera parameters
	GLdouble eyeX=100.0, eyeY=100.0, eyeZ=100.0;
	GLdouble lookX=0.0, lookY=0.0, lookZ=0.0;
	GLdouble upX=0, upY=1, upZ=0;
	cam = new Camara(new PV3D(eyeX, eyeY, eyeZ, 1), new PV3D(lookX, lookY, lookZ, 1), new PV3D(upX, upY, upZ, 0));//lookAt & projection

	//objects
	mr = new MontanaRusa(15,90);
}

void initGL() {	 		 
	glClearColor(0.6f,0.7f,0.8f,1.0);
    glEnable(GL_LIGHTING);    

	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	buildSceneObjects(); //camara ans objects

	// Camera set up
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

	// Frustum set up
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();     
	//glOrtho(xLeft, xRight, yBot, yTop, N, F);

	// Viewport set up
    glViewport(0, 0, WIDTH, HEIGHT);  
	

	 // Light0
    glEnable(GL_LIGHT0);
    GLfloat d[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
    GLfloat a[]={0.3f,0.3f,0.3f,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat p[]={3*25.0, 3*25.0, 0.0, 1.0};	 
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

void drawScene(){
	GLfloat sc = 2.0;
	
	//--------------------

	drawAxes();
	/*  Set View Angle */
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		// Rotacion
		glRotatef(rotate_x, 1.0, 0.0, 0.0); 
		glRotatef(rotate_y, 0.0, 1.0, 0.0); 
		glRotatef(rotate_z, 0.0, 0.0, 1.0);

		// Montaña Rusa
		glPushMatrix();
			
			glScalef(sc, sc, sc);
			glColor3f(1.0, 0.6, 0.0);	// (naranja)
			//glutSolidSphere(3, 30, 30);
			mr->dibuja();				//dibuja montaña rusa
		glPopMatrix();

	glPopMatrix();

	//-------------------
	
}


/*
void setVolumenVista(){
	// Frustum set up
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (proyOrt)
		glOrtho(xLeft, xRight, yBot, yTop, N, F);
	else {
		glFrustum(xLeft, xRight, yBot, yTop, N, F);
		//gluPerspective(fovy, aspect, N, F);
	}
}
*/

void tiling(int nCol){
	GLdouble SVAratio = (xRight - xLeft) / (yTop - yBot);
	GLdouble w = (GLdouble)WIDTH / (GLdouble)nCol;
	GLdouble h = w / SVAratio; // la altura de cada puerto se calcula proporcionalmente

	for (int c = 0; c < nCol; c++){
		GLdouble currentH = 0;
		while ((currentH + h) <= HEIGHT){
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				switch ((nCol*c + (int)(currentH/h) ) % 4)
				{
					case 0: cam->lateral(); break;
					case 1: cam->frontal(); break;
					case 2: cam->cenital(); break;
					case 3: cam->esquina(); break;
					default: break;
				}
				glViewport((GLint)(c*w), (GLint)currentH, (GLint)w, (GLint)h);
				cam->zoom();
				drawScene();
			glPopMatrix();
			currentH += h;
		}
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	if (tiles) tiling(2);
	else  {
		glViewport(0, 0, WIDTH, HEIGHT); //desembaldosar
		cam->zoom();
		drawScene();
	}

	glFlush();
	glutSwapBuffers();
}
/*
void zoom(){
	GLdouble w = WIDTH / factor;
	GLdouble h = HEIGHT / factor;


	GLdouble yMiddle =( yBot+yTop )/2.0;
	GLdouble xMiddle= ( xLeft+xRight )/2.0;

	xLeft =   xMiddle - w / 2.0;
	xRight =  xMiddle + w / 2.0;
	yBot = yMiddle - h / 2.0;
	yTop = yMiddle + h / 2.0;

	setVolumenVista();

	//display();
	//Sleep(50); //miliseconds

}
*/

void resize(int newWidth, int newHeight) {
	WIDTH= newWidth;
	HEIGHT= newHeight;
	GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
	glViewport (0, 0, WIDTH, HEIGHT) ;
   
	GLdouble SVAWidth= xRight-xLeft;
	GLdouble SVAHeight= yTop-yBot;
	GLdouble SVARatio= SVAWidth/SVAHeight;
	if (SVARatio >= RatioViewPort) {		 
		GLdouble newHeight= SVAWidth/RatioViewPort;
		GLdouble yMiddle= ( yBot+yTop )/2.0;
		yTop= yMiddle + newHeight/2.0;
		yBot= yMiddle - newHeight/2.0;
    }
	else {      
		GLdouble newWidth= SVAHeight*RatioViewPort;
		GLdouble xMiddle= ( xLeft+xRight )/2.0;
		xRight= xMiddle + newWidth/2.0;
		xLeft=  xMiddle - newWidth/2.0;
	}

	//TODO, cambiar a cam->protyecta??
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
		case '5':
			toggleAxes = 1 - toggleAxes; break;
		// tiling
		case 't':
			tiles = 1 - tiles; break;
		// rotaciones
		case 'a': //< 
			rotate_x -= 5; break;
		case 's': //>  
			rotate_x += 5; break;
		case 'q': //v  
			rotate_y -= 5; break;
		case 'w': //^  
			rotate_y += 5; break;
		case 'z': //v  
			rotate_z -= 5; break;
		case 'x': //^  
			rotate_z += 5; break;
		// zoom
		case 'y':
			cam->zoomIn(); break;
		case 'Y':
			cam->zoomOut(); break;
		// desplazamientos
		case '4': // <
			cam->desplazamiento(0,0,0,1); break;
		case '6': 
			cam->desplazamiento(0,0,1,0); break;
		case '8': // ^
			cam->desplazamiento(1,0,0,0); break;
		case '2':
			cam->desplazamiento(0,1,0,0); break;
		// proyecciones
		case 'o': 
			cam->setProyOrt(); break;
		case 'p': 
			cam->setProyPers(); break;
		// figura: lines o fill
		case 'l':
			mr->setLines(true); break;
		case 'f':
			mr->setLines(false); break;
		// recorrido ejes
		case 'b': 
			cam->recorridoEje(1.0,0.0,0.0); break;
		case 'B': 
			cam->recorridoEje(-1.0,0.0,0.0); break;
		case 'n':
			cam->recorridoEje(0.0,1.0,0.0); break;
		case 'N': 
			cam->recorridoEje(0.0,-1.0,0.0); break;
		case 'm': 
			cam->recorridoEje(0.0,0.0,1.0); break;
		case 'M':
			cam->recorridoEje(0.0,0.0,-1.0); break;
		// gira ejes
		case 'h': 
			cam->giraX(); break;
		case 'j':
			cam->giraY(); break;
		case 'k': 
			cam->giraZ(); break;
		// vistas
		case '7': 
			cam->frontal(); break;
		case '1':
			cam->lateral(); break;
		case '3': 
			cam->cenital(); break;
		case '9': 
			cam->esquina(); break;
		// Mov camara
		case 'e': 
			cam->pitch(1); break;
		case 'E': 
			cam->pitch(-1); break;
		case 'd':
			cam->yaw(1); break;
		case 'D':
			cam->yaw(-1); break;
		case 'c': 
			cam->roll(1); break;
		case 'C': 
			cam->roll(-1); break;
		default:
			need_redisplay = false;
			break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

int main(int argc, char *argv[]){
	cout<< "Starting console..." << endl;

	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");
    
	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;
    
	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop(); 
  
	// We would never reach this point using classic glut
	system("PAUSE"); 
   
	return 0;
}
