#pragma once

#include "glm/glm/glm.hpp"

#include <iostream>
#include <algorithm>

using namespace std;
using namespace glm;

struct Ray
{
public:
	vec3 origin;
	vec3 direction;

	float hitDistance = 0;

	Ray(vec3 org,vec3 dir)
	{
		origin = org;
		direction = dir;
	}
};