#include "MatrixTransform.h"

MatrixTransform::MatrixTransform(Matrix4 M)
{
   MatrixTransform::M = M;
}

void MatrixTransform::draw(Matrix4 C)
{
   C = C * M;
   Group::draw(C);
}