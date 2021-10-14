#include "Triangle.h"

triangle::triangle(vec3 pos, vec3 v0, vec3 v1, vec3 v2, vec3 color)
{

}

bool triangle::intersection(vec3 rayDirection, vec3 rayOrigin, float& t, vec3& IntPt, vec3& normVec)
{
	//Moller-Trumbore

	vec3 v0v1 = vertex1 - vertex0;
	vec3 v0v2 = vertex2 - vertex0;

	float u = (dot((rayOrigin - vertex0), (cross(rayDirection, v0v2)))) / dot(v0v1, cross(rayDirection, v0v2));
	float v = (dot(rayDirection, cross(rayOrigin - vertex0, v0v1))) / dot(v0v1, cross(rayDirection, v0v2));

	float w = 1 - u - v;

	if (u < 0 || u > 1)
		return false;
	else if (v < 0 || (u + v) > 1)
		return false;
	else
	{
		//compute intersection point, t and normal vector
		//add your codes here
		return true;
	}
}

void triangle::ComputeColor(const float ambientIntensity, const vec3 IntPt, const vec3 lightPt, const vec3 rayDirection, const vec3 tNormvec, float& ColValue)
{
}

triangle::~triangle()
{
}
