#include "Matrix.h"

Matrix::Matrix(int size, int color) {
	this->size = size;
	this->squares = new int*[size];
	for (int i = 0; i < this->size; ++i) {
		this->squares[i] = new int[size];
		for (int j = 0; j < this->size; ++j) {
			this->squares[i][j] = i+j;
		}
	}
}

Matrix::~Matrix() {

}

void Matrix::rotate(bool clockwise) {
	this->transpose();
	int* aux = new [this->size];
	if (clockwise) {
		this->reverseRows();
	} else {
		this->reverseColumns();
	}
}

void Matrix::reverseColumns() {
	for(int i = 0; i < this->size; ++i) {
		for (int j = 0; j < this->size / 2; ++j) {
			int aux;
			aux = this->squares[j][i];
			this->squares[j][i] = this->squares[this->size - (j+1)][i];
			this->squares[this->size - (j+1)][i] = aux;
		}
	}
}

void Matrix::reverseRows() {
	for(int i = 0; i < this->size; ++i) {
		for (int j = 0; j < this->size / 2; ++j) {
			int aux;
			aux = this->squares[i][j];
			this->squares[i][j] = this->squares[i][this->size - (j+1)];
			this->squares[i][this->size - (j+1)] = aux;
		}
	}
}

void Matrix::transpose() {
	for(int i = 0; i < this->size; ++i) {
		for (int j = 0; j < this->size; ++j) {
			int aux;
			aux = this->squares[i][j];
			this->squares[i][j] = this->squares[j][i];
			this->squares[j][i] = aux;
		}
	}
}

string Matrix::toString() {
	string result = "";
	for (int i = 0; i < this->size; ++i) {
		for (int j = 0; j < this->size; ++j) {
			result += to_string(this->squares[i][j]) + " ";
		}
		result += "\n";
	}
	result += "\n";
	return result;
}

Matrix* Matrix::getParent(Directions d) {
	switch(d) {
		case Directions::UP:
			return this->up;
			break;
		case Directions::DOWN:
			return this->down;
			break;
		case Directions::LEFT:
			return this->left;
			break;
		case Directions::RIGHT:
			return this->right;
			break;
	}
}