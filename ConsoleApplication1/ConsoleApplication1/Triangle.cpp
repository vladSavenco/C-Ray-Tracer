#include "Triangle.h"

triangle::triangle(vec3 pos, vec3 v0, vec3 v1, vec3 v2, vec3 col0, vec3 col1, vec3 col2, vec3 n0, vec3 n1, vec3 n2, float shin)
{
	position = pos;

	vert0 = v0+pos;
	vert1 = v1+pos;
	vert2 = v2+pos;

	color0 = col0;
	color1 = col1;
	color2 = col2;

	shyniness = shin;

	norm0 = n0;
	norm1 = n1;
	norm2 = n2;

	//getNormals();
}

void triangle::getNormals()
{
	vec3 ab = vert1 - vert0;
	vec3 ac = vert2 - vert0;

	norm0 = ab * ac;

	vec3 ba = vert0 - vert1;
	vec3 bc = vert2 - vert1;

	norm1 = ba * bc;

	vec3 ca = vert0 - vert2;
	vec3 cb = vert1 - vert2;
	norm2 = ca * cb;
}

vec3 triangle::getPosition(void)
{
	return position;
}

bool triangle::Intersection(Ray* ray)
{
		// compute plane's normal
		vec3 vert0vert1 = vert1 - vert0;
		vec3 vert0vert2 = vert2 - vert0;

		// no need to normalize
		vec3 triNormal = cross(vert0vert1, vert0vert2);
		float denominator = dot(triNormal, triNormal);

		//finding P
		// check if ray and plane are parallel ?
		float TriNormDotRayDirection = dot(triNormal, ray->direction);

		if (abs(TriNormDotRayDirection) < 0.00001)
		{
			return false;
		}
			
		// they are parallel so they don't intersect ! 

		//compute d parameter using equation 2
		float d = dot(triNormal, vert0);

		//compute ray hit disstance
		ray->hitDistance = (dot(triNormal, ray->origin) + d)/ TriNormDotRayDirection;

		//check if triangle is behind the ray
		if (ray->hitDistance < 0)
		{
			//cout << "triangle behind ray" << endl;
			return false;
		}

		//compute the intersection point using equation 1
		vec3 hitPoint = ray->origin + ray->hitDistance * ray->direction;
		ray->intersectPoint = hitPoint;

		//inside-out test
		vec3 c;

		//edge0
		vec3 edge0 = vert1 - vert0;
		vec3 vp0 = hitPoint - vert0;
		c = cross(edge0, vp0);
		if (dot(triNormal, c) < 0)
		{
			return false;//p is on the right side
		}

		//edge1
		vec3 edge1 = vert2 - vert1;
		vec3 vp1 = hitPoint - vert1;
		c = cross(edge1, vp1);
		if ((u = dot(triNormal, c)) < 0)
		{
			return false;//p is on the right side
		}

		//edge2
		vec3 edge2 = vert0 - vert2;
		vec3 vp2 = hitPoint - vert2;
		c = cross(edge2, vp2);
		if ((v = dot(triNormal, c)) < 0)
		{
			return false;//p is on the right side
		}

		u =u/ denominator;
		v =v/ denominator;

		w = 1 - v - u;
		return true;//this ray hits the triangle

}

vec3 triangle::getMyColor(void)
{
	return u * color0 + v * color1 + w * color2;
}

void triangle::ComputeColor(vec3 ambientLight, Light light, Ray* ray, vec3 surfaceCol, vec3& colVal)
{
	vec3 ttVec, rVec; //who?
	float vecDot; //who?
	float specValue, tt; //who?

	surfaceCol = u * color0 + v * color1 + w * color2;

	//calculating ambiental lighting
	vec3 ambientCol = surfaceCol * ambientLight;

	ambCol = ambientCol;

	//calculating diffuse lighting
	//
	vec3 ligtToPoint = normalize(light.origin - ray->intersectPoint);
	//

	vec3 normAtIntersec=normalize(u*norm0+v*norm1+w*norm2);
	//
	vec3 diffuseCol = surfaceCol * light.intensity * std::max(0.0f, dot(ligtToPoint, normAtIntersec));

	//calculate specular value
	vecDot = dot(normAtIntersec, ligtToPoint);
	ttVec = normAtIntersec * 2.0f * vecDot;

	rVec = ttVec - ligtToPoint;
	tt = std::max(0.0f, dot(rVec, -ray->direction)); // "-" ?????????
	specValue = pow(tt, 20.0f) * shyniness;

	colVal = ambientCol + diffuseCol + specValue;
}

vec3 triangle::getAmb(void)
{
	return ambCol;
}
