#include "Shape.h"

shape::shape()
{
}

bool shape::Intersection(Ray* ray)
{
	return false;
}

void shape::ComputeColor(const float ambientIntensity, const vec3 IntPt, const vec3 lightPt, const vec3 rayDirection, float& ColValue)
{
}

vec3 shape::getMyColor(void)
{
	return myColor;
}

vec3 shape::getPosition(void)
{
	return position;
}

vec3 shape::getNormal(void)
{
	return normal;
}
