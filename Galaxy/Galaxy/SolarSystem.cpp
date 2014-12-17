#include "SolarSystem.h"
#include "Planet.h"
#include "Sun.h"
#include "Matrix4.h"

SolarSystem::SolarSystem()
{
   planets = vector<Planet*>();
   translates = vector<MatrixTransform*>();
   orbits = vector<MatrixTransform*>();

   world = MatrixTransform();

   // Sun
   //Sun sun = Sun();
   //world.addChild(&sun);

   Matrix4 rotate = Matrix4();
   rotate.identity();
   for (int i = 0; i < 9; i++)
   {
      orbits.push_back(new MatrixTransform(rotate));
   }

   Matrix4 translate = Matrix4::makeTranslate(100, 0, 0);
   translates.push_back(new MatrixTransform(translate));
   translate = Matrix4::makeTranslate(200, 0, 0);
   translates.push_back(new MatrixTransform(translate));
   translate = Matrix4::makeTranslate(300, 0, 0);
   translates.push_back(new MatrixTransform(translate));
   translate = Matrix4::makeTranslate(400, 0, 0);
   translates.push_back(new MatrixTransform(translate));
   translate = Matrix4::makeTranslate(500, 0, 0);
   translates.push_back(new MatrixTransform(translate));
   translate = Matrix4::makeTranslate(600, 0, 0);
   translates.push_back(new MatrixTransform(translate));
   translate = Matrix4::makeTranslate(700, 0, 0);
   translates.push_back(new MatrixTransform(translate));
   translate = Matrix4::makeTranslate(800, 0, 0);
   translates.push_back(new MatrixTransform(translate));
   translate = Matrix4::makeTranslate(900, 0, 0);
   translates.push_back(new MatrixTransform(translate));

   planets.push_back(new Planet(.50, "Textures/mercurymap.jpg", "Textures/mercurybump_NRM.jpg", 1.59));
   planets.push_back(new Planet(1.0, "Textures/venusmap.jpg", "Textures/venusbump_NRM.jpg", 1.18));
   planets.push_back(new Planet(1.0, "Textures/earthmap1k.jpg", "Textures/earthbump1k_NRM.jpg", 1));
   planets[2]->setGlow(.21, .1, .03);
   planets.push_back(new Planet(.75, "Textures/mars_1k_color.jpg", "Textures/marsbump1k_NRM.jpg", .0343));
   planets[3]->setGlow(.025, .05, .25);
   planets.push_back(new Planet(11.21, "Textures/jupitermap.jpg", "Textures/smooth.jpg", .808));
   planets.push_back(new Planet(9.45, "Textures/saturnmap.jpg", "Textures/smooth.jpg", .439));
   planets.push_back(new Planet(4.0, "Textures/uranusmap.jpg", "Textures/smooth.jpg", .228));
   planets.push_back(new Planet(3.8, "Textures/neptunemap.jpg", "Textures/smooth.jpg", .182));
   planets.push_back(new Planet(.20, "Textures/plutomap2k.jpg", "Textures/plutobump2k_NRM.jpg", .157));

   for (int i = 0; i < 9; i++)
   {
      orbits[i]->addChild(translates[i]);
      translates[i]->addChild(planets[i]);
      world.addChild(orbits[i]);
   }  

   Sun * sun = new Sun();
   planets.push_back(sun);
   world.addChild(sun);
}

void SolarSystem::setUp()
{
   for (int i = 0; i < 10; i++)
      planets[i]->setUpShader();
}

void SolarSystem::render()
{
   glPushMatrix();
   update();
   GLfloat ptr[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, ptr);
   Matrix4 model2world = Matrix4(ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7], 
      ptr[8], ptr[9], ptr[10], ptr[11], ptr[12], ptr[13], ptr[14], ptr[15]);
   model2world.transpose();
   //model2world.identity();
   world.draw(model2world);
   glPopMatrix();
}

void SolarSystem::toggleBumps()
{
   for (int i = 0; i < 10; i++)
      planets[i]->bump = !planets[i]->bump;
}

void SolarSystem::toggleGlow()
{
   for (int i = 0; i < 10; i++)
      planets[i]->glowFlag = !planets[i]->glowFlag;
}

void SolarSystem::update()
{
   for (int i = 0; i < 9; i++) {
      Matrix4 rotate = Matrix4::makeRotateY(planets[i]->orbit_velocity * .1);
      orbits[i]->M = rotate * orbits[i]->M;
   }
}