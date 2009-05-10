#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameObject.h"


class Projectile: public GameObject
{
public:
	Projectile(float velocityx, float velocityy, float velocityz, MD2 *model, PCX *texture);
	virtual ~Projectile();

	void draw();
	void update(float);

private:
	float rotcube;
	float ypos;
	float xpos;
	float zpos;
	float xveloc;
	float yveloc;
	float zveloc;
	float yvelocstore;
	MD2 *model;
	int frame;
	float aniSpeed;
	PCX * tex;

};

#endif /*PROJECTILE_H_*/
