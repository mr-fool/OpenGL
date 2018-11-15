/*
 * Program.h
 *	Base class of a rendering program. Has a scene to render, a rendering engine and a window to render to.
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "imagebuffer.h"

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
struct GLFWwindow;

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

	//normalizing function
	float norm(glm::vec3 a);
	glm::vec3 normalize(glm::vec3 a);

	//find magnitude
	float findMagnitude(glm::vec3 v);

	//Cross Product
	glm::vec3 crossProduct(glm::vec3 a, glm::vec3 b);

	//Dot Product
	float dotProduct(glm::vec3 a, glm::vec3 b);

	//Find Discriminant
	float findDiscriminant(float a, float b, float c);

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
