#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "Matrix4.h"

class Viewport
{
public:
   Matrix4 matrix;

   Viewport::Viewport(int, int, int, int);

   void set(int, int, int, int);

   Matrix4* getMatrix();
};
#endif