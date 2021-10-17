#include "sphere.h"

Sphere::Sphere(float r, vec3 cen, vec3 col,float shin) {
	radius = r;
	position = cen;
	mycolor = col;
	shyniness = shin;
}

Sphere::~Sphere()
{
}

float Sphere::getRadius(void)
{
	return radius;
}

vec3 Sphere::getPosition(void)
{
	return position;
}

vec3 Sphere::getMyColor(void)
{
	return mycolor;
}

bool Sphere::Intersection(Ray* ray)
{
	float t0, t1; // solutions for t if the ray intersects 

	// geometric solution  // vector dir has to be normalize, length is 1.0
	vec3 L = position - ray->origin;

	float tca = dot(L, ray->direction);

	if (tca < 0)
	{
		return false;
	}

	float d = dot(L, L) - tca * tca;

	if (d > (radius * radius))
	{
		return false;
	}

	float thc = sqrt(radius * radius - d);
	t0 = tca - thc;
	t1 = tca + thc;

	if (t0 > t1)
	{
		std::swap(t0, t1);
	}

	if (t0 < 0) 
	{
		t0 = t1; // if t0 is negative, let's use t1 instead 

		if (t0 < 0)
		{
			return false; // both t0 and t1 are negative 
		}
	}

	ray->hitDistance = t0;

	//getting the ray intersect point
	ray->intersectPoint = ray->origin + ray->direction * t0;

	return true;
}

void Sphere::ComputeColor(vec3 ambientLight, Light light, Ray* ray, vec3 surfaceCol, vec3& colVal)
{
	vec3 ttVec,rVec; //?
	float vecDot; //?
	float specValue, tt;

	//calculating ambiental lighting
	vec3 ambientCol = surfaceCol * ambientLight;

	//calculating diffuse lighting
	//
	vec3 ligtToPoint = normalize(light.origin - ray->intersectPoint);
	//
	vec3 normAtIntersec = normalize(ray->intersectPoint - position);
	//
	vec3 diffuseCol = surfaceCol * light.intensity * std::max(0.0f, dot(ligtToPoint, normAtIntersec));

	//calculate specular value
	vecDot = dot(normAtIntersec, ligtToPoint);
	ttVec = normAtIntersec * 2.0f * vecDot;

	rVec = ttVec - ligtToPoint;
	tt = std::max(0.0f, dot(rVec,-ray->direction)); // "-" ?????????
	specValue = pow(tt, 20) * shyniness;

	colVal = ambientCol + diffuseCol + specValue;
}
