#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#define M_PI 3.14159265358979323846

#include <string>
#include "Vector4.h"
#include "Vector3.h"

class Matrix4
{
protected:
   double m[4][4];   // matrix elements; first index is for rows, second for columns (row-major)

public:
   Matrix4();
   Matrix4 operator=(const Matrix4&);
   Matrix4 operator*(const Matrix4&);
   Vector4 operator*(const Vector4&);

   double* getPointer();
   void identity();
   void transpose();
   double get(int, int);
   void set(int, int, double);

   static Matrix4 makeRotateX(double);
   static Matrix4 makeRotateY(double);
   static Matrix4 makeRotateZ(double);
   static Matrix4 makeRotate(double, const Vector3&);
   static Matrix4 makeScale(double, double, double);
   static Matrix4 makeTranslate(double, double, double);
   void print(std::string);
};

#endif