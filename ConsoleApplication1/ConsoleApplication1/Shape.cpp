#include "Shape.h"

shape::shape()
{
}

bool shape::intersection(vec3 rayDirection, vec3 rayOrigin, float& t, vec3& IntPt, vec3& normVec)
{
	return false;
}

void shape::ComputeColor(const float ambientIntensity, const vec3 IntPt, const vec3 lightPt, const vec3 rayDirection, float& ColValue)
{
}

shape::~shape()
{
}
