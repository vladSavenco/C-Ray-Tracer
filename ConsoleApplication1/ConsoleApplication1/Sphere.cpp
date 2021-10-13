#include "sphere.h"

Sphere::Sphere(float r, vec3 cen, vec3 col) {
	radius = r;
	center = cen;
	mycolor = col;
}

Sphere::~Sphere()
{
}

float Sphere::getRadius(void)
{
	return radius;
}

vec3 Sphere::getCenter(void)
{
	return center;
}

vec3 Sphere::getMyColor(void)
{
	return mycolor;
}

bool Sphere::intersection(vec3 center, vec3 orig, vec3 dir, float radius, float& t)
{
	float t0, t1; // solutions for t if the ray intersects 

	// geometric solution  // vector dir has to be normalize, length is 1.0
	vec3 L = center - orig;
	float tca = dot(L, dir);
	if (tca < 0) return false;
	float d = dot(L, L) - tca * tca;
	if (d > (radius * radius)) return false;

	float thc = sqrt(radius * radius - d);
	t0 = tca - thc;
	t1 = tca + thc;

	if (t0 > t1) std::swap(t0, t1);

	if (t0 < 0) {
		t0 = t1; // if t0 is negative, let's use t1 instead 
		if (t0 < 0) return false; // both t0 and t1 are negative 
	}

	t = t0;
	return true;
}

void Sphere::ComputeColor(const vec3 sourcePt, const vec3 IntPt, const vec3 CenPt, const vec3 dir, float& ColValue)
{
	vec3 lightToPt, surNorm, rVec, ttvec;
	float Ca, Cd, Cs, tt; //Ca for ambient colour; //Cd for diffuse colour; //Cs for specular highlights
	float vecdot;
	lightToPt = normalize(sourcePt - IntPt);
	surNorm = normalize(IntPt - CenPt);
	Cd = std::max(0.0, (double)dot(lightToPt, surNorm));
	Ca = 0.2;

	//compute specular value
	vecdot = dot(surNorm, lightToPt);
	ttvec.x = surNorm.x * 2.0 * vecdot;
	ttvec.y = surNorm.y * 2.0 * vecdot;
	ttvec.z = surNorm.z * 2.0 * vecdot;

	rVec = ttvec - lightToPt;
	tt = std::max(0.0, (double)dot(rVec, -dir));
	Cs = pow(tt, 20) * 0.7;

	//ColValue = Cs;
	ColValue = Ca + Cd + Cs;
}
