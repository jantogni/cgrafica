#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

GLfloat angle = 0.0;
GLfloat alpha1 = 0.0;
GLfloat alpha2 = 0.0;

void cube (void) {
	glRotatef(angle, 1.0, 0.0, 0.0);
	glColor4f(1.0, 0.0, 0.0, alpha1);			//color y alpha del cubo
	glutSolidCube(2);
	glColor4f(0.0, 1.0, 0.0, alpha2);			//color y alpha del cubo
	glutSolidCube(1);
}

void display (void) {
	glClearColor (0.0,0.0,0.0,1.0);
    	glClear (GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);					//habilitar blending
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//funcion de blending
    	glLoadIdentity();  
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	cube();
	glutSwapBuffers();
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case '+':
			angle++;
			break;
		case '-':
			angle--;
			break;
		case '1':
			if (alpha1 >= 0.9) alpha1 = 0.0; else alpha1 += 0.1;
			break;
		case '2':
			if (alpha2 >= 0.9) alpha2 = 0.0; else alpha2 += 0.1;
			break;
		case 27:   // escape
			exit(0);
			break;
    }
}

int main (int argc, char **argv) {
    	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);			//set the alpha buffer
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
    	glutCreateWindow ("Blending Example");
    	glutDisplayFunc (display);
	glutIdleFunc (display);
	glutReshapeFunc (reshape);
	glutKeyboardFunc(keyboard);
    	glutMainLoop ();
    	return 0;
} 
