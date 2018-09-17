#include "Cube.h"

Cube::Cube(int size) {
	this->size = size;

	Matrix* up =  new Matrix(size, Colors::WHITE);
	Matrix* down =  new Matrix(size, Colors::BLUE);
	Matrix* left =  new Matrix(size, Colors::ORANGE);
	Matrix* right =  new Matrix(size, Colors::RED);
	Matrix* front =  new Matrix(size, Colors::GREEN);
	Matrix* back =  new Matrix(size, Colors::YELLOW);

	up->setMatrix(back, Directions::UP, Directions::UP);
	up->setMatrix(front, Directions::DOWN, Directions::UP);
	up->setMatrix(left, Directions::LEFT, Directions::UP);
	up->setMatrix(right, Directions::RIGHT, Directions::UP);

	down->setMatrix(front, Directions::UP, Directions::DOWN);
	down->setMatrix(back, Directions::DOWN, Directions::DOWN);
	down->setMatrix(left, Directions::LEFT, Directions::DOWN);
	down->setMatrix(right, Directions::RIGHT, Directions::DOWN);

	left->setMatrix(up, Directions::UP, Directions::LEFT);
	left->setMatrix(down, Directions::DOWN, Directions::LEFT);
	left->setMatrix(back, Directions::LEFT, Directions::RIGHT);
	left->setMatrix(front, Directions::RIGHT, Directions::LEFT);

	right->setMatrix(up, Directions::UP, Directions::RIGHT);
	right->setMatrix(down, Directions::DOWN, Directions::RIGHT);
	right->setMatrix(front, Directions::LEFT, Directions::RIGHT);
	right->setMatrix(back, Directions::RIGHT, Directions::LEFT);

	front->setMatrix(up, Directions::UP, Directions::DOWN);
	front->setMatrix(down, Directions::DOWN, Directions::UP);
	front->setMatrix(left, Directions::LEFT, Directions::RIGHT);
	front->setMatrix(right, Directions::RIGHT, Directions::LEFT);

	back->setMatrix(up, Directions::UP, Directions::UP);
	back->setMatrix(down, Directions::DOWN, Directions::DOWN);
	back->setMatrix(right, Directions::LEFT, Directions::LEFT);
	back->setMatrix(left, Directions::RIGHT, Directions::RIGHT);

	this->faces[Directions::UP] = up;
	this->faces[Directions::LEFT] = left;
	this->faces[Directions::FRONT] = front;
	this->faces[Directions::RIGHT] = right;
	this->faces[Directions::BACK] = back;
	this->faces[Directions::DOWN] = down;
}

Matrix* Cube::getFace(Directions d) {
	return this->faces[d];
}