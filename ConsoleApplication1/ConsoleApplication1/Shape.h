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
	virtual void ComputeColor(vec3 ambientLight, Light light, Ray* ray, vec3 surfaceCol, vec3& colVal);

	virtual vec3 getMyColor(void);
	virtual vec3 getPosition(void);
	virtual vec3 getNormal(void);
};