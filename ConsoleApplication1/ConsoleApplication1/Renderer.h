#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>

#include "Shape.h"
#include "Light.h"

class Renderer
{
public:
	std::vector<shape*> shapeVec;

	Light LigtArr[1][1][1];

	const int SCREEN_WIDTH = 720;
	const int SCREEN_HEIGHT = 480;

	Renderer();

	bool initSDL(SDL_Window*& window, SDL_Surface*& screenSurface);
	void closeSDL(SDL_Window*& window);

	Uint32 convertColour(vec3 colour);
	void PutPixel32_nolock(SDL_Surface*& surface, int x, int y, Uint32 colour);

	void createAreaLight(vec3 pos, int lightAmmount, vec3 intens);
};

