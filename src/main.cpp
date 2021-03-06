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

int position_x = -5;
int position_y = -5;
int position_z = 5;
int num_movements = 0; //número de movimentos
float theta;
bool control_space = false; //controlador da tecla space
bool control_orientation = true; //sentido horario
bool control_3d = false; //visualização do cubo 3d ou 2d.

int especMaterial = 60;

Cube* cubo = new Cube(3);

const char* filename;
int width, height;
GLuint texid1 = -777;


unsigned char * readPPM(const char* filename) {
    FILE *arq = fopen(filename, "r");
    char format[3];
    int max;
    unsigned char* pixels =NULL;
    if(arq != NULL){
        fscanf(arq, "%s %d %d %d\n", format, &width, &height, &max);
        pixels= (unsigned char *) malloc(sizeof(unsigned char)*width*height*3);
        fread(pixels, sizeof(unsigned char), width*height*3, arq);
        fclose(arq);
        //printf("sucess ! path= %s",filename);
        return pixels;
    }
    //printf("error! path= %s",filename);
    return NULL;
}

GLuint loadTextura(const char *c){
    unsigned char *data = readPPM(c);
    GLuint texid;
    //printf("before %d",texid1);
    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    free(data);
    return texid;
}

void activeTex(void){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //printf("activate %d",texid1);
}


void textura(const char *filename) {

    texid1 = loadTextura(filename);
    //printf("after %d",texid1);
    activeTex();
}



void iluminacao ()
{
        GLfloat luzAmbiente[4] = {0.2,0.2,0.2,1.0}; 
        GLfloat luzDifusa[4] = {0.7,0.7,0.7,1.0};          
        GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};
        GLfloat posicaoLuz[4] = {0.0, 20.0, 20.0, 1.0};
 
        // Capacidade de brilho do material
        GLfloat especularidade[4] = {1.0,1.0,1.0,1.0}; 
        GLint especMaterial = 60;
 
        // Define a refletância do material 
        glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
        // Define a concentração do brilho
        glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
 
        // Ativa o uso da luz ambiente 
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

        glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);

		glEnable(GL_COLOR_MATERIAL);

		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
 
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
        glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
        glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );    
}


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

void getColor3f(int color, float* a, float* b, float* c) {
	
	if(color == 0) { //WHITE
		*a = 1.0;
		*b = 1.0;
		*c = 1.0; 
	} else if(color == 1) { //ORANGE 
		*a = 1.0;
		*b = 0.65;
		*c = 0.0;
	} else if(color == 2) { //GREEN 
		*a = 0.0;
		*b = 1.0;
		*c = 0.0; 
	} else if(color == 3) { //RED 
		*a = 1.0;
		*b = 0.0;
		*c = 0.0;
	} else if(color == 4) { //YELLOW 
		*a = 1.0;
		*b = 1.0;
		*c = 0.0;
	} else if(color == 5) { //BLUE 
		*a = 0.0;
		*b = 0.0;
		*c = 1.0; 
	}  

}


void oneFace(Matrix* m) {
	
	float a, b, c;

	glPushAttrib(GL_LIGHTING_BIT);

	glPushMatrix();
	for (int i = 0; i < m->getSize(); ++i)
	{

		GLfloat teste[3] = {1,1,1};
		activeTex();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,teste);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

		glPushAttrib(GL_LIGHTING_BIT);

		glPushMatrix();
		for (int j = 0; j < m->getSize(); ++j){
			
			
			getColor3f(m->getSquares()[i][j], &a, &b, &c);
			glColor3f(a, b, c);	
			glBegin(GL_POLYGON);
			glScalef(5,0,2.8);
			glBegin(GL_QUADS);
			
			glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0, 0.0, 0.0);
			

			glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0, 0.5, 0.0);

			glTexCoord2f(1.0f, 1.0f);	glVertex3f(0.5, 0.5, 0.0);

			glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.5, 0.0, 0.0);
			glEnd();

			glTranslatef(0.5, 0.0, 0.0);
		}
		glPopMatrix();
		glBindTexture( GL_TEXTURE_2D, 0 );
		glTranslatef(0.0, 0.5, 0.0);
		glPopAttrib();

	}
	glPopMatrix();
	glBindTexture( GL_TEXTURE_2D, 0 );
	glPopAttrib();
	

}


void inicializacao() {
	//cor de fundo eh cinza
	glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
	// set_color(); // definir cores dos cubos

	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	//colorização de gourand
	glShadeModel(GL_SMOOTH);
	
	glMatrixMode(GL_PROJECTION);
	//alterne e altere as projecoes para alcancar os resultados desejados
	gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 20.0);
	glMatrixMode(GL_MODELVIEW);

	gluLookAt(0.0, 5.0, 5.0,  /* eye is at (0,0,5) */
		0.0, 0.0, 0.0,      /* center is at (0,0,0) */
		0.0, 1.0, 0.);      /* up is in positive Y direction */


	iluminacao();
	
	glPushMatrix();

   	glTranslatef(0, 0, 0);
   	glScalef(1.0, 1.0, 1);
   	//glutWireCube(1.0);
   	glutSolidCube(1.0);
  	
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
	
	//limpa a tela com a cor de fundo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//altere gluLookAt para movimentar a camera ao redor do cubo.
	gluLookAt( position_x, position_y, position_z, 0.0, 0.0, 0.0, 0, 1, 0);

	
	iluminacao();

	textura("imgs/laranja.ppm");
	
	glColor3f(0, 0, 0);
	
	// Criação do cubo

	oneFace(cubo->getFace(Directions::LEFT));

	textura("imgs/verde.ppm");

	glTranslatef(cubo->getSize()*0.5, 0.0, 0.0);
	if(control_3d) 
		glRotatef(90, 0, 1, 0);
	oneFace(cubo->getFace(Directions::FRONT));

	textura("imgs/azul.ppm");

	glPushMatrix();
	if(!control_3d)
		glTranslatef(0.0, cubo->getSize()*(-0.5), 0.0);
	if(control_3d) { 
		glTranslatef(0.0, 0.0, cubo->getSize()*(-0.5));
		glRotatef(90, 1, 0, 0);
	}
	oneFace(cubo->getFace(Directions::DOWN));
	glPopMatrix();

	textura("imgs/branca.ppm");

	glPushMatrix();
	glTranslatef(0.0, cubo->getSize()*0.5, 0.0);
	if(control_3d) 
		glRotatef(-90, 1, 0, 0);
	oneFace(cubo->getFace(Directions::UP));
	glPopMatrix();

	textura("imgs/vermelha.ppm");

	glTranslatef(cubo->getSize()*0.5, 0.0, 0.0);
	if(control_3d) 
		glRotatef(90, 0, 1, 0);
	oneFace(cubo->getFace(Directions::RIGHT));

	textura("imgs/amarela.ppm");

	glTranslatef(cubo->getSize()*0.5, 0.0, 0.0);
	if(control_3d) 	
		glRotatef(90, 0, 1, 0);
	oneFace(cubo->getFace(Directions::BACK));

	//glutSolidSphere(1.0, 32, 32);

	glutSwapBuffers();

}

void funcaoKeyboard(unsigned char key, int x, int y) {

	if(key == 'q') {
		exit(-1);
	}
	if(key == 32) { // tecla space: pausar rotação automática da câmera.
		control_space = !control_space;
		if(!control_space)
			cout << "= Rotação pausada =" <<endl;
		else
			cout << "= Rotação automática =" <<endl;
	}
	if(key == 111) { // tecla o: altera orientação das rotações.
		control_orientation = !control_orientation;
		if (!control_orientation) {
			cout << "= Sentido anti-horário =" <<endl;
		} else {
			cout << "= Sentido horário =" <<endl;
		}
		
	}

	// Comandos referentes a movimentação da câmera

	if(key == 97) { //tecla a
		//position_x += 1;
		if(position_x <= 30) {
			position_x++;
		} else {
			position_x = -4;	
		}
	} 
	if(key == 120) { //tecla x
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

	// Comandos referentes as movimentações das faces.

	if(key == 108) { //tecla l
		cubo->getFace(Directions::LEFT)->rotate(control_orientation);
	} 
	if(key == 102) { //tecla f
		//cout << cubo->getFace(Directions::UP)->toString();
		//cubo->getFace(Directions::BACK)->rotate(!control_orientation);	
		cubo->getFace(Directions::FRONT)->rotate(control_orientation);	
	} 
	if(key == 100) { //tecla d
		//cubo->getFace(Directions::UP)->rotate(!control_orientation);
		cubo->getFace(Directions::DOWN)->rotate(control_orientation);
	} 
	if(key == 117) { //tecla u
		//cubo->getFace(Directions::DOWN)->rotate(!control_orientation);
		cubo->getFace(Directions::UP)->rotate(control_orientation);
	} 
	if(key == 114) { //tecla r
		cubo->getFace(Directions::RIGHT)->rotate(control_orientation);
	} 
	if(key == 98) { //tecla b
		//cubo->getFace(Directions::FRONT)->rotate(!control_orientation);
		cubo->getFace(Directions::BACK)->rotate(control_orientation);
	} 
	if(key == 118) { //tecla v : visualização 3d ou 2d
		control_3d = !control_3d;
	} 

	// Quantidade de movimentos 
	if(key == 108 || key == 102 || key == 100 ||
	   key == 117 || key == 114 || key == 98) {
		cout << "Movimentos: "<<++num_movements<<endl;
	}


	glutPostRedisplay();
}

int i = 0;
void temporizador() {
	i++;
	if(i == 17) {
		if(control_space) {
			if(position_x <= 30) {
				position_x++;
			} else {
				position_x = -4;	
			}
		} 

		i = 0;
		theta += 0.2;
	}

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

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cubo Mágico");
	glutKeyboardFunc(funcaoKeyboard);
	glutDisplayFunc(funcaoDisplay);
	glutIdleFunc(temporizador);
	inicializacao();
	glutMainLoop();

	return 0;
}

