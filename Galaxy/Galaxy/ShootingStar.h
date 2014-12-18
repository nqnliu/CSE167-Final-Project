#ifndef _SHOOTINGSTAR_H
#define _SHOOTINGSTAR_H

#include "Object.h"
#include "Matrix4.h"

class ShootingStar
{
private:
	Object *stars;
	Matrix4 model2world;

public:
	ShootingStar();
	~ShootingStar();
	void scale(float);
	void translate(float, float, float);
	void render();
	void shoot();
	void t(float, float, float);
};

#endif