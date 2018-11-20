/*
 * Program.h
 *	Base class of a rendering program. Has a scene to render, a rendering engine and a window to render to.
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "imagebuffer.h"
#include "ray.h"

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
struct GLFWwindow;

struct Sphere {
	glm::vec3 c;
	float r;
	glm::vec3 colour;
	glm::vec3 n;
	glm::vec3 intersect;
	float intmag;
};

struct Triangle {
	glm::vec3 pointA;
	glm::vec3 pointB;
	glm::vec3 pointC;
	glm::vec3 color;
};

struct Light {
	glm::vec3 postion;
	glm::vec3 color;
};

struct Plane {
	glm::vec3 point;
	glm::vec3 normal;
	glm::vec3 color;
};

struct Scene {
	std::vector<Triangle> *tris;
	std::vector<Light> *lights;
	std::vector<Plane> *planes;
	std::vector<Sphere> *spheres;
};

class Program {
public:
	Program();
	virtual ~Program();

	//Creates the rendering engine and the scene and does the main draw loop
	void start();

	//Initializes GLFW and creates the window
	void setupWindow();

	//Prints system specs to the console
	void QueryGLVersion();

    void generateRay(int width, int height, glm::vec3 lower_left_corner, glm::vec3 up, glm::vec3 origin, Scene s);
	glm::vec3 rayColor(const ray& r);
		
	//making it public for easier access
	ImageBuffer image;

private:
	GLFWwindow* window;
      
  
};

//Functions passed to GLFW to handle errors and keyboard input
//Note, GLFW requires them to not be member functions of a class
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif /* PROGRAM_H_ */
