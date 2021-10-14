
#include "Plane.h"

Plane::Plane(vec3 norm, vec3 cen, vec3 col)
{
	normal = norm;
	center = cen;
	myColor = col;
}

vec3 Plane::getMyColor(void)
{
	return myColor;
}

vec3 Plane::getCenter(void)
{
	return center;
}

vec3 Plane::getNormal(void)
{
	return normal;
}

bool Plane::Intersection(const vec3& normal, const vec3& center, const vec3& org, const vec3& dir, float& t)
{

	float denom = glm::dot(normal, dir);
	if (denom > 1e-6) 
	{
		vec3 p0l0 = center - org;

		t = glm::dot(p0l0, normal) / denom;
		if (t >= 0)
		{

			return true;
		}
		else
			return false;
	}

	return false;

}
