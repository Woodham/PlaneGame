/*
 * Vector.h
 *
 *  Created on: 24-Mar-2009
 *      Author: balor
 */

#ifndef VECTOR_H_
#define VECTOR_H_

class Vector {
public:
	Vector();
	Vector(float i, float j, float k);
	virtual ~Vector();
	float getI();
	float getJ();
	float getK();

	Vector * add(Vector * v);
private:
	float i,j,k;
};

#endif /* VECTOR_H_ */
