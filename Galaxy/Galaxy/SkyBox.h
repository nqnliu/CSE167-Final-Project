#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "Matrix4.h"

#include <Windows.h>
#include "GLee.h"
#include <GL/glut.h>

class SkyBox
{
private:
	GLuint textures[6];
	Matrix4 M;

public:
   SkyBox::SkyBox();
   void render( float size = 1000 );
   unsigned char* loadPPM(const char* filename, int& width, int& height);
   void loadTexture(GLuint texture, const char* filename);
   void createCubeMap();

   void scale(float);
   void rotateY(float);
   void translate(float, float, float);

};
#endif