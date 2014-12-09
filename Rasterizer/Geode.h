#ifndef _GEODE_H
#define _GEODE_H

#include "Node.h"

class Geode : public Node
{
public:
   virtual void render() = 0;
   void draw(Matrix4);
};
#endif