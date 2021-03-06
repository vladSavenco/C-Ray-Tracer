#pragma once
#include "shape.h"

class triangle : public shape
{
private:
	vec3 vert0, vert1, vert2;
	vec3 color0, color1, color2;
	vec3 norm0, norm1, norm2;

	float v=0, u=0, w=0;

	vec3 position;

	float shyniness=1.0f;

	vec3 ambCol;

public:
	triangle(vec3 pos, vec3 v0, vec3 v1, vec3 v2, vec3 col0, vec3 col1, vec3 col2,vec3 n0,vec3 n1,vec3 n2,float shin);

	void getNormals();

	vec3 getPosition(void)override;

	bool Intersection(Ray* ray) override;

	vec3 getMyColor(void) override;

	void ComputeColor(vec3 ambientLight, Light light, Ray* ray, vec3 surfaceCol, vec3& colVal) override;

	virtual vec3 getAmb(void);
};