#include "Geode.h"
#include <GL/glut.h>

void Geode::draw(Matrix4 C)
{
   glMatrixMode(GL_MODELVIEW);
   render();
}