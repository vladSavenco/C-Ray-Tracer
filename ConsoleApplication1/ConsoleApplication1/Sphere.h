#pragma once
#include "shape.h"
#include <glm/glm.hpp>

using namespace glm;

class Sphere : public shape
{
private:
	float radius;
	vec3  center;
	vec3 mycolor;
public:

	Sphere(float, vec3, vec3);
	~Sphere();

	float getRadius(void);
	vec3 getCenter(void);
	vec3 getMyColor(void);

	bool Intersection(vec3 center, vec3 orig, vec3 dir, float radius, float& t);
	void ComputeColor(const vec3 sourcePt, const vec3 IntPt, const vec3 CenPt, const vec3 dir, float& ColValue);
};