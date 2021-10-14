
#include "Plane.h"

Plane::Plane(vec3 norm, vec3 cen, vec3 col)
{
	normal = norm;
	position = cen;
	myColor = col;
}

vec3 Plane::getMyColor(void)
{
	return myColor;
}

vec3 Plane::getPosition(void)
{
	return position;
}

vec3 Plane::getNormal(void)
{
	return normal;
}

bool Plane::Intersection(Ray* ray)
{
	float denom = glm::dot(normal, ray->direction);
	if (denom > 1e-6) 
	{
		vec3 p0l0 = position - ray->origin;

		ray->hitDistance = glm::dot(p0l0, normal) / denom;
		if (ray->hitDistance >= 0)
		{

			return true;
		}
		else
			return false;
	}

	return false;

}
