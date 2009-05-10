#include "Projectile.h"


Projectile::Projectile(float velocityx, float velocityy, float velocityz, MD2 *model, PCX *tex)
{

	this->tex = tex;
	this->model = model;

	frame = 96;
	aniSpeed = 0.0f;

	rotcube = 0.0f;

	xpos = 0.0f;
	ypos = 0.0f;
	zpos = 0.0f;

	xveloc = velocityx;
	yveloc = velocityy;
	zveloc = velocityz;

	yvelocstore = yveloc;

	//glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &this->tex->getTexInfo()->id);

	//glBindTexture(GL_TEXTURE_2D, this->tex->getTexInfo()->id);



}

Projectile::~Projectile()
{
}


void Projectile::draw()
{



		//glTranslatef(xpos, ypos, zpos); // Translate Into The Screen 7.0 Units
		//glRotatef(rotcube, 0.0f, 1.0f, 0.0f); // Rotate The cube around the Y axis
		//glRotatef(rotcube, 1.0f, 1.0f, 1.0f);

		//glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		//glRotatef(-110.0f, 0.0f, 0.0f, 1.0f);

		//glScalef(0.05, 0.05, 0.05);

		/*THESE BITS*/

		gluBuild2DMipmaps(GL_TEXTURE_2D, this->tex->getTexInfo()->internalFormat, this->tex->getTexInfo()->width, this->tex->getTexInfo()->height, this->tex->getTexInfo()->format, GL_UNSIGNED_BYTE, this->tex->getTexInfo()->texels);


		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);





		glBindTexture(GL_TEXTURE_2D, 1);

		/*TO HERE*/

     	this->model->Draw(frame, this->tex->getTexInfo()->id);

}

void Projectile::update(float gravity)
{

	float newGrav = gravity / 1000;


	aniSpeed = aniSpeed + 0.25f;



	if(ypos >= 0.0f)
	{

	//rotcube +=2.0f;

	yveloc -= newGrav;

	ypos += yveloc;

	xpos += xveloc;

	zpos += zveloc;
	}else{
	//	rotcube =0.0f;
//
//		xpos = 2.0f;
//		ypos = 0.0f;
//		zpos = -4.0f;
//
//		yveloc = yvelocstore;
//
//		frame = 95;
	}


	if (aniSpeed > 1)
	{

		//cout << aniSpeed << endl;

	if(frame < 123)
	{
	frame++;
	}else if (ypos <= 0.0f){
		frame = 96;

				xpos = 0.0f;
				ypos = 0.0f;
				zpos = -4.0f;

				yveloc = yvelocstore;

	}

	aniSpeed = 0.0f;

	}



}
