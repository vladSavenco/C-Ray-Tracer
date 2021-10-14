#pragma once
#include "glm/glm/glm.hpp"

#include <iostream>
#include <algorithm>

using namespace glm;

class shape
{
private:
	vec3 center;
	vec3 diffuseColor;
	vec3 diffuseItensity;

public:
	shape();
	virtual bool Intersection(vec3 rayDirection, vec3 rayOrigin, float& t, vec3& IntPt, vec3& normVec);

	//for future ray tracing
	virtual void ComputeColor(const float ambientIntensity, const vec3 IntPt, const vec3 lightPt, const vec3 rayDirection, float& ColValue);
	~shape();
	vec3 position;
	vec3 mcolor;
};