#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>

#include "Vector4.h"
#include "House.h"
#include "Camera.h"
#include "PointCloud.h"
#include "Viewport.h"
#include "Projection.h"
#include "PointLight.h"

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
static float* zBuffer = new float[window_width * window_height];
static int mode = 0;
static int HOUSEMODE = 0;
static int BUNNYMODE = 1;
static int DRAGONMODE = 2;

using namespace std;

namespace Globals
{
   Camera camera = Camera(Vector3(0, 0, 20), Vector3(0, 0, 0), Vector3(0, 1, 0));
   Viewport viewport = Viewport(0, 0, window_width, window_height);
   Projection projection = Projection(60.0, double(window_width) / double(window_height), 1.0, 1000.0);
   PointCloud bunny = PointCloud("bunny.xyz", "bunny");
   PointCloud dragon = PointCloud("dragon.xyz", "dragon");
   PointLight light = PointLight(Vector3(-3.0, 3.0, 0.0), Vector3(1.0, 1.0, 1.0));
};

Matrix4* currModelMatrix = &Globals::bunny.getMatrix();
bool shade = false;
bool bufferOn = false;
bool varyPoints = false;

struct Color    // generic color class
{
   float r, g, b;  // red, green, blue
};

/*
void loadData()
{
   // point cloud parser goes here
   // parse both bunny and dragon

}*/

// Clear frame buffer
void clearBuffer()
{
   Color clearColor = { 0.0, 0.0, 0.0 };   // clear color: black
   for (int i = 0; i<window_width*window_height; ++i)
   {
      pixels[i * 3] = clearColor.r;
      pixels[i * 3 + 1] = clearColor.g;
      pixels[i * 3 + 2] = clearColor.b;
      zBuffer[i] = 1.0;
   }
}

bool verifyRange(double n, double lower, double upper)
{
   return n >= lower && n <= upper;
}

float getZValue(int x, int y)
{
   int offset = y*window_width + x;
   return zBuffer[offset];
}

void setZValue(int x, int y, float z)
{
   int offset = y*window_width + x;
   zBuffer[offset] = z;
}

bool bufferCheck(int x, int y, float z)
{
   if (!bufferOn) return true;

   if (z <= getZValue(x, y))
   {
      setZValue(x, y, z);
      return true;
   }
   return false;
}


void drawPixel(int x, int y, float z, float r, float g, float b)
{
   int offset = y*window_width * 3 + x * 3;
   if (verifyRange(offset, 0, window_width * window_height * 3 - 1) && bufferCheck(x, y, z))
   {
      pixels[offset] = r;
      pixels[offset + 1] = g;
      pixels[offset + 2] = b;
   }
}

void drawLine(int startX, int endX, int y, float z, float r, float g, float b)
{
   int mid = (startX + endX) / 2;
   for (int x = startX; x <= endX; x++)
   {
      float newZ = z - (std::abs(x - mid) / 150.0);
      drawPixel(x, y, newZ, r, g, b);
   }
}

// Draw a point into the frame buffer
void drawPoint(int x, int y, float z, float r, float g, float b)
{
   float size = z;
   if (!verifyRange(x, 0, window_width - 1) || !verifyRange(y, 0, window_height - 1))
   {
      return;
   }
   if (!varyPoints)
   {
      drawPixel(x, y, z, r, g, b);
   }
   else if (varyPoints)
   {
      size = (1 - size) * window_height / 15;
    
      for (int i = 0; i < size; i++){
         for (int j = 0; j < size; j++)
         {
            drawPixel(x + i, y + j, z, r, g, b);
         }
      }
   }
}

void rasterizePoint(Vector3 point3, Vector3 normal, Matrix4 modelMatrix)
{
   Vector4 point = Vector4(point3.x, point3.y, point3.z, 1.0);
   point = modelMatrix * point;

   double r = 1.0;
   double g = 1.0;
   double b = 1.0;
   //Vector3(0.8, 0.4, 0.2);
   if (shade)
   {
      Vector4 normal4 = Vector4(normal.x, normal.y, normal.z, 1.0);
      normal4 = modelMatrix * normal4;
      Vector3 newColor = Globals::light.calculateColor(Vector3(point.x, point.y, point.z), 
         Vector3(normal4.x, normal4.y, normal4.z), Vector3(0.776471, 0.443137, 0.443137));
      r = newColor.x;
      g = newColor.y;
      b = newColor.z;
   }

   point = Globals::camera.C * point;
   point = Globals::projection.matrix * point;
   point.dehomogenize();
   point = Globals::viewport.matrix * point;

   drawPoint(point.x, point.y, point.z, r, g, b);
}

void rasterize()
{
   // Put your main rasterization loop here
   // It should go over the point model and call drawPoint for every point in it

   if (mode == HOUSEMODE)
   {
      int len = 60;
      int index;
      int index2;

      for (int i = 0; i < len; i++)
      {
         bool one = i == false;
         index = House::indices[i];
         index2 = index * 3;
         Vector4 point = Vector4(House::vertices[index2], House::vertices[index2 + 1], House::vertices[index2 + 2], 1.0);
         if (one) point.print("p = ");
         point = Globals::camera.C * point;
         if (one)
         {
            Globals::camera.C.print("Camera matrix:\n");
            point.print("Cp = ");
         }
         point = Globals::projection.matrix * point;
         if (one) point.print("PCp = ");
         point.dehomogenize();
         if (one) point.print("DPCp = ");
         point = Globals::viewport.matrix * point;
         if (one) point.print("VDPCp = ");
         
         if (verifyRange(point.x, 0, window_width) && verifyRange(point.y, 0, window_height) && bufferCheck(point.x, point.y, point.z / point.w))
         {
            drawPixel(point.x, point.y, point.z, 1.0, 1.0, 1.0);
         }
      }
   }
   else if (mode == BUNNYMODE)
   {  
      std::vector<Vector3> bunnyPositions = Globals::bunny.positions;
      std::vector<Vector3> bunnyNormals = Globals::bunny.normals;

      for (int i = 0; i < bunnyPositions.size(); i++)
      {         
         rasterizePoint(bunnyPositions[i], bunnyNormals[i], Globals::bunny.model2world);
      }
   }
   else if (mode == DRAGONMODE)
   {
      std::vector<Vector3> dragonPositions = Globals::dragon.positions;
      std::vector<Vector3> dragonNormals = Globals::dragon.normals;

      for (int i = 0; i < dragonPositions.size(); i++)
      {
         rasterizePoint(dragonPositions[i], dragonNormals[i], Globals::dragon.model2world);
      }
   }
}

void displayCallback()
{
   clearBuffer();
   rasterize();

   // glDrawPixels writes a block of pixels to the framebuffer
   glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

   glutSwapBuffers();
}

void setViewport(int x, int y, int width, int height)
{
   Globals::viewport.set(x, y, width, height);
}

void setProjection(double fovY, double aspect, double zNear, double zFar)
{
   Globals::projection.set(fovY, aspect, zNear, zFar);
}

// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
   window_width = new_width;
   window_height = new_height;
   delete[] pixels;
   pixels = new float[window_width * window_height * 3];
   delete[] zBuffer;
   zBuffer = new float[window_width * window_height];
   setViewport(0, 0, window_width, window_height);
   setProjection(60.0, double(window_width) / double(window_height), 1.0, 1000.0);
   displayCallback();
}

void keyboardCallback(unsigned char key, int, int)
{
   cerr << "Key pressed: " << key << endl;
   switch (key) {
      case '1':
      {
         shade = false;
         varyPoints = false;
         bufferOn = false;
         break;
      }
      case '2':
      {
         shade = true;
         bufferOn = false;
         varyPoints = false;
         break;
      }
      case '3':
      {
         varyPoints = false;
         bufferOn = true;
         shade = true;
         break;
      }
      case '4':
      {
         varyPoints = true;
         bufferOn = true;
         shade = true;
         break;
      }
      case '5':
      {
         varyPoints = true;
         bufferOn = true;
         shade = true;
         break;
      }
      case 's':
      {
         Matrix4 scaleMatrix = Matrix4::makeScale(.75, .75, .75);
         *currModelMatrix = scaleMatrix * *currModelMatrix;
         break;
      }
      case 'S':
      {
         Matrix4 scaleMatrix = Matrix4::makeScale(1.25, 1.25, 1.25);
         *currModelMatrix = scaleMatrix * *currModelMatrix;
         break;
      }
      case 'y':
      {
         Matrix4 rotateMatrix = Matrix4::makeRotateY(-10);
         *currModelMatrix = rotateMatrix * *currModelMatrix;
         break;
      }
      case 'Y':
      {
         Matrix4 rotateMatrix = Matrix4::makeRotateY(10);
         *currModelMatrix = rotateMatrix * *currModelMatrix;
         break;
      }
   }
   displayCallback();
}

void specialKeysCallback(int key, int x, int y) {
   switch (key) {
      case GLUT_KEY_F1:
      {
         mode = BUNNYMODE;
         currModelMatrix = &Globals::bunny.getMatrix();
         break;
      }
      case GLUT_KEY_F2:
      {
         mode = DRAGONMODE;
         currModelMatrix = &Globals::dragon.getMatrix();
         break;
      }
   }

   displayCallback();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(window_width, window_height);
   glutCreateWindow("Rasterizer");

   //loadData();

   glutReshapeFunc(reshapeCallback);
   glutDisplayFunc(displayCallback);
   glutKeyboardFunc(keyboardCallback);
   glutSpecialFunc(specialKeysCallback);
   glutMainLoop();
}