
#include "Shape.h"
class Plane :
	public shape
{
private:
	vec3 normal;
	vec3 position;
	vec3 myColor;

	float shyniness;

public:


	Plane(vec3 norm, vec3 cen, vec3 col,float shin);

	vec3 getMyColor(void) override;
	vec3 getPosition(void) override;
	vec3 getNormal(void) override;

	bool Intersection(Ray* ray);
	void ComputeColor(vec3 ambientLight, Light light, Ray* ray, vec3 surfaceCol, vec3& colVal) override;
};
