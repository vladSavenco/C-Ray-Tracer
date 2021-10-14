#include "Renderer.h"

bool Renderer::initSDL(SDL_Window*& window, SDL_Surface*& screenSurface)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		//create the window
		window = SDL_CreateWindow("SDL Version", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "SDL Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			return true;
		}
	}
}

void Renderer::closeSDL(SDL_Window*& window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Uint32 Renderer::convertColour(vec3 colour)
{
	int tt;
	Uint8 r, g, b;

	tt = (int)(colour.r * 255);
	if (tt <= 255) r = tt; else r = 255;
	tt = (int)(colour.g * 255);
	if (tt <= 255) g = tt; else g = 255;
	tt = (int)(colour.b * 255);
	if (tt <= 255) b = tt; else b = 255;

	Uint32 rgb;

	//check which order SDL is storing bytes
	rgb = (r << 16) + (g << 8) + b;

	return rgb;
}

void Renderer::PutPixel32_nolock(SDL_Surface*& surface, int x, int y, Uint32 colour)
{
	Uint8* pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = colour;
}
