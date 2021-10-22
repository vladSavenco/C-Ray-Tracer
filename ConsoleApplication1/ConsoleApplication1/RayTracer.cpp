#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

#include <thread>
#include <future>

#include <SDL.h>
#include <glm/glm.hpp>

#include "Renderer.h"
#include "Ray.h"

#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

#include "GameObj.h"

using namespace std;
using namespace glm;

#define PI 3.14159265
SDL_Event event;

Renderer renderer;

bool Intersection;

//array of the distance of the ray hits
vector<float> t_arr;
vector<vec3> color_arr;
//ray direction and origin
vec3 dir, org;

bool shadowCalculation(Light light, Ray ray, shape &myShape)
{
	//calculate ray direction
	vec3 l = light.origin - ray.intersectPoint;
	vec3 normal = ray.intersectPoint - myShape.getPosition();

	//normalize vectors
	normal = normalize(normal);
	l = normalize(l);
	//create new ray
	Ray ray2(ray.intersectPoint,l);

	//if we hit any obj then there should be a shadow
	if (myShape.Intersection(&ray2) == true)
	{
		return true;
	}
	else
		return false;
}

void CheckIntersections(int i)
{
		//Checking for intersection of the shapes
		Ray ray(org, dir);

		Intersection = renderer.shapeVec[i]->Intersection(&ray);
		if (Intersection == true)
		{
			t_arr.push_back(ray.hitDistance);

			//create a value to give to the pixel
			vec3 colVal = renderer.shapeVec[i]->getMyColor();

			//calling the calculate light function
			renderer.shapeVec[i]->ComputeColor(vec3(0.1, 0.1, 0.1), renderer.LigtArr[0][0][0], &ray, renderer.shapeVec[i]->getMyColor(), colVal);

			//color_arr.push_back(colVal);

			//new check shadows
			vec3 finalCol = vec3(0, 0, 0);
			float divCount = 0;
			int count = 0;

			for (int j = 0; j < renderer.shapeVec.size(); j++)
			{
				if (i != j)
				{
					for (int x = 0; x < 1; x++)
					{
						for (int y = 0; y < 1; y++)
						{
							for (int z = 0; z < 1; z++)
							{
								Ray newRay(ray.intersectPoint, glm::normalize(renderer.LigtArr[x][y][z].origin - ray.intersectPoint));

								bool shadowIntersect = renderer.shapeVec[j]->Intersection(&newRay);

								divCount++;

								if (shadowIntersect == true)
								{
									count++;
									finalCol = finalCol + renderer.shapeVec[i]->getAmb();
								}
								else
								{
									finalCol = finalCol + colVal;
								}
							}
						}
					}
				}
			}

			if (count > 0)
			{
				color_arr.push_back(finalCol / divCount);
			}
			else
			{
				color_arr.push_back(colVal);
			}
			//check for shadows?
			/*for (int j = 0; j < renderer.shapeVec.size(); j++)
			{
				bool isInShadow = false;

				if (i == j)
				{
					continue;
				}

				//create a vec3 final color
				vec3 finalCol(0, 0, 0);

				for (int m = 0; m < renderer.lightVec.size(); m++)
				{
					if (shadowCalculation(renderer.lightVec[m], ray, *renderer.shapeVec[j]) == true)
					{
						isInShadow = true;
					}
					else
					{
						isInShadow = false;
					}

					if (isInShadow != true)
					{
						finalCol = finalCol+colVal;
					}
					if (isInShadow == true)
					{
						finalCol = finalCol + vec3 (0,0,0);
					}
				}

				finalCol.x = finalCol.x /9.0;
				finalCol.y = finalCol.y / 9.0;
				finalCol.z = finalCol.z / 9.0;

				//pushing back the color of the pixel in the collor array
				color_arr.push_back(finalCol);
			}*/
		}
}

int main(int argc, char* args[])
{

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


	float t, min_t, ColorVal;
	int i, whichone;
	vec3 ttvec, mat_color, final_Color, IntPt;
	 
	//add spheres
	Sphere redSphere(4, vec3(0, 0, -20), vec3(1.00, 0.32, 0.36), 0);
	renderer.shapeVec.push_back(&redSphere);

	Sphere yellowSphere(2, vec3(5, -1, -15), vec3(0.90, 0.76, 0.46),1);
	renderer.shapeVec.push_back(&yellowSphere);
	
	Sphere blueSphere(3, vec3(5, 0, -25), vec3(0.65, 0.77, 0.97),0);
	renderer.shapeVec.push_back(&blueSphere);
	
	Sphere graySphere(3, vec3(-5.5, 0, -15), vec3(0.90, 0.90, 0.90),1);
	renderer.shapeVec.push_back(&graySphere);
	
	//add a plane
	Plane whitePlane(vec3(0,1,0), vec3(0, -4, 0), vec3(1, 1, 1),1);
	renderer.shapeVec.push_back(&whitePlane);
	
	//add a triangle
	//triangle rgbTriangle(vec3(0,0, -2), vec3(1, 0, 0), vec3(-1, 0, 0), vec3(0, 1,0), vec3(1, 1,0), vec3(1, 1, 0), vec3(1, 1, 0),vec3(0,0.6,1),vec3(-0.4, -0.4, 1),vec3(0.4, -0.4, 1),1);
	//renderer.shapeVec.push_back(&rgbTriangle);

	//add pig
	//GameObj pig("./Models/Pig.obj", vec3(0, 0, -1), vec3(1, 1, 0), 1);
	//for (int i = 0; i < pig.triangleVec.size(); i++)
	//{
	//	renderer.shapeVec.push_back(&pig.triangleVec[i]);
	//}

	//create Lights
	renderer.createAreaLight(vec3(0, 0, 0), 1, vec3(1.0, 1.0, 1.0));

	org.x = 0.0; org.y = 0.0; org.z = 0.0;

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

			for (int i = 0; i < renderer.shapeVec.size(); i++)
			{
				CheckIntersections(i);
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

			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					cout << "key press" << endl;
					org.y = org.y + 1;
					cout << org.y << endl;
					//redraw window
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

								for (int i = 0; i < renderer.shapeVec.size(); i++)
								{
									CheckIntersections(i);
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
					break;

				case SDLK_DOWN:
					cout << "key press" << endl;
					org.y = org.y - 1;
					//redraw window
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

							for (int i = 0; i < renderer.shapeVec.size(); i++)
							{
								CheckIntersections(i);
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
					break;

				case SDLK_LEFT:
					cout << "key press" << endl;
					org.x = org.x - 1;
					//redraw window
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

							for (int i = 0; i < renderer.shapeVec.size(); i++)
							{
								CheckIntersections(i);
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
					break;

				case SDLK_RIGHT:
					cout << "key press" << endl;
					org.x = org.x + 1;
					//redraw window
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

							for (int i = 0; i < renderer.shapeVec.size(); i++)
							{
								CheckIntersections(i);
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
					break;
				}
			}
		}
	}

	renderer.closeSDL(window);
	return 0;
}