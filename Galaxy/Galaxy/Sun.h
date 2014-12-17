#ifndef _SUN_H
#define _SUN_H

#include "shader.h"
#include "Sun.h"
#include "Planet.h"

class Sun : public Planet
{
public:
   Sun::Sun();
   void render();
   void renderGlow();

private:
	void glow(float);
};
#endif