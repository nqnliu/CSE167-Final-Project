#include <math.h>
#include <iostream>
#include <iomanip> 

#include "Matrix4.h"

using namespace std;

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0.0;
    }
  }
} 

Matrix4::Matrix4(float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8,
   float v9, float v10, float v11, float v12, float v13, float v14, float v15, float v16)
{
   m[0][0] = v1;
   m[0][1] = v2;
   m[0][2] = v3;
   m[0][3] = v4;
   m[1][0] = v5;
   m[1][1] = v6;
   m[1][2] = v7;
   m[1][3] = v8;
   m[2][0] = v9;
   m[2][1] = v10;
   m[2][2] = v11;
   m[2][3] = v12;
   m[3][0] = v13;
   m[3][1] = v14;
   m[3][2] = v15;
   m[3][3] = v16;
}

Matrix4 Matrix4::operator=(const Matrix4 &m2)
{
  if (this != &m2)
  {
    for (int i=0; i<4; ++i)
    {
      for (int j=0; j<4; ++j)
      {
        m[i][j] = m2.m[i][j];
      }
    }
  }
  return *this;
}

Matrix4 Matrix4::operator*(const Matrix4 &m2)
{
   Matrix4 newMatrix = Matrix4();

   for (int row = 0; row < 4; row++)
   {
      for (int col = 0; col < 4; col++)
      {
         for (int inner = 0; inner < 4; inner++)
         {
            newMatrix.m[row][col] += m[row][inner] * m2.m[inner][col];
         }
      }
   }

   return newMatrix;
}

Vector4 Matrix4::operator*(const Vector4 &v)
{
   double newXyzw[] = { 0, 0, 0, 0 };
   double xyzw[] = { v.x, v.y, v.z, v.w };

   for (int row = 0; row < 4; row++)
   {
      for (int col = 0; col < 4; col++)
      {
         newXyzw[row] += m[row][col] * xyzw[col];
      }
   }

   return Vector4(newXyzw[0], newXyzw[1], newXyzw[2], newXyzw[3]);
}

// return pointer to matrix elements
double* Matrix4::getPointer()
{
  return &m[0][0];
}

// set matrix to identity matrix
void Matrix4::identity()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      if (i==j) 
        m[i][j] = 1.0; 
      else 
        m[i][j] = 0.0;
    }
  }
}

// transpose the matrix (mirror at diagonal)
void Matrix4::transpose()
{
  Matrix4 temp;
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      temp.m[j][i] = m[i][j];
    }
  }
  *this = temp;  // copy temporary values to this matrix
}


double Matrix4::get(int i, int j)
{
   return m[i][j];
}

void Matrix4::set(int i, int j, double value)
{
   m[i][j] = value;
}

Matrix4 Matrix4::makeRotateX(double angle)
{
   Matrix4 rotateMatrix = Matrix4();
   rotateMatrix.identity();

   angle = angle / 180.0 * M_PI;  
   rotateMatrix.m[1][1] = cos(angle);
   rotateMatrix.m[1][2] = -sin(angle);
   rotateMatrix.m[2][1] = sin(angle);
   rotateMatrix.m[2][2] = cos(angle);

   return rotateMatrix;
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
Matrix4 Matrix4::makeRotateY(double angle)
{
   Matrix4 rotateMatrix = Matrix4();
   rotateMatrix.identity();

   angle = angle / 180.0 * M_PI;
   rotateMatrix.m[0][0] = cos(angle);
   rotateMatrix.m[0][2] = sin(angle);
   rotateMatrix.m[2][0] = -sin(angle);
   rotateMatrix.m[2][2] = cos(angle);

   return rotateMatrix;
}

Matrix4 Matrix4::makeRotateZ(double angle)
{
   Matrix4 rotateMatrix = Matrix4();
   rotateMatrix.identity();

   angle = angle / 180.0 * M_PI;
   rotateMatrix.m[0][0] = cos(angle);
   rotateMatrix.m[0][1] = -sin(angle);
   rotateMatrix.m[1][0] = sin(angle);
   rotateMatrix.m[1][1] = cos(angle);

   return rotateMatrix;
}

Matrix4 Matrix4::makeRotate(double angle, const Vector3& axis)
{
   Matrix4 rotateMatrix = Matrix4();
   rotateMatrix.identity();

   Vector3 unitVector = Vector3(axis.v[0], axis.v[1], axis.v[2]);
   unitVector.normalize();

   angle = angle / 180.0 * M_PI;
   double cosA = cos(angle);
   double sinA = sin(angle);

   rotateMatrix.m[0][0] = 1 + (1 - cosA) * (unitVector.v[0] * unitVector.v[0] - 1);
   rotateMatrix.m[0][1] = -unitVector.v[2] * sinA + (1 - cosA) * unitVector.v[0] * unitVector.v[1];
   rotateMatrix.m[0][2] = unitVector.v[1] * sinA + (1 - cosA) * unitVector.v[0] * unitVector.v[2];
   rotateMatrix.m[1][0] = unitVector.v[2] * sinA + (1 - cosA) * unitVector.v[1] * unitVector.v[0];
   rotateMatrix.m[1][1] = 1 + (1 - cosA) * (unitVector.v[1] * unitVector.v[1] - 1);
   rotateMatrix.m[1][2] = -unitVector.v[0] * sinA + (1 - cosA) * unitVector.v[1] * unitVector.v[2];
   rotateMatrix.m[2][0] = -unitVector.v[1] * sinA + (1 - cosA) * unitVector.v[2] * unitVector.v[0];
   rotateMatrix.m[2][1] = unitVector.v[0] * sinA + (1 - cosA) * unitVector.v[2] * unitVector.v[1];
   rotateMatrix.m[2][2] = 1 + (1 - cosA) * (unitVector.v[2] * unitVector.v[2] - 1);

   return rotateMatrix;
}

Matrix4 Matrix4::makeScale(double sx, double sy, double sz)
{
   Matrix4 scaleMatrix = Matrix4();
   scaleMatrix.identity();

   scaleMatrix.m[0][0] = sx;
   scaleMatrix.m[1][1] = sy;
   scaleMatrix.m[2][2] = sz;

   return scaleMatrix;
}

Matrix4 Matrix4::makeTranslate(double tx, double ty, double tz)
{
   Matrix4 translateMatrix = Matrix4();
   translateMatrix.identity();

   translateMatrix.m[0][3] = tx;
   translateMatrix.m[1][3] = ty;
   translateMatrix.m[2][3] = tz;

   return translateMatrix;
}

void Matrix4::print(string comment)
{
   cout << setprecision(2) << std::fixed << comment;

   for (int i = 0; i < 4; i++)
   {
      cout << "[" << std::setw(8) << m[i][0];

      for (int j = 1; j < 4; j++)
      {
         cout << ", " << std::setw(8) << std::setfill(' ') << ("%.2f", m[i][j]);
      }
      cout << "]\n";
   }
   cout << "\n";
}