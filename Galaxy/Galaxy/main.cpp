#ifdef _WIN32
#include <windows.h>
#endif

#include "main.h"

#include <iostream>
#include <GL/glut.h>

using namespace std;
static int window_width = 512, window_height = 512;

namespace Globals
{
};

void displayCallback()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

   glFlush();
   glutSwapBuffers();
}

// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
   cerr << "Window::reshapeCallback called" << endl;
   glViewport(0, 0, new_width, new_height);  // set new viewport size
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, double(new_width) / (double)new_height, 1.0, 1000.0); // set perspective projection viewing frustum
   glMatrixMode(GL_MODELVIEW);
}

void keyboardCallback(unsigned char key, int, int)
{
}

void specialKeysCallback(int key, int x, int y) {
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(window_width, window_height);
   glutCreateWindow("Galaxy");

   glutReshapeFunc(reshapeCallback);
   glutDisplayFunc(displayCallback);
   glutKeyboardFunc(keyboardCallback);
   glutSpecialFunc(specialKeysCallback);
   glutMainLoop();
}