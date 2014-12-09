#include "Camera.h"
#include "Vector3.h"

Camera::Camera()
{
   C = Matrix4();
   C.identity();
}

Camera::Camera(Vector3 e, Vector3 d, Vector3 up)
{
   Camera::e = e;
   Camera::d = d;
   Camera::up = up;

   Vector3 z = e - d;
   z.normalize();
   Vector3 x = up.cross(z);
   x.normalize();
   Vector3 y = z.cross(x);
   y.normalize();

   Matrix4 rotation = Matrix4();
   rotation.identity();

   rotation.set(0, 0, x.x);
   rotation.set(1, 0, x.y);
   rotation.set(2, 0, x.z);

   rotation.set(0, 1, y.x);
   rotation.set(1, 1, y.y);
   rotation.set(2, 1, y.z);

   rotation.set(0, 2, z.x);
   rotation.set(1, 2, z.y);
   rotation.set(2, 2, z.z);

   rotation.transpose();

   Matrix4 translation = Matrix4::makeTranslate(-e.x, -e.y, -e.z);
   // create two temp matrix for rotation and translation
   // rotation = x, y z

   C = rotation * translation;
   // translation inverse = -e

   //C.print("");

   //C.transpose(); // change to column major
}

GLdouble* Camera::getGLMatrix()
{
   return C.getPointer();
}

