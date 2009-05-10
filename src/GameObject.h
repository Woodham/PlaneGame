#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_


#include "MD2.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void draw();
	void update();



};

#endif /*GAMEOBJECT_H_*/
