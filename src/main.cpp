#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


#include "Directions.h"
#include "Colors.h"
#include "Cube.h"
#include <string>
using std::string;
#include "Matrix.h"

#include <iostream>
using std::cout;
using std::endl;

// g++ main.cpp -lGL -lGLU -lglut
int position_x = -4;
int position_y = 3;
int position_z = -7;
int control_space = 1; //controlador da tecla space

float mat_color[5][5];

float randomf() {
	return ((float)rand())/RAND_MAX;
}

void set_color() {
	for(int i=0;i<5;i++) {
		for(int j=0;j<5;j++) {	
			mat_color[i][j] = randomf();
		}
	}
}

void nCubes(float x, float y, float z) {
	glPushMatrix();	
	for(int j=0; j < 9;j++) {
		glPushMatrix();
		float a = 3.0;

		for(int i = 0; i < 3; i++) {
			//glutWireCube(1.0);	
			//glColor3f(0,0,mat_color[j][i]);
			glutSolidCube(1.0);
			a = 3.0 * mat_color[j][i];
			
			if(a < 1.0 ) {a = 1.0; }
			if(a > 5.0) {a = 4.0; }

			glScalef(1.0, 1.0, 1.0);
			glTranslatef(2.7, 0, 0);	
			glColor3f(mat_color[j][i], mat_color[j][j],mat_color[i][i]);
		}

		//glutWireCube(1.0);	
		//glColor3f(mat_color[j][i],mat_color[j][i],mat_color[j][i]);
		//glColor3f(0.0, 1.0, 0.0);
		glutSolidCube(1.0);	
		glScalef(1.0, 1.0, 1.0);
		glPopMatrix();
		glTranslatef(0, 0, 2.7);
	}

	glPopMatrix();

}

void inicializacao() {
	//cor de fundo eh cinza
	glClearColor(0.8, 0.8, 0.8, 0.8);
	set_color(); // definir cores dos cubos

	glMatrixMode(GL_PROJECTION);
	//alterne e altere as projecoes para alcancar os resultados desejados
	glFrustum(-2, 2, -1, 1, 1.5, 20.0);

	glPushMatrix();

   	glTranslatef(0, 0, 0);
   	glScalef(1.0, 1.0, 1);
   	glutWireCube(1.0);

   	
}

void printModelView() {
	GLfloat v[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, v);
	printf("=========== MODELVIEW ===========\n");
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++)
			printf("%f ", v[j*4+i]);
		printf("\n");
	}
}

void printProjection() {
	GLfloat v[16];
	glGetFloatv(GL_PROJECTION_MATRIX, v);
	printf("=========== PROJECTION ===========\n");
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++)
			printf("%f ", v[j*4+i]);
		printf("\n");
	}

	printf("=========== COLORS ===========\n");
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++)
			printf("%f ", mat_color[i][j]);
		printf("\n");
	}

}

void funcaoDisplay() {
	//mensagem para verificar quando esta funcao eh chamada
	system("clear");
	printf("display\n");
	printModelView();
	printProjection();

	//limpa a tela com a cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//altere gluLookAt para movimentar a camera ao redor da cidade
	//gluLookAt(-4, 3, -4, 0, 0, 0, 0, 1, 0);
	gluLookAt( position_x, position_y, position_z, 3.5, 1, 1, 0, 1, 0);
	
	glColor3f(0, 0, 0);
	//desenhar um grid de cubos esticados verticalmente 
	glutWireCube(1.0);
	
	nCubes(1.2, 0, 0); // desenhar grid de cubos.

	glFlush();

	glutSwapBuffers();

}

void funcaoKeyboard(unsigned char key, int x, int y) {

	if(key == 'q') {
		exit(-1);
	}
	if(key == 32) { // tecla space
		control_space *= -1;
	}
	if(key == 97) { //tecla a
		//position_x += 1;
		if(position_x <= 30) {
			position_x++;
		} else {
			position_x = -4;	
		}
	} 
	if(key == 100) { //tecla d
		//position_x -= 1;
		if(position_x >= -20) {
			position_x--;
		} else {
			position_x = -4;	
		}
	} 
	if(key == 119) { //tecla w
		position_y += 1;
	} 
	if(key == 115) { //tecla s
		position_y -= 1;
	} 
	if(key == 122) { //tecla z
		position_z += 1;
	} 
	if(key == 101) { //tecla e
		position_z -= 1;
	} 

	glutPostRedisplay();
}

int i = 0;
void temporizador() {
	i++;
	if(i == 17) {
		if(control_space > 0) {
			if(position_x <= 30) {
				position_x++;
			} else {
				position_x = -4;	
			}
		} 

		i = 0;
	}

	//funcaoKeyboard();

    glutPostRedisplay();

}

// Função auxiliar para imprimir uma borda qualquer
string edgeToString(int* edge, int size) {
	string resultado = "";
	for (int i = 0; i < size; ++i) {
		resultado += to_string(edge[i]) + " ";
	}
	resultado += '\n';

	return resultado;
}

int main(int argc, char **argv) {

	// Cria um cubo de tamanho 2x2:
	Cube c = Cube(2);

	// Pega a face da frente e imprime as cores dela na tela:
	Matrix* front = c.getFace(Directions::FRONT);
	cout << front->toString() << endl;

	// Também vou imprimir o parente de cima:
	cout << front->getMatrix(Directions::UP)->toString() << endl;

	// Agora, vou imprimir a borda do parente de cima que está ligada à face front:
	cout << edgeToString(front->getParentEdge(Directions::UP), front->getSize()) << endl;

	// Agora, vou rotacionar em sentido horário (por causa do true, se fosse false, era anti-horário) a face da frente, e imprimir novamente:
	// front->rotate(true);
	// cout << front->toString() << endl;

	// srand(time(NULL));
	// glutInit(&argc, argv);
	// glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// glutInitWindowSize(800, 800);
	// glutInitWindowPosition(100, 100);
	// glutCreateWindow("Cubo Mágico");
	// glutKeyboardFunc(funcaoKeyboard);
	// glutDisplayFunc(funcaoDisplay);
	// //glutIdleFunc(temporizador);
	// inicializacao();

	// glutMainLoop();

	return 0;
}

