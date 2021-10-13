#pragma once
#include <iostream>
#include <SDL.h>

class Renderer
{
public:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	bool initSDL(SDL_Window*& window, SDL_Surface*& screenSurface);

	void closeSDL(SDL_Window*& window);
};

