// WINDOWS
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

// APPLE
//#include "screencasts.h"
///////////////////////////////////

#include "Camara.h"
#include "Escena.h"
#include "TextureLoader.h"

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
Escena* escena;
GLfloat *mm; // mmm y tt para que la cam siga al coche
TAfin *tt;

/*  Various global state */
int toggleAxes = 1;   /* toggle axes on and off */
int tiles = 0;	 /* toggle tiles on and off */
bool proyOrt = true;
bool proyPer = false;
bool texture = false;


/* lights */
int toggleLight0 = 1;
int toggleLight1 = 0;
int toggleLight2 = 0;
int toggleFaros = 0;
int toggleAmbGlob = 0;
GLfloat *amb;


GLfloat rotate_x = 0;
GLfloat rotate_y = 0;
GLfloat rotate_z = 0;


/* coche */
GLfloat carAng = 0.0;
int carOpen = 0;
GLfloat carMov = 1.0;
GLfloat carIncAng = 10;

void buildSceneObjects(){

	//objects
	escena = new Escena(carAng,0, carOpen,-1);
	mm = escena->setCar(carAng, 0, carOpen,-1);


	// Camera parameters
	GLdouble eyeX=100.0, eyeY=100.0, eyeZ=100.0;
	GLdouble lookX=mm[12], lookY=mm[13], lookZ=mm[14];
	GLdouble upX=0, upY=1, upZ=0;
	cam = new Camara(new PV3D(eyeX, eyeY, eyeZ, 1), new PV3D(lookX, lookY, lookZ, 1), new PV3D(upX, upY, upZ, 0));//lookAt & projection

	//params
	amb = new GLfloat[4];
	
}

void initGL() {	 		 
	glClearColor(0.6f,0.7f,0.8f,1.0);
    glEnable(GL_LIGHTING);    

	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.1f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	//GLfloat amb[] = {0.0,0.0,0.0,1.0}; // negra
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb); // oscuridad total

	buildSceneObjects(); //camara and objects

	// Camera set up
	
	// Frustum set up
   
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

	// Light1 - remota
	glDisable(GL_LIGHT1);
    GLfloat d_e1[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, d_e1);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, d_e1);
    GLfloat a1[]={0.3f,0.3f,0.3f,1.0};
    glLightfv(GL_LIGHT1, GL_AMBIENT, a1);
	GLfloat p1[]={1.0, 1.0, 0.0, 0.0};	 
	glLightfv(GL_LIGHT1, GL_POSITION, p1);
	
	// Light2 -  farola
	glDisable(GL_LIGHT2);

	// Light3 -  faro 1
	glDisable(GL_LIGHT3);
	
	// Light4 -  faro 2
	glDisable(GL_LIGHT4);

	//////////////////////
	// textura

	// leer -> TextureLoader
	unsigned int t_width, t_height;
	unsigned char * data = loadBMPRaw("nube24.bmp", t_width, t_height);

	// Crear un objeto textura (OpenGL texture)
	GLuint textureID;
	glGenTextures(1, &textureID);
	cout << textureID << endl;

	// ligadura
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	

	// envoltura - tiling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// filtrado (magnificar o minificar)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST_MIPMAP_LINEAR
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// textura y color - modulate
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// asociar data leida y objeto textura
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); 
	
	///////////////
	 
 }

void printMan(){
	cout << "A C C I O N E S" << endl;
	cout << " 5 - toggle axes" << endl;
	cout << " t - tiles" << endl;
	cout << " y,Y - zoom" << endl;
	cout << " o,p - cambiar de proyeccion" << endl;
	cout << "ROTACIONES" << endl;
	cout << " a,A - rotar X" << endl;
	cout << " q,Q - rotar Y" << endl;
	cout << " z,Z - rotar Z" << endl;
	cout << "DESPLAZAMIENTO" << endl;
	cout << " 4,6 - desplazamiento horizontal" << endl;
	cout << " 2,8 - desplazamiento vertical" << endl;
	cout << "RECORRIDO EJES" << endl;
	cout << " b,B - recorrido eje X" << endl;
	cout << " n,N - recorrido eje Y" << endl;
	cout << " m,N - recorrido eje Z" << endl;
	cout << "RODEA EJES" << endl;
	cout << " h - gira X" << endl;
	cout << " j - gira Y" << endl;
	cout << " k - gira Z" << endl;
	cout << "VISTAS" << endl;
	cout << " 7 - vista frontal" << endl;
	cout << " 1 - vista lateral" << endl;
	cout << " 3 - vista cenital" << endl;
	cout << " 9 - vista esquina" << endl;
	cout << "MOV CAMARA" << endl;
	cout << " e,E - pitch" << endl;
	cout << " d,D - yaw" << endl;
	cout << " c,C - roll" << endl;
	cout << "COCHE" << endl;
	cout << " r,R - mover coche" << endl;

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
	//GLfloat sc = 2.0;
	
	// Light2
    GLfloat d_e[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, d_e);
	//glLightfv(GL_LIGHT2, GL_SPECULAR, d_e);
    GLfloat a[]={0.3f,0.3f,0.3f,1.0};
    glLightfv(GL_LIGHT2, GL_AMBIENT, a);
	GLfloat p[]={0.0, 13.5, 0.0, 1.0};	//14 
	glLightfv(GL_LIGHT2, GL_POSITION, p);
	// Light 2 foco
	//glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 90);
	//glLightf(GL_LIGHT3, GL_SPOT_EXPONENT,10);
	//GLfloat dirEm[] = {0.0,-1.0,0.0};
	//glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dirEm);


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
			
			
			GLfloat len = 100;
			int ocupa = 100;
			int numLin = 20;
			GLfloat esp = ocupa/(numLin*1.0);

			glBegin(GL_LINES);
			for(int i =0;i<numLin;i++){
				glColor3f(1.0, 0.6, 0.0);	// (naranja)
				glVertex3f(-len/2.0, 0, -ocupa/2 + i*esp);
				glVertex3f( len/2.0, 0, -ocupa/2 + i*esp);
			}
			glEnd();
			
			// dibuja
			escena->dibuja();

		glPopMatrix();

	glPopMatrix();

	//-------------------
	
}




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


void resize(int newWidth, int newHeight) {
	cam->resize(newWidth, newHeight);
	WIDTH= newWidth;
	HEIGHT= newHeight;
	
}

void key(unsigned char key, int x, int y){
	bool need_redisplay = true;
	GLfloat PI=3.141592;
	switch (key) {
		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			// Freeglut's sentence for stopping glut's main loop (*)
			//exit(0); //APPLE
			glutLeaveMainLoop(); //WINDOWS
			break;
		// lights
		case '0':
			toggleLight0 = 1 - toggleLight0; 
			if (toggleLight0) glEnable(GL_LIGHT0); // remota posicional
			else glDisable(GL_LIGHT0);
			break;
		case 'w':
			toggleLight1 = 1 - toggleLight1; 
			if (toggleLight1) glEnable(GL_LIGHT1); // remota direccional
			else glDisable(GL_LIGHT1);
			break;
		case 's':
			toggleLight2 = 1 - toggleLight2; 
			if (toggleLight2) glEnable(GL_LIGHT2); // farola
			else glDisable(GL_LIGHT2);
			break;
		case 'f':
			toggleFaros = 1 - toggleFaros; 
			if (toggleFaros) { glEnable(GL_LIGHT3); glEnable(GL_LIGHT4); }
			else { glDisable(GL_LIGHT3); glDisable(GL_LIGHT4); }
			break;
		case 'x':
			toggleAmbGlob = 1 - toggleAmbGlob; 
			if (toggleAmbGlob) {amb[0]=0;amb[1]=0;amb[2]=0; amb[3]=1.0; } // negro
			else { {amb[0]=0.2;amb[1]=0.2;amb[2]=0.2; amb[3]=1.0; }  }
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb); // oscuridad total
			break;
		// axes
		case '5':
			toggleAxes = 1 - toggleAxes; break;
		// tiling
		case 't':
			tiles = 1 - tiles; break;
		// rotaciones
		case 'a': //< 
			rotate_x -= 5; break;
		case 'A': //>  
			rotate_x += 5; break;
		case 'q': //v  
			rotate_y -= 5; break;
		case 'Q': //^  
			rotate_y += 5; break;
		case 'z': //v  
			rotate_z -= 5; break;
		case 'Z': //^  
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
		//
		case 'r': 
			//carZ += carMov;
			mm = escena->setCar(carAng,carMov,carOpen,-1);

			// actuamos sobre la tranf del coche (mm) para que las rotaciones funcionen
			//tt = new TAfin(); //(mm);
			//tt->rota(rotate_x, new PV3D(1.0, 0.0, 0.0,0));
			//tt->rota(rotate_y, new PV3D(0.0, 1.0, 0.0,0));
			//tt->rota(rotate_z, new PV3D(0.0, 0.0, 1.0,0));
			//tt->postmultipica(mm);// el orden del postmultiplica importa!! tt.m * mm
			//mm = tt->getMatrizAfin();

			cout << "Ang: " << carAng << " - mov:" << carMov << " - movZ:" << carMov*cos(carAng*PI/180) << " - movX:" << carMov*sin(carAng*PI/180) << endl;
			//cout << mm[12] << " " << mm[13] << " " << mm[14] << endl;
			cam->cambiaPos(new PV3D(0,0,0/*carMov*/,1), new PV3D(mm[12], mm[13], mm[14],1));//new PV3D(0,0,carMov,1));//
			
			break;
		case 'R': 
			//carZ -= carMov;
			mm = escena->setCar(carAng,-carMov,carOpen,-1);

			//

			cout << "Ang: " << carAng << " - mov:" << carMov << " - movZ:" << carMov*cos(carAng*PI/180) << " - movX:" << carMov*sin(carAng*PI/180) << endl;
			cam->cambiaPos(new PV3D(0, 0, 0/*-carMov*/, 1), new PV3D(mm[12], mm[13], mm[14], 1));//new PV3D(0,0,-carMov,1));//
			
			break;
		case 'i': // derecha
			//carZ -= 0.5*carMov;
			carAng -= carIncAng;
			mm = escena->setCar(carAng,0,carOpen,-1);

			//

			cout << "Ang: " << carAng << " - mov:" << carMov << " - movZ:" << carMov*cos(carAng*PI/180) << " - movX:" << carMov*sin(carAng*PI/180) << endl;
			cam->cambiaPos(new PV3D(0,0,0/*carMov*/,1), new PV3D(mm[12], mm[13], mm[14],1));//new PV3D(0,0,carMov,1));//
			break;
		case 'u': // izq
			//carZ -= 0.5*carMov;
			carAng += carIncAng;
			mm = escena->setCar(carAng,0,carOpen,-1);

			//

			cout << "Ang: " << carAng << " - mov:" << carMov << " - movZ:" << carMov*cos(carAng*PI/180) << " - movX:" << carMov*sin(carAng*PI/180) << endl;
			//cout << mm[12] << " " << mm[13] << " " << mm[14] << endl;
			cam->cambiaPos(new PV3D(0,0,0/*carMov*/,1), new PV3D(mm[12], mm[13], mm[14],1));//new PV3D(0,0,carMov,1));//
			break;
		case 'l':
			carOpen = 1 - carOpen;
			if (carOpen) for (int i=0;i<8;i++){
				escena->setCar(carAng,0,carOpen,i);
				display();
				Sleep(20);
			}
			else for (int i=7;i>-1;i--){
				escena->setCar(carAng,0,carOpen,i);
				display();
				Sleep(20);
			}
			break;
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
	printMan();

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
