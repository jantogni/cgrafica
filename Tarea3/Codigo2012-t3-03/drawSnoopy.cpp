#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100

int shapes_number = 0;
bool lights = true;
bool light0 = true;
bool light1 = false;

enum shapeTypes {cube = 1, sphere} type;

GLfloat xpos = 0.0f;
GLfloat ypos = 0.0f;
GLfloat zpos = 0.0f;

GLfloat x_vector[100];
GLfloat y_vector[100];
GLfloat z_vector[100];

GLfloat delta = 0.2f;

void addShape(enum shapeTypes);
void keys(unsigned char , int , int );
void drawShapes();
void reshape (int , int );

struct shape{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat size;
	enum shapeTypes type;
} shapes[N];

void addShape(enum shapeTypes type){
	shapes_number++;

	if(shapes_number == 1){
		shapes[shapes_number-1].x = 0.0f;
		shapes[shapes_number-1].y = 0.0f;
		shapes[shapes_number-1].z = -10.0f;

		shapes[shapes_number-1].r = 20;
		shapes[shapes_number-1].g = 3;
		shapes[shapes_number-1].b = 3;
	}
	else{
		xpos -= delta;
		ypos -= delta;

		shapes[shapes_number-1].x = xpos;
		shapes[shapes_number-1].y = ypos;
		shapes[shapes_number-1].z = zpos;

		shapes[shapes_number-1].r = 0;
		shapes[shapes_number-1].g = 30;
		shapes[shapes_number-1].b = 182;
	}

	shapes[shapes_number-1].size = 1.0f;
	shapes[shapes_number-1].type = type;
}

void keys(unsigned char key, int x, int y){
	switch(key){
		case 'x':
			shapes[shapes_number-1].x -= delta;
			break;

		case 'X':
			shapes[shapes_number-1].x += delta;
			xpos += delta;
			break;

		case 'y':
			shapes[shapes_number-1].y -= delta;
			ypos -= delta;
			break;

		case 'Y':
			shapes[shapes_number-1].y += delta;
			ypos += delta;
			break;

		case 'z':
			shapes[shapes_number-1].z -= delta;
			zpos -= delta;
			break;

		case 'Z':
			shapes[shapes_number-1].z += delta;
			zpos += delta;
			break;

		case 's':
			shapes[shapes_number-1].size -= 0.1f;
			break;

		case 'S':
			shapes[shapes_number-1].size += 0.1f;
			break;

		case '1':
			addShape(cube);
			break;

		case '2':
			addShape(sphere);
			break;

		case '8':
			if (lights){
				glDisable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
				lights = false;
			}
			else{
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
				lights = true;
			}
			break;

		case '9':
			if (light0){
				glDisable(GL_LIGHT0);
				light0 = false;
				if (!light1)
					lights = false;
			}
			else{
				glEnable(GL_LIGHT0);
				light0 = true;
				if(light1)
					lights = true;
			}
			break;

		case '0':
			if (light1){
				glDisable(GL_LIGHT1);
				light1 = false;
				if(!light0)
					lights = false;
			}
			else{
				glEnable(GL_LIGHT1);
				light1 = true;
				if(light0)
					lights = true;
			}
			break;

		case 27:
			exit(0);
			break;
	}
}

void drawShapes(){
	int i=0;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	if (lights){
		if (light0){
			GLfloat position0[] = {10, 10, 5, 0.0f};
			glLightfv(GL_LIGHT0, GL_POSITION, position0);
		}
		if (light1){
			GLfloat position1[] = {-10, 10, 5, 0.0f};
			glLightfv(GL_LIGHT1, GL_POSITION, position1);
		}
	}

	for (i = 0; i < shapes_number; i++){
		glLoadIdentity();
		glColor3f(shapes[i].r,shapes[i].g,shapes[i].b);
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glTranslatef(shapes[i].x, shapes[i].y, shapes[i].z);

		x_vector[i] = shapes[i].x;
		y_vector[i] = shapes[i].y;
		z_vector[i] = shapes[i].z;

		switch(shapes[i].type){
			case cube:
				glutSolidCube(shapes[i].size);
				break;

			case sphere:
				glutSolidSphere(shapes[i].size/2, 100*shapes[i].size, 100*shapes[i].size);
				break;
		}
	}

	glFlush();
}

void reshape (int width, int height){
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main (int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize (640, 480);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Spheres");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat ambient[] = {0.1, 0.1, 0.1, 1.0};
	GLfloat diffuse[] = {0.7, 0.7, 0.7, 1.0};
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	glEnable(GL_LIGHT0);

	GLfloat param[] = {0.5, 0.5, 0.5};
	glLightModelfv(GL_LIGHT_MODEL_COLOR_CONTROL, param);

	addShape(sphere);

	glutDisplayFunc(drawShapes);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutIdleFunc(drawShapes);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
