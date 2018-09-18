#include "Game.h"

/**
 * Inicializa o jogo
 * */
Game::Game(int* argc, char** argv) {

	// Inicializa variáveis de posição:
	Game::posX = -5;
	Game::posY = 0;
	Game::posZ = 0;

	// Inicializa semente para geração de float randômico
	srand(time(NULL));

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Cubo magico");
	glutKeyboardFunc(this->funcaoKeyboard);
	glutDisplayFunc(this->display);
	this->drawCube();

	// Inicialização:
	glClearColor(0.8, 0.8, 0.8, 0.8);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
	glMatrixMode(GL_MODELVIEW);
	// gluLookAt(-4, 3, -4, 0, 0, 0, 0, 1, 0);
	gluLookAt(Game::posX, Game::posY, Game::posZ,  /* eye is at (0,0,5) */
	0, 0, 0,      /* center is at (0,0,0) */
	0, 1, 0);      /* up is in positive Y direction */
	glutMainLoop();
}

float Game::randomf() {
	return ((float)rand())/RAND_MAX;
}

void Game::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Game::drawCube();
	glFlush();
	glutSwapBuffers();
}

void Game::drawCube() {
	glBegin(GL_POLYGON);
	glVertex3f(-0.500000, -0.500000, 0.500000);
	glVertex3f(0.500000, -0.500000, 0.500000);
	glVertex3f(0.500000, 0.500000, 0.500000);
	glVertex3f(-0.500000, 0.500000, 0.500000);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.500000, 0.500000, 0.500000);
	glVertex3f(0.500000, 0.500000, 0.500000);
	glVertex3f(0.500000, 0.500000, -0.500000);
	glVertex3f(-0.500000, -0.500000, -0.500000);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.500000, 0.500000, -0.500000);
	glVertex3f(0.500000, 0.500000, -0.500000);
	glVertex3f(0.500000, -0.500000, -0.500000);
	glVertex3f(-0.500000, -0.500000, -0.500000);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.500000, -0.500000, -0.500000);
	glVertex3f(0.500000, -0.500000, -0.500000);
	glVertex3f(0.500000, -0.500000, 0.500000);
	glVertex3f(-0.500000, -0.500000, 0.500000);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.500000, -0.500000, 0.500000);
	glVertex3f(0.500000, -0.500000, -0.500000);
	glVertex3f(0.500000, 0.500000, -0.500000);
	glVertex3f(0.500000, 0.500000, 0.500000);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.500000, -0.500000,-0.500000);
	glVertex3f(-0.500000, -0.500000, 0.500000);
	glVertex3f(-0.500000, 0.500000, 0.500000);
	glVertex3f(-0.500000, 0.500000, -0.500000);
	glEnd();
}

void Game::funcaoKeyboard(unsigned char key) {
	// switch(key) {
	// 	case 'q':
	// 		exit(-1);
	// 		break;
	// 	case 97:
	// 		Game::posX++;
	// 		break;
	// 	case 100:
	// 		Game::posY
	// }
	// if(key == 'q') {
	// 	exit(-1);
	// }
	// // if(key == 32) { // tecla space
	// // 	control_space *= -1;
	// // }
	// if(key == 97) { //tecla a
	// 	//position_x += 1;
	// 	if(position_x <= 30) {
	// 		position_x++;
	// 	} else {
	// 		position_x = -4;	
	// 	}
	// } 
	// if(key == 100) { //tecla d
	// 	//position_x -= 1;
	// 	if(position_x >= -20) {
	// 		position_x--;
	// 	} else {
	// 		position_x = -4;	
	// 	}
	// } 
	// if(key == 119) { //tecla w
	// 	position_y += 1;
	// } 
	// if(key == 115) { //tecla s
	// 	position_y -= 1;
	// } 
	// if(key == 122) { //tecla z
	// 	position_z += 1;
	// } 
	// if(key == 101) { //tecla e
	// 	position_z -= 1;
	// } 

	// glutPostRedisplay();
}