#ifdef _WIN32
#include <windows.h>
#endif

#include "main.h"

#include <iostream>
#include <GL/glut.h>

using namespace std;
static int window_width = 512, window_height = 512;
Sun sun = Sun();
SkyBox skybox;

namespace Globals
{
};

void init()
{
	skybox.createCubeMap();
}

void displayCallback()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

   skybox.render();
   sun.render();

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
   glViewport(0, 0, new_width, new_height);  // set new viewport size
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, double(new_width) / (double)new_height, 1.0, 1000.0); // set perspective projection viewing frustum
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
   float position[] = { 0, 5.0, 0.0, 1.0 };	// lightsource position
   float shininess[] = { 100.0 };
   float diffuse[] = { 0.0, 0.0, 0.0, 0.0 };

   shininess[0] = 100.0;

   specular[0] = 1.0;
   specular[1] = 1.0;
   specular[2] = 1.0;
   specular[3] = 1.0;

   diffuse[0] = 0.1;
   diffuse[1] = 0.5;
   diffuse[2] = 0.8;
   diffuse[3] = 1.0;

   ambient[0] = .7;
   ambient[1] = .7;
   ambient[2] = .7;
   ambient[3] = 1.0;

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

   init();

   glutMainLoop();
}