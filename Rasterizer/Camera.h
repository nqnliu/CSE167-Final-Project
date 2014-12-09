#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector3.h"
#include "Matrix4.h"
#include <GL/glut.h>

class Camera
{
public:
   Vector3 e; // center of projection
   Vector3 d; // look at point
   Vector3 up; // up vector
   Matrix4 C; // camera matrix, row major

   Camera::Camera();
   Camera::Camera(Vector3, Vector3, Vector3);

   GLdouble* getGLMatrix();
};

#endif