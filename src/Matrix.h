#ifndef __MATRIX_H_INCLUDED__
#define __MATRIX_H_INCLUDED__

#include <string>
#include "Directions.h"
using std::string;
using std::to_string;

class Matrix {
	public:
		Matrix(int size, int color);
		~Matrix();
		void rotate(bool clockwise);
		string toString();
		int* getEdge(Directions d);
		Matrix* getParent(Directions d);
	private:
		void transpose();
		void reverseRows();
		void reverseColumns();
		int size;
		int** squares;
		Matrix* up;
		Matrix* down;
		Matrix* left;
		Matrix* right;
};

#endif