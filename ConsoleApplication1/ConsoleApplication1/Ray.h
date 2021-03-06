#pragma once

#include "glm/glm/glm.hpp"

#include <iostream>
#include <algorithm>

#include "Light.h"

using namespace std;
using namespace glm;

struct Ray
{
public:
	vec3 origin;
	vec3 direction;

	vec3 intersectPoint;

	float hitDistance = 0;

	Ray(vec3 org,vec3 dir)
	{
		origin = org;
		direction = dir;
	}
};