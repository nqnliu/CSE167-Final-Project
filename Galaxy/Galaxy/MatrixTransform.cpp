#include "MatrixTransform.h"
#include "main.h"

MatrixTransform::MatrixTransform()
{
   M = Matrix4();
   M.identity();
}

MatrixTransform::MatrixTransform(Matrix4 matrix)
{
  M = matrix;
}

void MatrixTransform::draw(Matrix4 C)
{
   C = C * M;
   Group::draw(C);
}