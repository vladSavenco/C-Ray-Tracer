#include "Shape.h"

shape::shape()
{
}

bool shape::Intersection(Ray* ray)
{
	return false;
}

void shape::ComputeColor(vec3 ambientLight, Light light, Ray* ray, vec3 surfaceCol, vec3& colVal)
{
	//calculating ambiental lighting
	//vec3 ambientCol = surfaceCol * ambientLight;

	//colVal = ambientCol;
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
