#include "SpaceShip.h"
#include "ObjParser.h"
#include "main.h"

SpaceShip::SpaceShip()
{
   //shader =;
   modelToWorld = Matrix4();
   modelToWorld.identity();
   positions = std::vector<Vector3>();
   normals = std::vector<Vector3>();
   ObjParser::parse("fsaucer01.obj", positions, normals);
   scale(.10);
   translate(0, 0, -399);
   /*
   auto timeUpdater = make_shared<updaters::BasicTimeUpdater>();
   m_system->addUpdater(timeUpdater);

   auto colorUpdater = make_shared<updaters::BasicColorUpdater>();
   m_system->addUpdater(colorUpdater);

   auto m_eulerUpdater = make_shared<updaters::EulerUpdater>();
   m_eulerUpdater->m_globalAcceleration = glm::vec4{ 0.0, -10.0, 0.0, 0.0 };
   m_system->addUpdater(m_eulerUpdater);

   auto m_floorUpdater = std::make_shared<updaters::AttractorUpdater>();
   //m_floorUpdater->add(glm::vec4(0.0, 5.0, 0.0, .2));
   m_system->addUpdater(m_floorUpdater);

   auto particleEmitter = std::make_shared<ParticleEmitter>();
   {
      particleEmitter->m_emitRate = (float)500 * 0.45f;

      // pos:
      auto posGenerator = std::make_shared<generators::BoxPosGen>();
      posGenerator->m_pos = glm::vec4{ 0.0, 0.0, 5, 0.0 };
      posGenerator->m_maxStartPosOffset = glm::vec4{ 0.2, 0.0, 0, 0.0 };
      //posGenerator->m_center = glm::vec4{ 0.0, 0.0, 1, 0.0 };
      //posGenerator->m_radX = 0.15f;
      //posGenerator->m_radY = 0.15f;
      particleEmitter->addGenerator(posGenerator);

      auto colGenerator = std::make_shared<generators::BasicColorGen>();
      colGenerator->m_minStartCol = glm::vec4{ 0.5, 0.5, 0.5, 1.0 };
      colGenerator->m_maxStartCol = glm::vec4{ 1.0, 1.0, 1.0, 1.0 };
      colGenerator->m_minEndCol = glm::vec4{ 1.0, 1.0, 1.0, 0.0 };
      colGenerator->m_maxEndCol = glm::vec4{ 0.5, 0.5, 0.5, 0.0 };
      particleEmitter->addGenerator(colGenerator);

      auto velGenerator = std::make_shared<generators::BasicVelGen>();
      velGenerator->m_minStartVel = glm::vec4{ 0.0f, 0.0f, 0.15f, 0.0f };
      velGenerator->m_maxStartVel = glm::vec4{ 0.0f, 0.0f, 0.45f, 0.0f };
      particleEmitter->addGenerator(velGenerator);

      auto timeGenerator = std::make_shared<generators::BasicTimeGen>();
      timeGenerator->m_minTime = 1.0;
      timeGenerator->m_maxTime = 3.5;
      particleEmitter->addGenerator(timeGenerator);
   }
   m_system->addEmitter(particleEmitter);*/

}

void SpaceShip::render()
{
   if (!partShader)
      partShader = new Shader("particle.vert", "particle.frag", true);
   //glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(Vector3), &positions[0], GL_STATIC_DRAW);
   glPushMatrix();
   //glDisable(GL_DEPTH_TEST);
   Matrix4 m2w = Matrix4(modelToWorld);
   m2w.transpose();
   //m2w.identity();
   glLoadMatrixd(m2w.getPointer());

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
      //normal.normalize();
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