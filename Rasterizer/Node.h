#ifndef _NODE_H
#define _NODE_H

#include "Matrix4.h"

class Node
{
public:
   virtual void draw(Matrix4) = 0;
   virtual void update() = 0;
};
#endif