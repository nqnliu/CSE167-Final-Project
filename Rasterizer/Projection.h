#ifndef _PROJECTION_H_
#define _PROJECTION_H_

#include "Matrix4.h"

class Projection
{
public:
   Matrix4 matrix;

   Projection::Projection(double, double, double, double);

   void set(double, double, double, double);

   Matrix4* getMatrix();
};
#endif