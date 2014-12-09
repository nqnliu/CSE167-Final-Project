#ifndef _POINTCLOUD_H
#define _POINTCLOUD_H

#include "Vector3.h"
#include "Matrix4.h"

#include <vector>
#include <string>

class PointCloud
{
public:
   std::vector<Vector3> positions;
   std::vector<Vector3> normals;
   std::string name;

   Matrix4 model2world;

   Vector3 maxPos;
   Vector3 minPos;

   Vector3 maxNorm;
   Vector3 minNorm;

   PointCloud::PointCloud(char*, std::string);

   void scale(double s);
   void calculateMaxMin();
   void centerInWindow();
   void scaleToWindow();

   Matrix4& getMatrix();
};

#endif