#include "Earth.h"
#include "SOIL.h"

Earth::Earth(float size, char * colorMap, char* bumpMap, float velocity) 
   : Planet(size, colorMap, bumpMap, velocity)
{

}

void Earth::setUpShader()
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

   glActiveTexture(GL_TEXTURE2);
   night_id = SOIL_load_OGL_texture
      (
      "Textures/earthlights1k.jpg",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_TEXTURE_REPEATS
      );
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glBindTexture(GL_TEXTURE_2D, night_id);

   bumpMap = new Shader("bump.vert", "earth.frag", true);
   bumpMap->bind();
   uniformTex0 = glGetUniformLocation(bumpMap->pid, "colorMap");
   glUniform1i(uniformTex0, 0);
   uniformTex0 = glGetUniformLocation(bumpMap->pid, "normalMap");
   glUniform1i(uniformTex0, 1);
   uniformTex0 = glGetUniformLocation(bumpMap->pid, "skyMap");
   glUniform1i(uniformTex0, 2);
   bumpMap->unbind();

   textureMap->bind();
   uniformTex0 = glGetUniformLocation(textureMap->pid, "colorMap");
   glUniform1i(uniformTex0, 0);
   textureMap->unbind();
}