#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>

#include "Shape.h"

class Renderer
{
public:
	std::vector<shape*> shapeVec;
	std::vector<Light> lightVec;

	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	bool initSDL(SDL_Window*& window, SDL_Surface*& screenSurface);
	void closeSDL(SDL_Window*& window);

	Uint32 convertColour(vec3 colour);
	void PutPixel32_nolock(SDL_Surface*& surface, int x, int y, Uint32 colour);

	void createLight(vec3 org,vec3 intens);
};

