#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include "cstdlib"
#include "time.h"
#include <GL/glut.h>

class Game {
	public:
		Game(int* argc, char **argv);
		float randomf();
		static void drawCube();
		static void display();
		static void funcaoKeyboard(unsigned char key);
	private:
		static int posX, posY, posZ;
};

#endif