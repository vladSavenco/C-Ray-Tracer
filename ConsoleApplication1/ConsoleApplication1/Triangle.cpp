#include "Triangle.h"

triangle::triangle(vec3 pos, vec3 v0, vec3 v1, vec3 v2, vec3 col0, vec3 col1, vec3 col2)
{
	position = pos;

	vert0 = v0+pos;
	vert1 = v1+pos;
	vert2 = v2+pos;

	color0 = col0;
	color1 = col1;
	color2 = col2;
}

bool triangle::Intersection(Ray* ray)
{
		// compute plane's normal
		vec3 v0v1 = vert1 - vert0;
		vec3 v0v2 = vert2 - vert0;

		// no need to normalize
		vec3 normal = cross(v0v1, v0v2);

		float denom = dot(normal, normal);

		//finding P

		// check if ray and plane are parallel ?
		float NdotRayDirection = dot(normal, ray->direction);
		if (abs(NdotRayDirection) < 0.000001)
		{
			return false;
			cout << "paralel" << endl;
		}
			
		// they are parallel so they don't intersect ! 

		//compute d parameter using equation 2
		float d = dot(normal, vert0);

		//compute ray hit disstance
		ray->hitDistance = (dot(normal, ray->origin) + d);

		//check if triangle is behind the ray
		if (ray->hitDistance < 0)
		{
			//cout << "triangle behind ray" << endl;
			return false;
		}
		//compute the intersection point using equation 1
		vec3 hitPoint = ray->origin + ray->hitDistance * ray->direction;

		//inside-out test
		vec3 c;

		//edge0
		vec3 edge0 = vert1 - vert0;
		vec3 vp0 = hitPoint - vert0;
		c = cross(edge0, vp0);
		if (dot(normal, c) < 0)
		{
			//cout << "edge 1 go fricky" << endl;
			return false;//p is on the right side
		}

		//edge1
		vec3 edge1 = vert2 - vert1;
		vec3 vp1 = hitPoint - vert1;
		c = cross(edge1, vp1);
		if ((u = dot(normal, c)) < 0)
		{
			//cout << "edge 2 go fricky" << endl;
			return false;//p is on the right side
		}

		//edge2
		vec3 edge2 = vert0 - vert2;
		vec3 vp2 = hitPoint - vert2;
		c = cross(edge2, vp2);
		if ((v = dot(normal, c)) < 0)
		{
			//cout << "edge 3 go fricky" << endl;
			return false;//p is on the right side
		}

		u /= denom;
		v /= denom;

		w = 1 - v - u;
		return true;//this ray hits the triangle

}

vec3 triangle::getMyColor(void)
{
	return u * color0 + v * color1 + w * color2;
}

void triangle::ComputeColor(const float ambientIntensity, const vec3 IntPt, const vec3 lightPt, const vec3 rayDirection, const vec3 tNormvec, float& ColValue)
{
}

triangle::~triangle()
{
}
