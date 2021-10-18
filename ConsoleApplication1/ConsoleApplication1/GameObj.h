#pragma once

#include "ObjLoader.h"
#include "Triangle.h"

class GameObj
{
public:
	std::string path;
	vec3 position;
	vec3 color;
	float shynines;

	vector<VertexWithAll> vertices;

	vector<triangle> triangleVec;

	GameObj(std::string pat,vec3 pos,vec3 col,float shin);
};

