#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Projectile.h"
#include "PCX.h"
#include "MD2.h"
#include "BSP.h"

class Environment
{
public:
	Environment();
	virtual ~Environment();

	void display();
	void update();

	float getGravity();

private:
	static const float gravity = 9.81;
	Projectile *proj;
	BSP * map;

};



#endif /*ENVIRONMENT_H_*/
