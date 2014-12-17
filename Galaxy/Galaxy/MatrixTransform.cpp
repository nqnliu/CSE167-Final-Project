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

void MatrixTransform::scale(float s)
{
	Matrix4 scale;

	scale = scale.makeScale(s,s,s);
	M = M * scale;
}

void MatrixTransform::rotateY(float deg)
{
	Matrix4 rotate;

	rotate = rotate.makeRotateY(deg);
	M =  M * rotate;
}