#ifdef _WIN32
#include <windows.h>
#endif

#include "main.h"

#include <iostream>
#include <Windows.h>
#include "GLee.h"
#include <GL/glut.h>

using namespace std;

Sun sun;
SkyBox skybox;
BezierCurve camera;
Planet planet = Planet(1.0, "mars_1k_color.jpg","mars_1k_normal.jpg");
Planet planet2 = Planet(1.0, "earthmap1k.jpg", "earthbump1k_NRM.jpg");

namespace Globals
{
};

void init()
{
	skybox.createCubeMap();
   planet.setUpShader();
   planet2.setUpShader();
}

void displayCallback()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

   camera.move(.0005);

   skybox.render();

   glPushMatrix();
   sun.render();
   glTranslatef(5.0, 0.0, 0.0);
   planet2.render();

   glTranslatef(5.0, 0.0, 0.0);
   planet.render();
   glPopMatrix();

   glFlush();
   glutSwapBuffers();
}

void idleCallback()
{
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
   gluPerspective(60.0, double(window_width) / (double)window_height, 1.0, 1000.0); // set perspective projection viewing frustum
   glTranslatef(0.0, 0.0, -20.0);
   glMatrixMode(GL_MODELVIEW);
}

void keyboardCallback(unsigned char key, int, int)
{
   switch (key) {
   case 's':
   {
      glScalef(.75, .75, .75);
      break;
   }
   case 'S':
   {
      glScalef(1.25, 1.25, 1.25);
      break;
   }
   case 'y':
   {
      glRotatef(-10, 0, 1, 0);
      break;
   }
   case 'Y':
   {
      glRotatef(10, 0, 1, 0);
      break;
   }
   case ' ':
   {
	   camera.pause();
	   break;
   }
   }
}

void specialKeysCallback(int key, int x, int y) {
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(window_width, window_height);
   glutCreateWindow("Galaxy");

   float specular[] = { 1.0, 1.0, 1.0, 1.0 };
   float ambient[] = { .5, .5, .5, 1.0 };
   float position[] = { 10.0, 10.0, 20.0, 1.0 };	// lightsource position
   float shininess[] = { 100.0 };
   float diffuse[] = { 0.1, 0.5, 0.8, 1.0 };

   //Generate material properties:

   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
   glEnable(GL_COLOR_MATERIAL);

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