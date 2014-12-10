#include "Sun.h"
#include "GL\glut.h"

Sun::Sun()
{

}

void Sun::render()
{
   float specular[] = { 1.0, 1.0, 1.0, 1.0 };
   float ambient[] = { .5, .5, .5, 1.0 };
   float position[] = { 0, 0.0, 0.0, 1.0 };	// lightsource position
   float shininess[] = { 100.0 };
   float diffuse[] = { 0.0, 0.0, 0.0, 0.0 };
   // Generate light source:
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glEnable(GL_LIGHT0);

   float color[3] = { 1.0, 1.0, 0.8 };
   glColor3f(color[0], color[1], color[2]);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
   glutSolidSphere(1.0, 50, 50);
}