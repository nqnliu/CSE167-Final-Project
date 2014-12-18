#include "SpaceShip.h"
#include "ObjParser.h"
#include "main.h"

SpaceShip::SpaceShip()
{
   modelToWorld = Matrix4();
   modelToWorld.identity();
   positions = std::vector<Vector3>();
   normals = std::vector<Vector3>();
   ObjParser::parse("fsaucer01.obj", positions, normals);
   scale(.10);
   translate(0, 0, -399);
}

void SpaceShip::render()
{
   //glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(Vector3), &positions[0], GL_STATIC_DRAW);
   glPushMatrix();
   //glDisable(GL_DEPTH_TEST);
   Matrix4 m2w = Matrix4(modelToWorld);
   m2w.transpose();
   //m2w.identity();
   glLoadMatrixd(m2w.getPointer());
   glEnableClientState(GL_VERTEX_ARRAY);

   float specular[] = { 1.0, 1.0, 1.0, 1.0 };
   float ambient[] = { .5, .5, .5, 1.0 };
   float shininess[] = { 100.0 };
   float diffuse[] = { 0.5, 0.5, 0.5, 1.0 };

   //Generate material properties:
   //glEnable(GL_COLOR_MATERIAL);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

   glColor3f(.5, .5, .5);
   glBegin(GL_QUADS);
   for (unsigned int i = 0; i < positions.size(); i++)
   {
      Vector3 vertex = positions[i];
      Vector3 normal = normals[i];
      normal.normalize();
      glNormal3f(normal.v[0], normal.v[1], normal.v[2]);
      glVertex3f(vertex.v[0], vertex.v[1], vertex.v[2]);
   }
   glEnd();
   glEnable(GL_DEPTH_TEST);
   glPopMatrix();
   //glDisable(GL_COLOR_MATERIAL);
}

void SpaceShip::scale(double s)
{
   Matrix4 scaleMatrix = Matrix4::makeScale(s, s, s);
   modelToWorld = modelToWorld * scaleMatrix;
}

void SpaceShip::translate(float x, float y, float z)
{
   Matrix4 translate = Matrix4::makeTranslate(x, y, z);
   modelToWorld = translate * modelToWorld;
}