#include "PointCloud.h"
#include "XYZParser.h"
#include "Vector3.h"
#include "Matrix4.h"

#include <vector>
#include <iostream>
#include <algorithm>

PointCloud::PointCloud(char * fileName, std::string name)
{
   PointCloud::name = name;

   positions = std::vector<Vector3>();
   normals = std::vector<Vector3>();
   XYZParser::parse(fileName, &positions, &normals);

   model2world = Matrix4();
   model2world.identity();

   centerInWindow();
   scaleToWindow();
}

void PointCloud::scale(double s)
{
   Matrix4 scaleMatrix = Matrix4::makeScale(s, s, s);
   model2world = scaleMatrix * model2world;
}

void PointCloud::centerInWindow()
{
   calculateMaxMin();
   double midX = ((maxPos.x - minPos.x) / 2.0) + minPos.x;
   double midY = ((maxPos.y - minPos.y) / 2.0) + minPos.y;
   double midZ = ((maxPos.z - minPos.z) / 2.0) + minPos.z;
   
   Matrix4 translationMatrix = Matrix4::makeTranslate(-midX, -midY, -midZ);
   translationMatrix.print("Centering translation matrix for " + name + ":\n");
   model2world = model2world * translationMatrix;
}

void PointCloud::calculateMaxMin()
{
   maxPos = Vector3(positions[0].x, positions[0].y, positions[0].z);
   minPos = Vector3(positions[0].x, positions[0].y, positions[0].z);

   for (int i = 1; i < positions.size(); i++)
   {
      minPos.x = std::min(minPos.x, positions[i].x);
      minPos.y = std::min(minPos.y, positions[i].y);
      minPos.z = std::min(minPos.z, positions[i].z);

      maxPos.x = std::max(maxPos.x, positions[i].x);
      maxPos.y = std::max(maxPos.y, positions[i].y);
      maxPos.z = std::max(maxPos.z, positions[i].z);
   }

   minPos.print("Min position coords for " + name + ": ");
   std::cout << "\n";
   maxPos.print("Max position coords for " + name + ": ");
   std::cout << "\n";
}

void PointCloud::scaleToWindow()
{
   double angle = (30.0 / 180.0) * M_PI;
   double ratio = 2 * (20.0 * tan(angle)) / (maxPos.x - minPos.x);

   Matrix4 scaleMatrix = Matrix4::makeScale(ratio, ratio, ratio);
   scaleMatrix.print("Scale matrix for " + name + ":\n");
   model2world = scaleMatrix * model2world;
}

Matrix4& PointCloud::getMatrix()
{
   return model2world;
}
