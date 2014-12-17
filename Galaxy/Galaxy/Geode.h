#ifndef _GEODE_H
#define _GEODE_H

#include "Node.h"
#include "Vector3.h"

class Geode : public Node
{
public:
   float r;
   float g;
   float b;

   virtual void render() = 0;
   void draw(Matrix4);
};
#endif