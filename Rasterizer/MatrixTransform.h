#ifndef _MATRIXTRANSFORM_H
#define _MATRIXTRANSFORM_H

#include "Group.h"

class MatrixTransform : public Group
{
public:
   Matrix4 M;

   MatrixTransform(Matrix4);

   void draw(Matrix4);
};

#endif