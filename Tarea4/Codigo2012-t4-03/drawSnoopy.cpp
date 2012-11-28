#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// estructura para guardar las coordenadas de los elementos
typedef struct{
	GLfloat x; // giro
	GLfloat y; // elevacion
	GLfloat z; // profundidad
} posicion;

posicion cono, cubo, esfera; 

// posicion Z de la vista.
double posZ = 45;

// posicion de las luces.
GLfloat light_pos0[] = { 0.0, 0.0, 1.0, 0.0 };
GLfloat light_pos1[] = { 1.0, 0.0, -10.0, 0.0 };
GLfloat light_pos2[] = { -3.0, 1.0, 4.0, 1.0 };
GLfloat light_pos3[] = { 4.5, 5.5, 8.5, 1.0 };

// foco de las luces en "spot"
GLfloat light_spot2[] = {0.0, 0.0, 0.0};
GLfloat light_spot3[] = {1.5, 0.0, 1.0};

//Inicializa las propiedades de la fuente de luz
static void init(void){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
}

void display (void){

	GLfloat light_ambient[] = { 0.75, 0.75, 0.75, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	//Defino un material Rojo
	GLfloat mat_ambient_cono[] = {0.05, 0.05, 0.05, 1.0f}; 
	GLfloat mat_diffuse_cono[] = { 0.8, 0.0, 0.0, 1.0f};
	GLfloat mat_specular_cono[] = {0.9, 0.8, 0.8, 1.0f};

	//Defino un material Azul
	GLfloat mat_ambient_cubo[] = {0.1, 0.1, 0.1, 1.0f}; 
	GLfloat mat_diffuse_cubo[] = {0.0, 0.0, 0.8, 1.0f};
	GLfloat mat_specular_cubo[] = {0.9, 0.9, 0.9, 1.0f};

	//Defino un material Verde
	GLfloat mat_ambient_esfera[] = {0.1, 0.1, 0.1, 1.0f}; 
	GLfloat mat_diffuse_esfera[] = {0.0, 0.7, 0.0, 1.0f};
	GLfloat mat_specular_esfera[] = {0.8, 0.8, 0.8, 1.0f};

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum(-1,1,-1,1,10,1000);
	gluLookAt(0.0,0.0,posZ,0.0,0.0,0.0,0.0,0.001,0.0);
	glMatrixMode( GL_MODELVIEW);
	
	/* Luces */
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_spot2 );
	glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);

	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light_spot3 );
	glLightfv(GL_LIGHT3, GL_POSITION, light_pos3);

	/* esferas de las luces */
	glPushMatrix();
	glTranslatef(light_pos0[0],light_pos0[1],light_pos0[2]);
	glutWireSphere(0.1,16,16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(light_pos1[0],light_pos1[1],light_pos1[2]);
	glutWireSphere(0.1,16,16);
	glPopMatrix();

	/* conos de las luces */
	glPushMatrix();
	glTranslatef(light_pos2[0],light_pos2[1],light_pos2[2]);
	glutWireCone(0.1,0.2,50,10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(light_pos3[0],light_pos3[1],light_pos3[2]);
	glutWireCone(0.1,0.2,50,10);
	glPopMatrix();

	/* Dibuja el cono */
	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient_cono);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse_cono);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular_cono);
	glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
	glPushMatrix ();
	glTranslatef (-1.0, 1.0, 2.0); 
	glRotatef(-45.0, 1.0, 0.0, 0.0);
	glRotated(-cono.x, 1.0, 0.0, 0.0);
	glRotated(-cono.y, 0.0, 1.0, 0.0);
	glRotated(cono.z, 0.0, 0.0, 1.0);
	glutSolidCone(1, 2, 50, 10);
	glPopMatrix();

	/* Dibuja el cubo */
	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient_cubo);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse_cubo);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular_cubo);
	glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
	glPushMatrix ();
	glTranslatef (1.5, 0.0, 1.0); 
	glRotatef(15.0, 0.0, 1.0, 0.0);
	glRotated(-cubo.x, 1.0, 0.0, 0.0);
	glRotated(-cubo.y, 0.0, 1.0, 0.0);
	glRotated(cubo.z, 0.0, 0.0, 1.0);
	glutSolidCube(2.0);
	glPopMatrix ();

	/* Dibuja la esfera */
	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient_esfera);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse_esfera);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular_esfera);
	glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
	glPushMatrix ();
	glTranslatef (-1.0, -1.0, 0.0); 
	glRotated(-esfera.x, 1.0, 0.0, 0.0);
	glRotated(-esfera.y, 0.0, 1.0, 0.0);
	glRotated(esfera.z, 0.0, 0.0, 1.0);
	glutSolidSphere (1.0, 16, 16);
	glPopMatrix ();

	glFlush();
	glutSwapBuffers();
}

void idle(){
	display();
}

void vis(int visible){
        if (visible == GLUT_VISIBLE)
                glutIdleFunc(idle);
        else
                glutIdleFunc(NULL);
}

void reshape(int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
	// inicialmente esta seleccionada la esfera 1
	static int seleccion=0;
	static int estado[]={1, 0, 0, 0};
	switch (key) {
	/* seleccion de las luces y objetos */
		case '1':
			seleccion=0;
			fprintf(stdout, "luz seleccionada: %d\n", seleccion+1);
			break;
		case '2':
			seleccion=1;
                        fprintf(stdout, "luz seleccionada: %d\n", seleccion+1);
                        break;
		case '3':
			seleccion=2;
                        fprintf(stdout, "luz seleccionada: %d\n", seleccion+1);
                        break;
		case '4':
			seleccion=3;
                        fprintf(stdout, "luz seleccionada: %d\n", seleccion+1);
                        break;
		case '5':
			seleccion=4;
			fprintf(stdout, "figura seleccionada: cono\n");
			break;
		case '6':
			seleccion=5;
			fprintf(stdout, "figura seleccionada: cubo\n");
			break;
		case '7':
			seleccion=6;
			fprintf(stdout, "figura seleccionada: esfera\n");
			break;
	/* encendido o apagado de la luz seleccionada */
		case 'L':
		case 'l':
			if(seleccion==0){
				if(estado[0]==0){
					glEnable(GL_LIGHT0);
					estado[0]=1;
					fprintf(stdout, "Luz 1 prendida\n");
				}
				else{
					glDisable(GL_LIGHT0);
					estado[0]=0;
					fprintf(stdout, "Luz 1 apagada\n");
				}
			}
			else if(seleccion==1){
                                if(estado[1]==0){
                                        glEnable(GL_LIGHT1);
                                        estado[1]=1;
					fprintf(stdout, "Luz 2 prendida\n");
                                }
                                else{
                                        glDisable(GL_LIGHT1);
                                        estado[1]=0;
					fprintf(stdout, "Luz 2 apagada\n");
                                }
                        }
			else if(seleccion==2){
                                if(estado[2]==0){
                                        glEnable(GL_LIGHT2);
                                        estado[2]=1;
					fprintf(stdout, "Luz 3 prendida\n");
                                }
                                else{
                                        glDisable(GL_LIGHT2);
                                        estado[2]=0;
					fprintf(stdout, "Luz 3 apagada\n");
                                }
                        }
			else if(seleccion==3){
                                if(estado[3]==0){
                                        glEnable(GL_LIGHT3);
                                        estado[3]=1;
					fprintf(stdout, "Luz 4 prendida\n");
                                }
                                else{
                                        glDisable(GL_LIGHT3);
                                        estado[3]=0;
					fprintf(stdout, "Luz 4 apagada\n");
                                }
                        }
			break;
	/* movimiento en el eje 'Y' del elemento seleccionado */
		case 'w':
		case 'W':
			if(seleccion == 0)
				light_pos0[1] += 0.2;
			else if(seleccion == 1)
				light_pos1[1] += 0.2;
			else if(seleccion == 2)
				light_pos2[1] += 0.2;
			else if(seleccion == 3)
				light_pos3[1] += 0.2;
			else if(seleccion==4) // cono
     				cono.y = cono.y + 10.0f;
			else if(seleccion==5) // cubo
				cubo.y = cubo.y + 10.0f;
			else if(seleccion==6) // esfera
				esfera.y = esfera.y + 10.0f;
			break;
		case 's':
		case 'S':
			if(seleccion == 0)
				light_pos0[1] -= 0.2;
			else if(seleccion == 1)
				light_pos1[1] -= 0.2;
			else if(seleccion == 2)
				light_pos2[1] -= 0.2;
			else if(seleccion == 3)
				light_pos3[1] -= 0.2;
			else if(seleccion==4) // cono
                                cono.y = cono.y - 10.0f;
                        else if(seleccion==5) // cubo
                                cubo.y = cubo.y - 10.0f;
                        else if(seleccion==6) // esfera
                                esfera.y = esfera.y - 10.0f;	
			break;
	/* movimiento en el eje 'X' del elemento seleccionado */
		case 'a':
		case 'A':
			if(seleccion == 0)
				light_pos0[0] -= 0.2;
			else if(seleccion == 1)
				light_pos1[0] -= 0.2;
			else if(seleccion == 2)
				light_pos2[0] -= 0.2;
			else if(seleccion == 3)
				light_pos3[0] -= 0.2;
			else if(seleccion==4) // cono
                                cono.x = cono.x - 10.0f;
                        else if(seleccion==5) // cubo
                                cubo.x = cubo.x - 10.0f;
                        else if(seleccion==6) // esfera
                                esfera.x = esfera.x - 10.0f;
                        break;
		case 'd':
		case 'D':
			if(seleccion == 0)
				light_pos0[0] += 0.2;
			else if(seleccion == 1)
				light_pos1[0] += 0.2;
			else if(seleccion == 2)
				light_pos2[0] += 0.2;
			else if(seleccion == 3)
				light_pos3[0] += 0.2;
			else if(seleccion==4) // cono
                                cono.x = cono.x + 10.0f;
                        else if(seleccion==5) // cubo
                                cubo.x = cubo.x + 10.0f;
                        else if(seleccion==6) // esfera
                                esfera.x = esfera.x + 10.0f;
                        break;
	/* movimiento en el eje 'Z' del elemento seleccionado */
		case 'q':
		case 'Q':
			if(seleccion == 0)
				light_pos0[2] -= 0.2;
			else if(seleccion == 1)
				light_pos1[2] -= 0.2;
			else if(seleccion == 2)
				light_pos2[2] -= 0.2;
			else if(seleccion == 3)
				light_pos3[2] -= 0.2;
			else if(seleccion==4) // cono
                                cono.z = cono.z - 10.0f;
                        else if(seleccion==5) // cubo
                                cubo.z = cubo.z - 10.0f;
                        else if(seleccion==6) // esfera
                                esfera.z = esfera.z - 10.0f;
                        break;
		case 'e':
		case 'E':
			if(seleccion == 0)
				light_pos0[2] += 0.2;
			else if(seleccion == 1)
				light_pos1[2] += 0.2;
			else if(seleccion == 2)
				light_pos2[2] += 0.2;
			else if(seleccion == 3)
				light_pos3[2] += 0.2;
			if(seleccion==4) // cono
                                cono.z = cono.z + 10.0f;
                        else if(seleccion==5) // cubo
                                cubo.z = cubo.z + 10.0f;
                        else if(seleccion==6) // esfera
                                esfera.z = esfera.z + 10.0f;
                        break;
	/* acercar o alejar la escena */
		case 'z':
			posZ -= 2;
			break;
		case 'Z':
			posZ += 2;
			break;
	/* Salida del programa */
		case 27:
			exit(EXIT_SUCCESS);
			break;
	}
	display();
}

int main(int argc, char **argv){
	/* inicializacion de los objetos */
	cono.x=cubo.x=esfera.x=-20.0f;
	cono.y=cubo.y=esfera.y=10.0f;
	cono.z=cubo.z=esfera.z=10.0f;

	glutInitWindowSize(700, 700);
	glutInitWindowPosition(200,50);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Lucecita, por rcovarru y rtobar");
	init();

	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutVisibilityFunc(vis);
	glutMainLoop();
	return 0;
}
