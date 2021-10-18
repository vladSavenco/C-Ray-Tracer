#include "GameObj.h"

GameObj::GameObj(std::string pat, vec3 pos, vec3 col, float shin)
{
	position = pos;
	path = pat;
	color = col;
	shynines = shin;

	vertices = loadOBJ(path);

	for (int i = 0; i < vertices.size(); i += 3)
	{
		triangle newTri(position, vertices[i].position, vertices[i + 1].position, vertices[i + 2].position, color, color, color, vertices[i].normal, vertices[i + 1].normal, vertices[i + 2].normal, shynines);
		triangleVec.push_back(newTri);
	}
}
