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

	int shyniness;

public:


	Sphere(float, vec3, vec3,int);
	~Sphere();

	float getRadius(void);
	vec3 getPosition(void) override;
	vec3 getMyColor(void) override;

	bool Intersection(Ray* ray);

	void ComputeColor(vec3 ambientLight, Light light, Ray* ray, vec3 surfaceCol, vec3& colVal) override;
};