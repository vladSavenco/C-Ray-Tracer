#pragma once
#include "shape.h"
#include <glm/glm.hpp>

using namespace glm;

class Sphere : public shape
{
private:
	float radius;
	vec3  position;
	vec3 mycolor;

public:


	Sphere(float, vec3, vec3);
	~Sphere();

	float getRadius(void);
	vec3 getPosition(void) override;
	vec3 getMyColor(void) override;

	bool Intersection(Ray* ray);
	void ComputeColor(const vec3 sourcePt, const vec3 IntPt, const vec3 CenPt, const vec3 dir, float& ColValue);
};