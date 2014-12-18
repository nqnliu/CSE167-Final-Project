#ifndef _SPACESHIP_H
#define _SPACESHIP_H
#include "Vector3.h"
#include "Matrix4.h"
#include "shader.h"
#include <vector>

class SpaceShip
{
public:
   Matrix4 modelToWorld;
   std::vector<Vector3> positions;
   std::vector<Vector3> normals;


   SpaceShip::SpaceShip();
   void render();
   void scale(double s);
   void translate(float x, float y, float z);
};
#endif