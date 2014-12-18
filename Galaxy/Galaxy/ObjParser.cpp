#include "ObjParser.h"
#include "Vector3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
void ObjParser::parse(char* filename, std::vector<Vector3>* points, std::vector<Vector3>* colors,
   std::vector<Vector3>* normals, std::vector<Vector3>* faces)
{
   FILE* fp;     // file pointer
   float x, y, z;  // vertex coordinates
   float r, g, b;  // vertex color
   int c1, c2;    // characters read from file
   int index1, index2, index3, index4, index5, index6;
   char ignore[1024];

   fopen_s(&fp, filename, "rb");
   if (fp == NULL) { cerr << "error loading file" << endl; exit(-1); }

   do {
      c1 = fgetc(fp);
      c2 = fgetc(fp);
      if ((c1 == 'v') && (c2 == ' '))
      {
         fscanf(fp, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
         points->push_back(Vector3(x, y, z));
         colors->push_back(Vector3(r, g, b));
      }
      else if ((c1 == 'v') && (c2 == 'n'))
      {
         fscanf(fp, " %f %f %f", &x, &y, &z);
         Vector3 normal = Vector3(x, y, z);
         normal.normalize();
         normals->push_back(normal);
      }
      else if ((c1 == '#'))
      {
         fgets(ignore, sizeof(ignore), fp);
      }
      else if ((c1 == 'f') && (c2 == ' '))
      {
         fscanf(fp, "%d%*2c%d %d%*2c%d %d%*2c%d", &index1, &index2, &index3, &index4, &index5, &index6);
         faces->push_back(Vector3(index1, index3, index5));
      }
   } while (c1 != EOF);

   // parse other cases and loop over lines of file

   fclose(fp);   // make sure you don't forget to close the file when done
}

void ObjParser::parse(char * filename, std::vector<Vector3> & vertices, std::vector<Vector3> & normals)
{
   std::vector< unsigned int > vertexIndices, normalIndices;
   std::vector< Vector3 > temp_vertices;
   std::vector< Vector3 > temp_normals;
   float x;
   float y;
   float z;

   FILE * file = fopen(filename, "r");
   if (file == NULL){
      printf("Impossible to open the file !\n");
      return;
   }

   while (1){
      char lineHeader[128];
      // read the first word of the line
      int res = fscanf(file, "%s", lineHeader);
      if (res == EOF)
         break; // EOF = End Of File. Quit the loop.

      // else : parse lineHeader
      if (strcmp(lineHeader, "v") == 0){
         fscanf(file, "%f %f %f\n", &x, &y, &z);
         temp_vertices.push_back(Vector3(x, y, z));
      }
      else if (strcmp(lineHeader, "vn") == 0){
         fscanf(file, "%f %f %f\n", &x, &y, &z);
         temp_normals.push_back(Vector3(x, y, z));
      }
      else if (strcmp(lineHeader, "f") == 0){
         std::string vertex1, vertex2, vertex3;
         unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
         int matches = fscanf(file, "%d//%d %d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2],
            &vertexIndex[3], &normalIndex[3]);
         if (matches != 8){
            printf("File can't be read by our simple parser : ( Try exporting with other options\n");
            return;
         }
         vertexIndices.push_back(vertexIndex[0]);
         vertexIndices.push_back(vertexIndex[1]);
         vertexIndices.push_back(vertexIndex[2]);
         vertexIndices.push_back(vertexIndex[3]);
         normalIndices.push_back(normalIndex[0]);
         normalIndices.push_back(normalIndex[1]);
         normalIndices.push_back(normalIndex[2]);
         normalIndices.push_back(normalIndex[3]);
      }
      // For each vertex of each triangle
   }
   for (unsigned int i = 0; i < vertexIndices.size(); i++){
      unsigned int vertexIndex = vertexIndices[i];
      unsigned int normalIndex = normalIndices[i];
      Vector3 vertex = temp_vertices[vertexIndex - 1];
      Vector3 normal = temp_normals[normalIndex - 1];
      vertices.push_back(vertex);
      normals.push_back(normal);
   }
   return;
}