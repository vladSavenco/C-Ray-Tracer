#pragma once
#include "glm/glm/glm.hpp"

#include <iostream>
#include <algorithm>

using namespace std;
using namespace glm;

struct Light
{
public:
	vec3 origin;
	vec3 intensity;

	Light(vec3 org,vec3 intens)
	{
		origin = org;
		intensity = intens;
	}
};