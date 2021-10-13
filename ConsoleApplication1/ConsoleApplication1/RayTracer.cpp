#include <iostream>
#include <fstream>      // std::ofstream
#include <math.h>
#include <vector>

#include <SDL.h>
#include <glm/glm.hpp>

#include "Renderer.h"
#include "Sphere.h"

#include "Triangle.h"

using namespace std;
using namespace glm;

#define PI 3.14159265
SDL_Event event;

Renderer renderer;

Uint32 convertColour(vec3 colour)
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
};

void PutPixel32_nolock(SDL_Surface*& surface, int x, int y, Uint32 colour)
{
	Uint8* pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = colour;
};

int main(int argc, char* args[])
{
	const int WIDTH = 640;
	const int HEIGHT = 480;
	float PixelNdx, PixelNdy, PixelRdx, PixelRdy, Iar, tanvalue, PCameraX, PCameraY;

	///SECTION - SDL Setup
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	if (!renderer.initSDL(window, screenSurface)) return -1;

	//create two dimensional pxiel array for the image
	vec3** image = new vec3 * [WIDTH];
	for (int i = 0; i < WIDTH; i++) image[i] = new vec3[HEIGHT];

	Iar = WIDTH / (float)HEIGHT;
	tanvalue = tanf(40.0 * PI / 180.0);  //40 degree for big field of view //15 for zoom in

	bool Intersection;
	float t, min_t, ColorVal;
	int i, whichone;
	vec3 ttvec, dir, org, mat_color, final_Color, IntPt;
	vector<float> t_arr;
	vector<vec3> color_arr;
	 
	//add spheres
	Sphere redSphere(4, vec3(0, 0, -20), vec3(1.00, 0.32, 0.36));
	color_arr.push_back(redSphere.getMyColor());

	Sphere yellowSphere(2, vec3(5, -1, -15), vec3(0.90, 0.76, 0.46));
	color_arr.push_back(yellowSphere.getMyColor());

	Sphere blueSphere(3, vec3(5, 0, -25), vec3(0.65, 0.77, 0.97));
	color_arr.push_back(blueSphere.getMyColor());

	Sphere graySphere(3, vec3(-5.5, 0, -15), vec3(0.90, 0.90, 0.90));
	color_arr.push_back(graySphere.getMyColor());
	
	///light setting
	vec3 sourcePt;
	sourcePt.x = 0.0; sourcePt.y = 20.0; sourcePt.z = 0.0;

	//draw the scene
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			t_arr.clear();
			color_arr.clear();

			PixelNdx = (x + 0.5) / (float)WIDTH;
			PixelNdy = (y + 0.5) / (float)HEIGHT;
			PixelRdx = 2 * PixelNdx - 1.0;
			PixelRdy = 1.0 - 2 * PixelNdy;
			PixelRdx = PixelRdx * Iar;

			PCameraX = PixelRdx * tanvalue;
			PCameraY = PixelRdy * tanvalue;

			ttvec.x = PCameraX;
			ttvec.y = PCameraY;
			ttvec.z = -1.0;
			//dir need to be normalized
			dir = normalize(ttvec);

			org.x = 0.0; org.y = 0.0; org.z = 0.0;

			//Checking for intersection of the spheres
			//red sphere
			Intersection = redSphere.intersection(redSphere.getCenter(), org, dir, redSphere.getRadius(), t);
			if (Intersection)
			{
				t_arr.push_back(t);
				color_arr.push_back(redSphere.getMyColor());
			}

			//yellow spher
			Intersection = yellowSphere.intersection(yellowSphere.getCenter(), org, dir, yellowSphere.getRadius(), t);
			if (Intersection)
			{
				t_arr.push_back(t);
				color_arr.push_back(yellowSphere.getMyColor());
			}

			//blue sphere
			Intersection = blueSphere.intersection(blueSphere.getCenter(), org, dir, blueSphere.getRadius(), t);
			if (Intersection)
			{
				t_arr.push_back(t);
				color_arr.push_back(blueSphere.getMyColor());
			}

			//gray sphere
			Intersection = graySphere.intersection(graySphere.getCenter(), org, dir, graySphere.getRadius(), t);
			if (Intersection)
			{
				t_arr.push_back(t);
				color_arr.push_back(graySphere.getMyColor());
			}

			if (t_arr.size() == 0)
			{
				image[x][y].x = 1.0;
				image[x][y].y = 0.0;
				image[x][y].z = 1.0;

				PutPixel32_nolock(screenSurface, x, y, convertColour(image[x][y]));
			}
			else
			{
				min_t = 1000.0;
				whichone = 0;
				for (i = 0; i < t_arr.size(); i++)
				{
					if (t_arr[i] < min_t) { whichone = i; min_t = t_arr[i]; }
				}
				image[x][y].x = color_arr[whichone].x;
				image[x][y].y = color_arr[whichone].y;
				image[x][y].z = color_arr[whichone].z;

				PutPixel32_nolock(screenSurface, x, y, convertColour(image[x][y]));
			}
		}
	}

	SDL_UpdateWindowSurface(window);
	bool quit = false;
	while (!quit)
	{
		//Keyboard Input
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}


	renderer.closeSDL(window);
	return 0;
}