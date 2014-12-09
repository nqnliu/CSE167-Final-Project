#include "Projection.h"

Projection::Projection(double fovY, double aspect, double zNear, double zFar)
{
   matrix = Matrix4();
   set(fovY, aspect, zNear, zFar);
}

void Projection::set(double fovY, double aspect, double zNear, double zFar)
{
   double fovRadian = (fovY / 180.0) * M_PI;
   double tanFov = tan (fovRadian / 2.0);
   matrix.set(0, 0, 1.0 / (aspect*tanFov));
   matrix.set(1, 1, 1.0 / tanFov);
   matrix.set(2, 2, (zNear + zFar) / (zNear - zFar));
   matrix.set(2, 3, (2 * zNear * zFar) / (zNear - zFar));
   matrix.set(3, 2, -1.0);
}

Matrix4* Projection::getMatrix()
{
   return &matrix;
}