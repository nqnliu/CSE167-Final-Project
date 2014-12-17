#ifndef _NODE_H
#define _NODE_H

#include "Matrix4.h"

class Node
{
public:
   virtual void draw(Matrix4) = 0;
};
#endif