#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <iostream>
#include "GameObject.h"
#include "Projectile.h"
#include "Environment.h"

using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00
#define RUN_UPDATE 0x01


/*
 * Registering this function as the AddTimer callback is not
 * the best way of regulating the screen update.  However it's
 * easy for the moment.  This function will run in a separate
 * thread and may cause concurrency access issues.
 */
Uint32 display(Uint32 interval, void *param) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = RUN_GRAPHICS_DISPLAY;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
	return interval;
}

Uint32 update(Uint32 interval, void *param) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = RUN_UPDATE;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
	return interval;
}

void display(Environment *env) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT);

	// Reset The Current Modelview Matrix
	glLoadIdentity();

	env->display();

	// Don't forget to swap the buffers (I did)
	SDL_GL_SwapBuffers();
}

void update(Environment *env)
{

	env->update();


}

int main(int argc, char ** argv) {
	SDL_Surface * surf;
	Uint32 width = 640;
	Uint32 height = 480;
	Uint32 colour_depth = 16; // in bits
	Uint32 delay = 1000/60; // in milliseconds
	Environment *env = new Environment();

	// Initialise SDL - when using C/C++ it's common to have to
	// initialise libraries by calling a function within them.
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
			cout << "Failed to initialise SDL: " << SDL_GetError() << endl;
			SDL_Quit();
	}

	// When we close a window quit the SDL application
	atexit(SDL_Quit);

	// Create a new window with an OpenGL surface
	if (!(surf = SDL_SetVideoMode(width, height, colour_depth, SDL_OPENGL))) {
			cout << "Failed to initialise video mode: " << SDL_GetError() << endl;
			SDL_Quit();
		}

	// Set the state of our new OpenGL context
	glViewport(0,0,(GLsizei)(width),(GLsizei)(height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(GLfloat)(width)/(GLfloat)(height),1.0f,10000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);

	//glEnable(GL_TEXTURE_2D);

	// Call the function "display" every delay milliseconds
	SDL_AddTimer(delay, display, NULL);

	//Then call the function "update"
	SDL_AddTimer(delay, update, NULL);

	// Add the main event loop
	SDL_Event event;
	while (SDL_WaitEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				SDL_Quit();
			case SDL_USEREVENT:

				switch (event.user.code) {
				case RUN_GRAPHICS_DISPLAY:
					display(env);
					break;
				case RUN_UPDATE:
					update(env);
					break;
				}

			}
	}
}
