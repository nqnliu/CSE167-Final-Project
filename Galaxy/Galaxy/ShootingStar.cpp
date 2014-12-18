#include "ShootingStar.h"

#include "Vector3.h"
#include "Vector4.h"
#include "main.h"

ShootingStar::ShootingStar()
{
	stars = new Object("shootingstar.obj");
	model2world = model2world.makeTranslate(-6000, 0, 0);
}


ShootingStar::~ShootingStar()
{
	delete stars;
}


void ShootingStar::scale(float s)
{
	stars->scale(s);
}

void ShootingStar::translate(float tx, float ty, float tz)
{
	stars->translate(tx,ty,tz);
}

void ShootingStar::shoot()
{
	model2world.identity();
	model2world = model2world.makeTranslate(1000, 1000, 90);
}

void ShootingStar::t(float tx, float ty, float tz)
{
	model2world = model2world.makeTranslate(tx, ty, tz) * model2world ;
}

void ShootingStar::render()
{
	model2world = model2world.makeTranslate(-20, -20, 0) * model2world ;
	stars->render(model2world);
}