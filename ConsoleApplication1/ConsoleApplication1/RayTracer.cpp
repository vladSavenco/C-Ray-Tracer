#include <iostream>
#include <fstream>      // std::ofstream
#include <math.h>
#include <vector>

#include <SDL.h>
#include <glm/glm.hpp>

#include "Renderer.h"

#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

using namespace std;
using namespace glm;

#define PI 3.14159265
SDL_Event event;


int main(int argc, char* args[])
{
	Renderer renderer;

	const int WIDTH = renderer.SCREEN_WIDTH;
	const int HEIGHT = renderer.SCREEN_HEIGHT;
	float PixelNdx, PixelNdy, PixelRdx, PixelRdy, Iar, tanvalue, PCameraX, PCameraY;

	///SECTION - SDL Setup
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	if (!renderer.initSDL(window, screenSurface))
	{
		return -1;
	}

	//create two dimensional pxiel array for the image
	vec3** image = new vec3 * [WIDTH];
	for (int i = 0; i < WIDTH; i++) image[i] = new vec3[HEIGHT];

	Iar = WIDTH / (float)HEIGHT;
	tanvalue = tanf(40.0 * PI / 180.0);  //40 degree for big field of view //15 for zoom in

	bool Intersection;
	float t, min_t, ColorVal;
	int i, whichone;
	vec3 ttvec, dir, org, mat_color, final_Color, IntPt;

	//array of the distance of the ray hits
	vector<float> t_arr;
	vector<vec3> color_arr;
	 
	//add spheres
	Sphere redSphere(4, vec3(0, 0, -20), vec3(1.00, 0.32, 0.36),0);
	renderer.shapeVec.push_back(&redSphere);

	Sphere yellowSphere(2, vec3(5, -1, -15), vec3(0.90, 0.76, 0.46),1);
	renderer.shapeVec.push_back(&yellowSphere);

	Sphere blueSphere(3, vec3(5, 0, -25), vec3(0.65, 0.77, 0.97),0);
	renderer.shapeVec.push_back(&blueSphere);

	Sphere graySphere(3, vec3(-5.5, 0, -15), vec3(0.90, 0.90, 0.90),1);
	renderer.shapeVec.push_back(&graySphere);
	
	//add a plane
	Plane whitePlane(vec3(0,-1,0), vec3(0, -4, 0), vec3(1, 1, 1),1);
	renderer.shapeVec.push_back(&whitePlane);
	
	//add a triangle
	triangle rgbTriangle(vec3(30,0, -0.5), vec3(8, 0, 0), vec3(-8, 0, 0), vec3(0, 8,0), vec3(0, 1,0), vec3(0, 1, 0), vec3(0, 1, 0),1);
	renderer.shapeVec.push_back(&rgbTriangle);

	///light settings
	renderer.createLight(vec3(10,20,-10),vec3(1.0,1.0,1.0));

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

			//Checking for intersection of the shapes
			for (int i = 0; i < renderer.shapeVec.size(); i++)
			{
				Ray ray(org,dir);

				Intersection = renderer.shapeVec[i]->Intersection(&ray);
					if (Intersection == true)
					{
						t_arr.push_back(ray.hitDistance);

						//create a value to give to the pixel
						vec3 colVal=renderer.shapeVec[i]->getMyColor();

						//calling the calculate light function
						renderer.shapeVec[i]->ComputeColor(vec3(0.1, 0.1, 0.1), renderer.lightVec[0], &ray, renderer.shapeVec[i]->getMyColor(), colVal);

						//pushing back the color of the pixel in the collor array
						color_arr.push_back(colVal);
					}
			}

			if (t_arr.size() == 0)
			{
				image[x][y].x = 0.0;
				image[x][y].y = 0.0;
				image[x][y].z = 0.0;

				renderer.PutPixel32_nolock(screenSurface, x, y, renderer.convertColour(image[x][y]));
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

				renderer.PutPixel32_nolock(screenSurface, x, y, renderer.convertColour(image[x][y]));
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