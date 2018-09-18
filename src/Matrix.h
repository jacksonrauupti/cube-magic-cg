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
		void setEdge(int* edge, Directions d, bool inverse = false);
		int* getEdge(Directions d);
		int* getParentEdge(Directions d);
		void setParentEdge(int* edge, Directions d, bool inverse = false);
		void setMatrix(Matrix* m, Directions d, Directions r);
		Matrix* getMatrix(Directions d);
		int getSize();
	private:
		void transpose();
		void reverseRows();
		void reverseColumns();
		Directions getRealD(Directions r, Directions d);
		int size;
		int** squares;
		struct DMatrix {
			Matrix* m;
			Directions d;
		} parents[4];
};

#endif