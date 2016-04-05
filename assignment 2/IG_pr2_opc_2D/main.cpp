#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>


#include "Lapiz.h"
#include <iostream>
using namespace std;

const GLdouble PHI = 1.618033988; // num aureo
const GLdouble PI = 3.141592;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
double  HEIGHT = 500, WIDTH = HEIGHT*PHI;

// Scene visible area size
GLdouble  yTop = 200.0, yBot = 0, xLeft = 0.0, xRight = yTop*PHI;




int toggleAxes = 0;   /* toggle axes on and off */
int tiles = 0;	 /* toggle tiles on and off */
GLdouble factZ = 1;

Lapiz* lap;
const bool pintar = true;
const GLdouble dist = 300;
const GLdouble B = PHI*dist;
const GLdouble H = dist;

const GLdouble xC = (xRight-xLeft)/2,		yC = (yTop-yBot)/2;
const GLdouble xInfizq = xC - B/2.0,		yInfizq = yC - H/2.0;
const GLdouble xO = xInfizq + (B - H)*(B - H) / (2 * B - H) + H, yO = yInfizq + (-H*H + H*B) / (2 * B - H);
//const GLdouble xO = xInfizq + B*B / (B + H), yO = yInfizq + H*H / (B + H);

GLdouble b = B; // base variable
GLdouble h = H; // altura variabñe
int toggleCentro =  1;

int step = 0;

void drawPoint(PV2D * p){
	glBegin(GL_POINTS);
	glColor3f(0.6f, 0.0f, 1.0f); // morado
	glVertex2d(p->getX(), p->getY());
	glColor3f(0.0f, 0.0f, 1.0f); // azul
	glEnd();
}

void zoom(){
	GLdouble w = WIDTH / factZ;
	GLdouble h = HEIGHT / factZ;

	GLdouble xMid = (toggleCentro)? xC:xO;
	GLdouble yMid = (toggleCentro)? yC:yO;
	//xMid = (xRight-xLeft)/2; yMid = (yTop-yBot)/2;


	xLeft =   xMid - w / 2.0;
	xRight =  xMid + w / 2.0;
	yBot = yMid - h / 2.0;
	yTop = yMid + h / 2.0;

	

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft, xRight, yBot, yTop);

}

void intitGL(){

	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0); 

	glPointSize(4.0);
	glLineWidth(2.0);

	lap = new Lapiz();

	// Viewport
    glViewport(0, 0, WIDTH, HEIGHT);
    
	// Model transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Scene Visible Area
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft, xRight, yBot, yTop); 
	zoom();
 }

void drawAxes(){
	// Drawing axes
	if (toggleAxes) {
		GLfloat len = 200;

		glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);// rojo X
		glVertex2f(xC, yC);
		glVertex2f(xC+len, yC);

		glColor3f(0.0, 1.0, 0.0);// verde Y
		glVertex2f(xC, yC);
		glVertex2f(xC, yC+len);
		glEnd();
	}
}
void drawGoldenSpiral(){

  // ***** DIBUJA CENTRO Y OJO
	glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f); // rojo
		glVertex2d(xC, yC); // centro
		//glVertex2d(xInfizq, yInfizq); // primera izqInf
	
		glColor3f(0.0f, 1.0f, 0.0f); // verde
		glVertex2d(xO,yO); // ojo de dios
	glEnd();
  


  glColor3f(0.0f, 0.0f, 1.0f); // azul

  // ***** DIBUJA RECTANGULO
  PV2D* pIni = new PV2D(xInfizq, yInfizq, 1);
  lap->dibujaRectangulo(pIni, B, H);


  // ***** POSICION PARA EMPEZAR CON LA ESPIRAL
  lap->moveTo(pIni, !pintar);
  lap->turnTo(0);
  lap->forward(B, !pintar);
  //drawPoint(lap->getPos());////
  // |  !


  // ***** DIBUJAR ESPIRAL
  b=B;
  h=H;
  PV2D* p;
  for (int s=0; s<step; s++){
	  switch (s%4)
	  {
	  case 0:
		  //drawPoint(lap->getPos());////
		  p = new PV2D(lap->getPos()->getX()-b+h, lap->getPos()->getY(), 1);
		  lap->moveTo(p, !pintar);
		  lap->turnTo(PI/2);
		  lap->forward(h, pintar);
		  lap->dibujaArco(p,h,PI/2, PI/2);

		  lap->moveTo(p, !pintar);
		  //drawPoint(p);////
		  b = h/PHI;
		  break;
	  case 1:
		  //drawPoint(lap->getPos());////
		  p = new PV2D(lap->getPos()->getX(), lap->getPos()->getY()+h-b, 1);
		  lap->moveTo(p, !pintar);
		  lap->turnTo(0);
		  lap->forward(b, pintar);
		  lap->dibujaArco(p,b,0, PI/2);

		  lap->moveTo(p, !pintar);
		  //drawPoint(p);////
		  h = b/PHI;
		  break;
	  case 2:
		  //drawPoint(lap->getPos());////
		  p = new PV2D(lap->getPos()->getX()+b-h, lap->getPos()->getY(), 1);
		  lap->moveTo(p, !pintar);
		  lap->turnTo(3*PI/2);
		  lap->forward(h, pintar);
		  lap->dibujaArco(p,h,3*PI/2, PI/2);

		  lap->moveTo(p, !pintar);
		  drawPoint(p);////
		  b = h/PHI;
		  break;
	  case 3:
		  //drawPoint(lap->getPos());////
		  p = new PV2D(lap->getPos()->getX(), lap->getPos()->getY()-h+b, 1);
		  lap->moveTo(p, !pintar);
		  lap->turnTo(PI);
		  lap->forward(b, pintar);
		  lap->dibujaArco(p,b,PI, PI/2);

		  lap->moveTo(p, !pintar);
		  //drawPoint(p);////
		  h = b/PHI;
		  break;
	  default:
		  break;
	  }
  }
}

void drawPentagrams(){
	int N = 5;
	GLdouble lado = 300.0;
	glColor3f(0.0f, 0.0f, 1.0f); // azul

	// ***** DIBUJA Pentagono
	PV2D* pIni = new PV2D(xC, yC, 1);
	lap->dibujaPoligono(pIni, 0, N, lado);

	// ***** DIBUJA pentagramas
	for (int s=0; s<step; s++){
		if (s%2 == 0)
			lap->dibujaEstrellaImpar(pIni, 0, N, lado);
		else
			lap->dibujaEstrellaImpar(pIni, PI, N, lado);
		
		lado = lado/(PHI*PHI);
	}
	
}

void drawScene(){
	drawAxes();

  // Scene rendering

  //drawGoldenSpiral();
  drawPentagrams();
}

void tiling(int nCol){
	GLdouble SVAratio = (xRight - xLeft) / (yTop - yBot);
	GLdouble w = (GLdouble)WIDTH / (GLdouble)nCol;
	GLdouble h = w / SVAratio; // la altura de cada puerto se calcula proporcionalmente

	for (int c = 0; c < nCol; c++){
		GLdouble currentH = 0;
		while ((currentH + h) <= HEIGHT+1){
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glViewport((GLint)(c*w), (GLint)currentH, (GLint)w, (GLint)h);
				zoom();
				drawScene();
			glPopMatrix();
			currentH += h;
			
		}
	}
}

void display(void){

  glClear(GL_COLOR_BUFFER_BIT);

	if (tiles) tiling(2);
	else  {
		glViewport(0, 0, WIDTH, HEIGHT); //desembaldosar
		zoom();
		drawScene();
	}

  glFlush();
  glutSwapBuffers();
}


void resize(int newWidth, int newHeight){
  //Resize Viewport
  WIDTH= newWidth;
  HEIGHT= newHeight;
  GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
  glViewport ( 0, 0, WIDTH, HEIGHT ) ;
  
  //Resize Scene Visible Area 
  //Se actualiza el área visible de la escena
  //para que su ratio coincida con ratioViewPort
  GLdouble SVAWidth= xRight-xLeft;
  GLdouble SVAHeight= yTop-yBot;
  GLdouble SVARatio= SVAWidth/SVAHeight;
  if (SVARatio >= RatioViewPort) {
	 // Increase SVAHeight
     GLdouble newHeight= SVAWidth/RatioViewPort;
	 GLdouble yMiddle= ( yBot+yTop )/2.0;
     yTop= yMiddle + newHeight/2.0;
     yBot= yMiddle - newHeight/2.0;
     }
  else {
     //Increase SVAWidth
     GLdouble newWidth= SVAHeight*RatioViewPort;
     GLdouble xMiddle= ( xLeft+xRight )/2.0;
	 xRight= xMiddle + newWidth/2.0;
     xLeft=  xMiddle - newWidth/2.0;
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(xLeft, xRight, yBot, yTop);
}



void desplazamiento(int up, int down, int ri, int le){ // x = 1 o 0
	GLdouble U = 5/factZ;
	
	if (le)  { xLeft -= U;		xRight -= U; }
	if (ri)  { xLeft += U;		xRight += U; }
	if (up)  { yTop += U;		yBot += U;   }
	if (down){ yTop -= U;		yBot -= U;   }
	
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft, xRight, yBot, yTop); 
}

void key(unsigned char key, int x, int y){
 
  bool need_redisplay = true;

  switch (key) {
  case 27:  /* Escape key */
    //continue_in_main_loop = false; // (**)
	glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop (*)
    break;
  case '5':
	toggleAxes = 1 - toggleAxes; break;
  case 'o':
	  toggleCentro = 1 - toggleCentro; zoom();  break;
  // Espiral
  case 'a' :
	step++;
	cout << "s :  " << step << endl;
	break ;
  case 's' :
    step--;
	cout << "s :  " << step << endl;
	break ;
  // zoom
  case '+' :
	factZ *= 1.01; zoom();
	break ;
  case '-' :
    factZ *= 0.99; zoom();
	break ;
  // desplazamiento
  case '8' : // ^
	  desplazamiento(1,0,0,0);
	break ;
  case '2' :
    desplazamiento(0,1,0,0);
	break ;
  case '4' : // <
	desplazamiento(0,0,0,1);
	break ;
  case '6' :
    desplazamiento(0,0,1,0);
	break ;
  // tiling
  case 't':
	tiles = 1 - tiles; break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}



int main(int argc, char *argv[]){
  cout<< "Starting console..." << endl;

  int my_window; //my window's identifier

  //Initialization
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition (50, 100);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
  glutInit(&argc, argv);

  //Window construction
  my_window = glutCreateWindow( "Freeglut 2D-project" );
    
  //Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutDisplayFunc(display);

  //OpenGL basic setting
  intitGL();


  // Freeglut's main loop can be stopped executing (**)
  //while ( continue_in_main_loop )
  //  glutMainLoopEvent();

  // Classic glut's main loop can be stopped after X-closing the window,
  // using the following freeglut's setting (*)
  glutSetOption ( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION ) ;
    
  // Classic glut's main loop can be stopped in freeglut using (*)
  glutMainLoop(); 
  
  // We would never reach this point using classic glut
  system("PAUSE"); 
   
  return 0;
}
