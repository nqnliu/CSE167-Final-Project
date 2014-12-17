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

   SolarSystem::SolarSystem();
   void render();
   void setUp();
   void toggleBumps();
   void toggleGlow();
   void update();
};