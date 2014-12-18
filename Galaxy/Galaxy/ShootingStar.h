#ifndef _SHOOTINGSTAR_H
#define _SHOOTINGSTAR_H

#include "Object.h"
#include "Matrix4.h"

class ShootingStar
{
private:
	Object *stars;
	Matrix4 model2world;
	bool render_flag;

public:
	ShootingStar();
	~ShootingStar();
	void scale(float);
	void translate(float, float, float);
	void render();
	void shoot();
	void t(float, float, float);
	void renderflag(bool);
};

#endif