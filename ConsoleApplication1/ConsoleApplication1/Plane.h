
#include "Shape.h"
class Plane :
	public shape
{
private:
	vec3 normal;
	vec3 center;
	vec3 myColor;

public:
	Plane(vec3 norm, vec3 cen, vec3 col);

	vec3 getMyColor(void);
	vec3 getCenter(void);
	vec3 getNormal(void);

	bool Intersection(const vec3& n, const vec3& origin, const vec3& org, const vec3& dir, float& t);
};
