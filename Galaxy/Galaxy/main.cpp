#ifdef _WIN32
#include <windows.h>
#endif

#include "main.h"
#include "SolarSystem.h"
#include "SpaceShip.h"
#include <iostream>
#include <memory>
#include <Windows.h>
#include "GLee.h"
#include <GL/glut.h>
#include "BasicParticles.hpp"
#include "BasicParticleGenerators.hpp"
#include "ParticleUpdaters.hpp"
#include "glParticleRenderer.hpp"

using namespace std;
using namespace particles;

bool glow_flag = 1;

SkyBox skybox;
BezierCurve camera;
SolarSystem * solar;
SpaceShip * spaceShip;
ShootingStar *shootingstar;

namespace Globals
{
};

void init()
{
   spaceShip = new SpaceShip();
   solar = new SolarSystem();
	skybox.createCubeMap();
   solar->setUp();
}

void displayCallback()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
   
   /*float specular2[] = { 0.0, 0.0, 0.0, 1.0 };
   float ambient2[] = { .5, .5, .5, 1.0 };
   float position2[] = { 0, 0.0, 0.0, 1.0 };	// lightsource position
   float shininess2[] = { 1.0 };
  
   // Generate light source:
   glLightfv(GL_LIGHT0, GL_POSITION, position2);
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient2);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specular2);
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glEnable(GL_LIGHT0);*/
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_NORMALIZE);

   skybox.render(4000);
   //spaceShip->render();
   solar->render();
   if (shootingstar != NULL)
	shootingstar->render();

   glFlush();
   glutSwapBuffers();
}

void idleCallback()
{
	camera.move(.0005);
	displayCallback();         // call display routine to show the cube
}

// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
   cerr << "Window::reshapeCallback called" << endl;
   window_width = new_width;
   window_height = new_height;
   glViewport(0, 0, window_width, window_height);  // set new viewport size
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, double(window_width) / (double)window_height, 1.0, 4000.0); // set perspective projection viewing frustum
   gluLookAt(0,0,-400, 0, 0, 0, 0,1,0);
   //glTranslatef(0, 0, -400);
   glMatrixMode(GL_MODELVIEW);
}

void keyboardCallback(unsigned char key, int, int)
{
   switch (key) {
   case 's':
   {
	   solar->scale(.9);
	   skybox.scale(.9);
	   if (shootingstar != NULL)
		shootingstar->scale(.9);
      break;
   }
   case 'S':
   {
	   solar->scale(1.1);
	   skybox.scale(1.1);
	   if (shootingstar != NULL)
		shootingstar->scale(1.1);
      break;
   }
   case 'y':
   {
	   solar->rotateY(-10);
	   skybox.rotateY(-10);
	   break;
   }
   case 'Y':
   {
	   solar->rotateY(10);
	   skybox.rotateY(10);
	   break;
   }
   case ' ':
   {
	   camera.pause();
      solar->moving = !solar->moving;
	   break;
   }
   case 'g':
   {
	   glow_flag = !glow_flag;
      solar->toggleGlow();
	   break;
   }
   case 'b':
   {
      solar->toggleBumps();
      break;
   }
   case 'p':
   {
      glLoadIdentity();
      gluLookAt(0, 0, -200, 0, 0, -200, 0, 0, 1);
      break;
   }
   case 39: // '
   {
	   solar->translate(2, 0, 0);
	   skybox.translate(2, 0, 0);
	   break;
   }
   case 59: // ;
   {
	   solar->translate(-2, 0, 0);
	   skybox.translate(-2, 0, 0);
	   break;
   }
   case '[': 
   {
	   solar->translate(0, -2, 0);
	   skybox.translate(0, -2, 0);
	   break;
   }
   case '/': 
   {
	   solar->translate(0, 2, 0);
	   skybox.translate(0, 2, 0);
	   break;
   }
   case 'v':
   {
	   if (shootingstar != NULL) delete shootingstar;
	   shootingstar = new ShootingStar();
	   shootingstar->shoot();
	   break;
   }
   case 'V':
   {
	   delete shootingstar;
	   shootingstar = NULL;
	   break;
   }
   }
}

void specialKeysCallback(int key, int x, int y) {
   switch (key) {
   case GLUT_KEY_LEFT:
	   glMatrixMode(GL_PROJECTION);
	   glTranslatef(-2, 0, 0);
      spaceShip->translate(2, 0, 0);
	   //glRotatef(4, 0, 1, 0);
	  glMatrixMode(GL_MODELVIEW);
      break;
   case GLUT_KEY_RIGHT:
	   glMatrixMode(GL_PROJECTION);
	   glTranslatef(2, 0, 0);
      spaceShip->translate(-2, 0, 0);
	   //glRotatef(-4,0,1,0);
	   glMatrixMode(GL_MODELVIEW);
      break;
   case GLUT_KEY_UP:
	   glMatrixMode(GL_PROJECTION);
	   glTranslatef(0, 0, -2);
      spaceShip->translate(0, 0, 2);
	   glMatrixMode(GL_MODELVIEW);
      break;
   case GLUT_KEY_DOWN:
	   glMatrixMode(GL_PROJECTION);
	   glTranslatef(0, 0, 2);
      spaceShip->translate(0, 0, -2);
	   glMatrixMode(GL_MODELVIEW);
      break;
   }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(window_width, window_height);
   glutCreateWindow("Galaxy");

   glEnable(GL_LIGHTING);
   glutReshapeFunc(reshapeCallback);
   glutDisplayFunc(displayCallback);
   glutKeyboardFunc(keyboardCallback);
   glutSpecialFunc(specialKeysCallback);
   glutIdleFunc(idleCallback);

   glEnable(GL_DEPTH_TEST);
   init();

   glutMainLoop();
}