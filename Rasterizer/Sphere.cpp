#include "Sphere.h"
#include <GL/glut.h> 

void Sphere::render()
{
   glutSolidSphere(1, 50, 50);
}

/*
/*scalex - scaling of sphere around x-axis
scaley - scaling of sphere around y-axis
r - radius of sphere
*//*
void drawHalfSphere(const int scaley, const int scalex, GLfloat r) {
   int i, j;
   GLfloat v[scalex*scaley][3];

   for (i = 0; i<scalex; ++i) {
      for (j = 0; j<scaley; ++j) {
         v[i*scaley + j][0] = r*cos(j * 2 * M_PI / scaley)*cos(i*M_PI / (2 * scalex));
         v[i*scaley + j][1] = r*sin(i*M_PI / (2 * scalex));
         v[i*scaley + j][2] = r*sin(j * 2 * M_PI / scaley)*cos(i*M_PI / (2 * scalex));
      }
   }

   glBegin(GL_QUADS);
   for (i = 0; i<scalex - 1; ++i) {
      for (j = 0; j<scaley; ++j) {
         glVertex3fv(v[i*scaley + j]);
         glVertex3fv(v[i*scaley + (j + 1) % scaley]);
         glVertex3fv(v[(i + 1)*scaley + (j + 1) % scaley]);
         glVertex3fv(v[(i + 1)*scaley + j]);
      }
   }
   glEnd();
}*/