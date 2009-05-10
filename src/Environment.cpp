#include "Environment.h"


Environment::Environment()
{

	this->map = new BSP("/home/woodham/jpal/maps/jpal.bsp");

	PCX * texture = new PCX("/home/woodham/MEGAMAN.PCX");

	MD2 * model = new MD2("/home/woodham/TRIS.MD2");

	proj = new Projectile(0.0f, 0.0f, 0.0f, model, texture);


}

Environment::~Environment()
{
}


void Environment::display()
{

	glLoadIdentity();

	//static float bob = 0.0f;

	//glRotatef(bob, 1.0f,1.0f, 0.0f);

	//bob += 5.0f;

	//glTranslatef(100.0f, -200.0f, 560.0f);



	//glPushMatrix();

	map->Draw();

//proj->draw();



	//glPopMatrix();

	//glPushMatrix();



	//glPopMatrix();

	//

	//


	//proj->draw();

	//glPopMatrix();

}

void Environment::update()
{

	proj->update(gravity);

}

float Environment::getGravity()
{

	return gravity;

}


