/*
 * Vector.cpp
 *
 *  Created on: 24-Mar-2009
 *      Author: balor
 */

#include "Vector.h"

Vector::Vector() {
	this->i = 0.0f;
	this->j = 0.0f;
	this->k = 0.0f;
}

Vector::Vector(float i, float j, float k) {
	this->i = i;
	this->j = j;
	this->k = k;
}

Vector::~Vector() {
	// TODO Auto-generated destructor stub
}

float Vector::getI() {
	return this->i;
}

float Vector::getJ() {
	return this->j;
}

float Vector::getK() {
	return this->k;
}

Vector * Vector::add(Vector * v) {
	return new Vector(this->i + v->getI(),
			this->j + v->getJ(),
			this->k + v->getK());
}
