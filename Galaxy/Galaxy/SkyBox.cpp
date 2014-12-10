#include "SkyBox.h"
#include <stdlib.h>
#include <iostream>
#include "GL/glut.h"
#include "main.h"

SkyBox::SkyBox()
{
}

void SkyBox::render()
{
}

/** Load a ppm file from disk.
@input filename The location of the PPM file.  If the file is not found, an error message
will be printed and this function will return 0
@input width This will be modified to contain the width of the loaded image, or 0 if file not found
@input height This will be modified to contain the height of the loaded image, or 0 if file not found
@return Returns the RGB pixel data as interleaved unsigned chars (R0 G0 B0 R1 G1 B1 R2 G2 B2 .... etc) or 0 if an error ocured
*/
unsigned char* SkyBox::loadPPM(const char* filename, int& width, int& height)
{
   const int BUFSIZE = 128;
   FILE* fp;
   unsigned int read;
   unsigned char* rawData;
   char buf[3][BUFSIZE];
   char* retval_fgets;
   size_t retval_sscanf;

   if ((fp = fopen(filename, "rb")) == NULL)
   {
      std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
      width = 0;
      height = 0;
      return NULL;
   }

   // Read magic number:
   retval_fgets = fgets(buf[0], BUFSIZE, fp);

   // Read width and height:
   do
   {
      retval_fgets = fgets(buf[0], BUFSIZE, fp);
   } while (buf[0][0] == '#');
   retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
   width = atoi(buf[1]);
   height = atoi(buf[2]);

   // Read maxval:
   do
   {
      retval_fgets = fgets(buf[0], BUFSIZE, fp);
   } while (buf[0][0] == '#');

   // Read image data:
   rawData = new unsigned char[width * height * 3];
   read = fread(rawData, width * height * 3, 1, fp);
   fclose(fp);
   if (read != 1)
   {
      std::cerr << "error parsing ppm file, incomplete data" << std::endl;
      delete[] rawData;
      width = 0;
      height = 0;
      return NULL;
   }

   return rawData;
}


// load image file into texture object
GLuint SkyBox::loadTexture(char * ppmFile, GLenum side_target)
{
   GLuint texture[1];
   int twidth, theight;   // texture width/height [pixels]
   unsigned char* tdata;  // texture pixel data

   // Load image file
   tdata = loadPPM(ppmFile, twidth, theight);
   if (tdata == NULL) return 0;

   glGenTextures(1, &texture[0]);
   // Set this texture to be the one we are working with
   glBindTexture(GL_TEXTURE_2D, texture[0]);
   // Set bi-linear filtering for both minification and magnification
   // Make sure no bytes are padded:
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   // Select GL_MODULATE to mix texture with polygon color for shading:
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   // Use bilinear interpolation:
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   // Generate the texture
   glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

   return 0;
}

void SkyBox::createCubeMap()
{
   GLint texLoc;
   shade->bind();
   glActiveTexture(GL_TEXTURE1);
   loadTexture("clouds_front.ppm", GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
   //glActiveTexture(GL_TEXTURE1);
   texLoc = glGetUniformLocation(shade->pid, "back");
   glUniform1i(texLoc, 1);
   glActiveTexture(GL_TEXTURE2);
   loadTexture("clouds_back.ppm", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
   //glActiveTexture(GL_TEXTURE2);
   texLoc = glGetUniformLocation(shade->pid, "front");
   glUniform1i(texLoc, 2);
   glActiveTexture(GL_TEXTURE3);
   loadTexture("clouds_left.ppm", GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
   //glActiveTexture(GL_TEXTURE3);
   texLoc = glGetUniformLocation(shade->pid, "left");
   glUniform1i(texLoc, 3);
   glActiveTexture(GL_TEXTURE4);
   loadTexture("clouds_right.ppm", GL_TEXTURE_CUBE_MAP_POSITIVE_X);
   //glActiveTexture(GL_TEXTURE4);
   texLoc = glGetUniformLocation(shade->pid, "right");
   glUniform1i(texLoc, 4);
   glActiveTexture(GL_TEXTURE5);
   loadTexture("clouds_top.ppm", GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
   texLoc = glGetUniformLocation(shade->pid, "top");
   glUniform1i(texLoc, 5);
   shade->unbind();
}