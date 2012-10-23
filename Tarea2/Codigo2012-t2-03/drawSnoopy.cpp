/*	drawSnoopy.cpp
	this programs draws Snoopy on a window*/

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <fstream>
//#include <windows.h>
#include <sys/stat.h>
using namespace std;

GLsizei wh = 600;
GLsizei ww = 600;
GLsizei swh = 400;
GLsizei sww = 400;
GLfloat xgs = 1, ygs = 1,xgp = 0, ygp = 0; //Global Scale and Global Position for Moving Snoopy
GLfloat xs = 1, ys = 1; //Global Scale for Static Snoopy

GLdouble width = 1.0;		//Definicion del factor de ancho
GLdouble height = 1.0;		//Definicion del factor de alto

GLboolean flat = GL_TRUE;
GLdouble x_snoopy;
GLdouble y_snoopy;

GLdouble x_box;
GLdouble y_box;

GLdouble g_v;

GLdouble zoom;

bool existeArchivo(string nombreArchivo){       
	struct stat stArchivoInfo;
        if(stat(nombreArchivo.c_str(),&stArchivoInfo))
        {       cout << "No se puede abrir el archivo snoopy3.txt" << endl;
                getchar();
                exit(0);
        }
        return true;
}


/* DisplaySnoopy(width scale, 
 *		height scale, 
 *		x position, 
 *		y position
 * ) */ 

void DisplaySnoopy(GLfloat xls, GLfloat yls, GLfloat xlp, GLfloat ylp){       
	char lineFill;
        GLfloat xj, yj;
	GLfloat min_x = 0, min_y = 0; //extremo inferior izquerdo
	GLfloat max_x = 0, max_y = 0; //extremo superior derecho
        int j, nroPuntos;
        fstream inStream;

        existeArchivo("2012-2-cg-snoopy.txt");
        ifstream datos("2012-2-cg-snoopy.txt");
        glClear(GL_COLOR_BUFFER_BIT);
        //glTranslatef(xlp,ylp,0);
	glTranslatef(10,10,0);
        glScalef(5.0*xls,5.0*yls, 1.0);
        do{       
		datos >> nroPuntos >> lineFill;
                if(lineFill == 'l') glBegin(GL_LINE_STRIP);
                else glBegin(GL_POLYGON);
                for(j = 1; j <= nroPuntos; j++){       
			datos >> xj >> yj;
		
			//xj += x_snoopy; 
			//yj += y_snoopy;

                        glVertex2f(xj+x_snoopy, yj+y_snoopy);

			//Se identifican las coordenadas extremas de la figura para poder formar un rectangulo
			if (xj < min_x)
				min_x = xj;
			else if (xj > max_x)
				max_x = xj;
			if (yj < min_y)
				min_y = yj;
			else if (yj > max_y)
				max_y = yj;
                }
                glEnd();
        } while((xj = datos.get()) != EOF);

	//Se dibuja un rectangulo conectando un grupo de vertices con una linea desde el primero al ultimo vertice
	//En este caso el primer y ultimo vertice es el del extremo inferior izquerdo

	min_x += x_box;
	max_x += x_box;
	
	min_y += y_box;
	max_y += y_box;

	glBegin(GL_LINE_STRIP);
		glVertex2f(max_x, max_y);
		glVertex2f(min_x, max_y);
		glVertex2f(min_x, min_y);
		glVertex2f(max_x, min_y);		
		glVertex2f(max_x, max_y);
	glEnd();

	glutSwapBuffers();
}

int staticS;

void specialkeys( GLint key, GLint u, GLint v ){   
	switch (key) {
	case GLUT_KEY_UP:
        	y_snoopy += g_v;
		y_box += g_v;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
        	y_snoopy -= g_v;
		y_box -= g_v;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
        	x_snoopy -= g_v;
		x_box -= g_v;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
	        x_snoopy += g_v;
		x_box += g_v;
		glutPostRedisplay();
		break;
	}
}

void keyboard( GLubyte key, GLint x, GLint y ){   
	switch (key) {
	case 'w':	
		y_box += g_v;
		break;

	case 's':	
		y_box -= g_v;
		break;

	case 'a':	
		x_box -= g_v;
		break;

	case 'd':	
		x_box += g_v;
		break;

	case 'i':	
		zoom += g_v;
		break;

	case 'o':	
		zoom -= g_v;
		break;

	}
}

void displays(void){	
	glMatrixMode(GL_MODELVIEW);
	gluOrtho2D(0.0, (GLdouble)sww * width * zoom, 0.0, (GLdouble)swh * height * zoom); //se aplica un factor a right y top
	DisplaySnoopy((GLfloat)xs/2,(GLfloat)ys/2, (GLfloat)sww/4, (GLfloat)swh/4);
	glutSwapBuffers();
}

void refreshDisplay(void){
        glutSetWindow(staticS);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glutPostRedisplay();
}

void myinit(void){       
	glClearColor(0.0, 0.0, 0.0, 1.0);
        glColor3f(1.0, 1.0, 1.0);
}

void myReshape(int w, int h){       
	glViewport(0, 0, w, h); //New viewport
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

	//se calculan los factores de ajuste de right y top considerando que la imagen no crezca de forma uniforme en ancho y alto
	if(w < h){
		height = 1.0 /((float)w /h);
		width = 1.0;
	}

	if(w > h){
		height = 1.0;
		width = (float)w / h;
	}

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}


/*	Main Loop
	Open window with initial window size, title bar, 
	RGBA display mode, and handle input events.	*/

int main(int argc, char** argv){	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize     (sww, swh); // window size
        glutInitWindowPosition (50, 50); // window position on screen

	staticS=glutCreateWindow("Static Snoopy");
	
    myinit();
	y_snoopy = 0;
	x_snoopy = 0;

	x_box = 0;
	y_box = 0;
	
	g_v = 0.5;   

	zoom = 1;

	glutKeyboardFunc( keyboard );
	glutSpecialFunc(specialkeys);
	glutDisplayFunc(displays); 
	glutReshapeFunc(myReshape);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize     (ww, wh);  // window size
	glutInitWindowPosition (400, 50); // window position on screen

	glutIdleFunc(refreshDisplay);

	glutMainLoop();
}
