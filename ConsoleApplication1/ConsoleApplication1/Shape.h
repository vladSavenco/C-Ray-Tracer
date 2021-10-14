#pragma once
#include "Ray.h"

class shape
{
private:
	vec3 position;
	vec3 myColor;
	vec3 normal;

	vec3 diffuseColor;
	vec3 diffuseItensity;

public:


	shape();
	virtual bool Intersection(Ray* ray);

	//for future ray tracing
	virtual void ComputeColor(const float ambientIntensity, const vec3 IntPt, const vec3 lightPt, const vec3 rayDirection, float& ColValue);

	virtual vec3 getMyColor(void);
	virtual vec3 getPosition(void);
	virtual vec3 getNormal(void);
};