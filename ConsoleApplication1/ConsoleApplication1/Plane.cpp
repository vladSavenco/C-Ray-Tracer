
#include "Plane.h"

Plane::Plane(vec3 norm, vec3 cen, vec3 col,float shin)
{
	normal = norm;
	position = cen;
	myColor = col;
	shyniness = shin;
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

		//getting the ray intersect point
		ray->intersectPoint = ray->origin + ray->direction * ray->hitDistance;

		if (ray->hitDistance >= 0)
		{

			return true;
		}
		else
			return false;
	}

	return false;

}

void Plane::ComputeColor(vec3 ambientLight, Light light, Ray* ray, vec3 surfaceCol, vec3& colVal)
{
	vec3 ttVec, rVec; //?
	float vecDot; //?
	float specValue, tt;

	//calculating ambiental lighting
	vec3 ambientCol = surfaceCol * ambientLight;

	//calculating diffuse lighting
	//
	vec3 ligtToPoint = normalize(light.origin - ray->intersectPoint);
	//
	vec3 normAtIntersec = normalize(normal);
	//
	vec3 diffuseCol = surfaceCol * light.intensity * std::max(0.0f, dot(ligtToPoint, normAtIntersec));

	//calculate specular value
	vecDot = dot(normAtIntersec, ligtToPoint);
	ttVec = normAtIntersec * 2.0f * vecDot;

	rVec = ttVec - ligtToPoint;
	tt = std::max(0.0f, dot(rVec, -ray->direction)); // "-" ?????????
	specValue =pow(tt, shyniness) *light.intensity.x;

	colVal = ambientCol + diffuseCol + specValue;
}
