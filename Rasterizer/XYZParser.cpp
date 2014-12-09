#include "XYZParser.h"
#include "Vector3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
void XYZParser::parse(char* filename, std::vector<Vector3>* points, std::vector<Vector3>* normals)
{
   std::ifstream myFile;            //creates stream myFile
   myFile.open(filename, std::ios_base::in);  //opens .txt file
   FILE * fp;
   fopen_s(&fp, filename, "r");
   double x, y, z, nX, nY, nZ;

   while (fscanf_s(fp, "%lf %lf %lf %lf %lf %lf", &x, &y, &z, &nX, &nY, &nZ) > 1)
   {
      (*points).push_back(Vector3(x, y, z));
      Vector3 normal = Vector3(nX, nY, nZ);
      normal.normalize();
      (*normals).push_back(normal);
   }

   /*
   while (myFile >> x >> y >> z >> nX >> nY >> nZ)
   {
      points.push_back(Vector3(x, y, z));
      normals.push_back(Vector3(nX, nY, nZ));
      cout << x;
   }*/
}