#include "Planet.h"
#include "SOIL.h"
#include "main.h"
#include <stdlib.h>
#include <iostream>
#define NUM_DIVS 50
#define PI 3.14159
Planet::Planet(float size, char * texture, char * normal, float v)
{
   Planet::size = size;
   texture_file = texture;
   normal_file = normal;
   glowcolor[0] = 1.0;
   glowcolor[1] = 0;
   glowcolor[2] = 0;
   bump = true;
   glowFlag = true;
   orbit_velocity = v;
}

Planet::Planet()
{
}

void Planet::render()
{
   if (bumpMap && bump)
      bumpMap->bind();
   else
      textureMap->bind();

   glPushMatrix();
   glColor3f(color[0], color[1], color[2]);
   glRotatef(90, 1, 0, 0);
   glScalef(size, size, size);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
   mySphere2();

   if (bumpMap && bump)
      bumpMap->unbind();
   else
	   textureMap->unbind();
   if (glowFlag)
	   renderGlow(1,1,1);
   glPopMatrix();
}

void Planet::glow(float s)
{
   //	lighting->bind();

   glPushMatrix();
   glColor4f(glowcolor[0], glowcolor[1], glowcolor[2], s);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glowcolor);
   glutSolidSphere(1.0, 50, 50);
   glPopMatrix();

   //	lighting->unbind();
}

void Planet::renderGlow(float r, float g, float b)
{
   glowcolor[0] = r;
   glowcolor[1] = g;
   glowcolor[2] = b;

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);

   float scaler;
   int n;
   float range;
   float step;

   range = 1.1;
   n = range * 40 - 40;
   step = .3 / n;

   for (int i = n; i >= 0; --i)
   {
      scaler = range - .026*(float)i;

      glPushMatrix();
      glScalef(scaler, scaler, scaler);
      glow(step);
      glPopMatrix();
   }

   glDisable(GL_BLEND);
}

void Planet::setUpShader()
{
   textureMap = new Shader("texture.vert", "texture.frag", true);
   GLint uniformTex0;

   glActiveTexture(GL_TEXTURE0);
   texture_id = SOIL_load_OGL_texture
      (
      texture_file,
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_TEXTURE_REPEATS
      );
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glBindTexture(GL_TEXTURE_2D, texture_id);

   if (bump) {
      glActiveTexture(GL_TEXTURE1);
      normal_id = SOIL_load_OGL_texture
         (
         normal_file,
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_TEXTURE_REPEATS
         );
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glBindTexture(GL_TEXTURE_2D, normal_id);
      bumpMap = new Shader("bump.vert", "bump.frag", true);
      bumpMap->bind();
      uniformTex0 = glGetUniformLocation(bumpMap->pid, "colorMap");
      glUniform1i(uniformTex0, 0);
      uniformTex0 = glGetUniformLocation(bumpMap->pid, "normalMap");
      glUniform1i(uniformTex0, 1);
      bumpMap->unbind();

      textureMap->bind();
      uniformTex0 = glGetUniformLocation(textureMap->pid, "colorMap");
      glUniform1i(uniformTex0, 0);
      textureMap->unbind();
   }
}

void Planet::setGlow(float r, float g, float b)
{
   glowcolor[0] = r;
   glowcolor[1] = g;
   glowcolor[2] = b;
}

// Modified from the glu source code for gluSphere() for a multi-textured unit sphere with normals
void Planet::mySphere2()
{
   GLint uniformTan;
   if (bumpMap) uniformTan = glGetAttribLocation(bumpMap->pid, "tangento");
   GLint i, j;
   GLfloat sintheta[NUM_DIVS + 1];
   GLfloat costheta[NUM_DIVS + 1];
   GLfloat sinphi[NUM_DIVS + 1];
   GLfloat cosphi[NUM_DIVS + 1];
   GLfloat angle;
   GLfloat sintemp1 = 0.0, sintemp2 = 0.0;
   GLfloat costemp1 = 0.0, costemp2 = 0.0;
   GLint slices = NUM_DIVS;
   GLint stacks = NUM_DIVS;
   GLfloat x, y, z;
   GLfloat s, t;
   GLfloat tangent[3];
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texture_id);
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_2D, normal_id);
   for (i = 0; i < slices; i++) {
      angle = 2.0 * PI * i / slices;
      sintheta[i] = sin(angle);
      costheta[i] = cos(angle);
   }

   for (j = 0; j <= stacks; j++) {
      angle = PI / 2.0 - PI * j / stacks;
      sinphi[j] = sin(angle);
      cosphi[j] = cos(angle);
   }
   /* Make sure it comes to a point */
   cosphi[0] = 0;
   cosphi[stacks] = 0;
   sintheta[slices] = sintheta[0];
   costheta[slices] = costheta[0];

   for (j = 0; j < stacks; j++) {
      sintemp1 = sinphi[j];
      sintemp2 = sinphi[j + 1];
      costemp1 = cosphi[j];
      costemp2 = cosphi[j + 1];

      glBegin(GL_QUAD_STRIP);
      for (i = 0; i <= slices; i++) {
         // Compute coordinates
         x = costheta[i] * costemp2;
         y = sintheta[i] * costemp2;
         z = sintemp2;
         s = 1 - (float)i / slices;
         t = 1 - (float)(j + 1) / stacks;
         tangent[0] = -costheta[i] * sintemp2;
         tangent[1] = -sintheta[i] * sintemp2;
         tangent[2] = costemp2;
         // Set vectors
         glNormal3f(x, y, z);
         glMultiTexCoord2f(GL_TEXTURE0, s, t);
         glMultiTexCoord2f(GL_TEXTURE1, s, t);
         // TODO: Set tangent vector in shader
         if (bumpMap) glVertexAttrib3f(uniformTan, tangent[0], tangent[1], tangent[2]);
         glVertex3f(x, y, z);

         // Compute coordinates
         x = costheta[i] * costemp1;
         y = sintheta[i] * costemp1;
         z = sintemp1;
         s = 1 - (float)i / slices;
         t = 1 - (float)j / stacks;
         tangent[0] = -costheta[i] * sintemp1;
         tangent[1] = -sintheta[i] * sintemp1;
         tangent[2] = costemp1;
         // Set vectors
         glNormal3f(x, y, z);
         glMultiTexCoord2f(GL_TEXTURE0, s, t);
         glMultiTexCoord2f(GL_TEXTURE1, s, t);
         if (bumpMap) glVertexAttrib3f(uniformTan, tangent[0], tangent[1], tangent[2]);
         // TODO: Set tangent vector in shader
         glVertex3f(x, y, z);
      }
      glEnd();
   }
}