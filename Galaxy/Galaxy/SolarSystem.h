#include "MatrixTransform.h"
#include "Planet.h"
#include <vector>

class SolarSystem
{
public:
   MatrixTransform world;
   vector<Planet*> planets;
   vector<MatrixTransform*> translates;
   vector<MatrixTransform*> orbits;
   Matrix4 model2world;
   bool moving = false;

   SolarSystem::SolarSystem();
   void render();
   void setUp();
   void toggleBumps();
   void toggleGlow();
   void update();
   void scale(float);
   void rotateY(float);
   void translate(float, float, float);

private:
	void ownRotation();
};