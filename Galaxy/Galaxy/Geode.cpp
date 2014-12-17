#include "Geode.h"
#include "main.h"
#include <iostream>
#include <GL/glut.h>

void Geode::draw(Matrix4 C)
{ 
   C.transpose();
   glPushMatrix();
   glLoadMatrixd(C.getPointer());
   render();
   glPopMatrix();
}