#include "Matrix.h"

Matrix::Matrix(int size, int color) {
	this->size = size;
	this->squares = new int*[size];
	//int count = 0;
	for (int i = 0; i < this->size; ++i) {
		this->squares[i] = new int[size];
		for (int j = 0; j < this->size; ++j) {
			this->squares[i][j] = color;
		}
	}
}

Matrix::~Matrix() {

}

void Matrix::rotate(bool clockwise) {
	this->transpose();
	int *aux;
	if (clockwise) {
		this->reverseRows();
		aux = this->getParentEdge(Directions::UP);
		this->setParentEdge(this->getParentEdge(Directions::LEFT), Directions::UP, true);
		this->setParentEdge(this->getParentEdge(Directions::DOWN), Directions::LEFT);
		this->setParentEdge(this->getParentEdge(Directions::RIGHT), Directions::DOWN, true);
		this->setParentEdge(aux, Directions::RIGHT);
	} else {
		this->reverseColumns();
		aux = this->getParentEdge(Directions::UP);
		this->setParentEdge(this->getParentEdge(Directions::RIGHT), Directions::UP);
		this->setParentEdge(this->getParentEdge(Directions::DOWN), Directions::RIGHT, true);
		this->setParentEdge(this->getParentEdge(Directions::LEFT), Directions::DOWN);
		this->setParentEdge(aux, Directions::LEFT, true);
	}
}

int Matrix::getSize() {
	return this->size;
}

/**
 * Adiciona a Matrix m à matriz atual, na posição d, levando em consideração q a parte de cima
 * da matriz adicionada está virada para r
 * */
void Matrix::setMatrix(Matrix* m, Directions d, Directions r) {
	this->parents[d].d = r;
	this->parents[d].m = m;
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
		for (int j = i+1; j < this->size; ++j) {
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

Matrix* Matrix::getMatrix(Directions d) {
	return this->parents[d].m;
}

int* Matrix::getEdge(Directions d) {
	int* edge = new int[this->size];
	switch(d) {
		case Directions::UP:
			for (int i = 0; i < this->size; ++i) {
				edge[i] = this->squares[0][i];
			}
			break;

		case Directions::DOWN:
			for (int i = 0; i < this->size; ++i) {
				edge[i] = this->squares[this->size-1][i];
			}
			break;

		case Directions::LEFT:
			for (int i = 0; i < this->size; ++i) {
				edge[i] = this->squares[i][0];
			}
			break;
		case Directions::RIGHT:
			for (int i = 0; i < this->size; ++i) {
				edge[i] = this->squares[i][this->size-1];
			}
			break;
	}
	return edge;
}

int* Matrix::getParentEdge(Directions d) {
	return this->parents[d].m->getEdge(this->parents[d].d);
}

void Matrix::setEdge(int* edge, Directions d, bool inverse) {
	switch(d) {
		case Directions::UP:
			for (int i = 0; i < this->size; ++i) {
				this->squares[0][i] = edge[inverse ? this->size - i - 1 : i];
			}
			break;

		case Directions::DOWN:
			for (int i = 0; i < this->size; ++i) {
				this->squares[this->size-1][i] = edge[inverse ? this->size - i - 1 : i];
			}
			break;

		case Directions::LEFT:
			for (int i = 0; i < this->size; ++i) {
				this->squares[i][0] = edge[inverse ? this->size - i - 1 : i];
			}
			break;
		case Directions::RIGHT:
			for (int i = 0; i < this->size; ++i) {
				this->squares[i][this->size-1] = edge[inverse ? this->size - i - 1 : i];
			}
			break;
	}
}

void Matrix::setParentEdge(int* edge, Directions d, bool inverse) {
	Matrix* parent = this->parents[d].m;
	parent->setEdge(edge, this->parents[d].d, inverse);
}

int** Matrix::getSquares() {
	return this->squares;
}