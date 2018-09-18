#ifndef __CUBE_H_INCLUDED__
#define __CUBE_H_INCLUDED__

#include "Matrix.h"
#include "Colors.h"

class Cube {
	public:
		Cube(int size);
		Matrix* getFace(Directions d);
		int getSize();
	private:
		Matrix* faces[6];
		int size;
};

#endif