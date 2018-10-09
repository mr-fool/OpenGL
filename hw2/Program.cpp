/*
* Program.cpp
*
*  Created on: Sep 10, 2018
*      Author: John Hall
*/

#include "Program.h"

#include <iostream>
#include <string>

//**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "RenderingEngine.h"
#include "Scene.h"

#include "texture.h"


//Pi
#define _USE_MATH_DEFINES
#include <math.h>

#include <string>     // std::string, std::to_string

#include "global.h"
#include <algorithm>

Program::Program() {
	setupWindow();
}

Program::~Program() {
	//Must be cleaned up in the destructor because these are allocated to the heap
	delete renderingEngine;
	delete scene;
}

void Program::start() {
	renderingEngine = new RenderingEngine();
	scene = new Scene(renderingEngine);

	//Main render loop
	while (!glfwWindowShouldClose(window)) {
		scene->displayScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

void Program::setupWindow() {
	//Initialize the GLFW windowing system
	if (!glfwInit()) {
		std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
		return;
	}

	//Set the custom error callback function
	//Errors will be printed to the console
	glfwSetErrorCallback(ErrorCallback);

	//Attempt to create a window with an OpenGL 4.1 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 1024;
	int height = 1024;
	window = glfwCreateWindow(width, height, "HW2", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}

	//So that we can access this object on key callbacks...
	glfwSetWindowUserPointer(window, this);

	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);

	//Bring the new window to the foreground (not strictly necessary but convenient)
	glfwMakeContextCurrent(window);


	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
	if (!gladLoadGL()) {
		std::cout << "GLAD init failed" << std::endl;
		return;
	}

	//Query and print out information about our OpenGL environment
	QueryGLVersion();
}



void Program::QueryGLVersion() {
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

	std::cout << "OpenGL [ " << version << " ] "
		<< "with GLSL [ " << glslver << " ] "
		<< "on renderer [ " << renderer << " ]" << std::endl;
}

void ErrorCallback(int error, const char* description) {
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}

static int scene = 1;
//rotation
bool shiftModifier = false;
float theta = 0.0;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	MyTexture texture;
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	std::vector<Geometry>& objects = program->getScene()->getObjects();

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		theta = 0;
		scale = 1;
		std::cout << "Key 1 is detected" << std::endl;
		program->getScene()->changeImage("image1-mandrill.png", objects, theta);
		scene = 1;

	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		theta = 0;
		scale = 1;
		std::cout << "Key 2 is detected" << std::endl;
		program->getScene()->changeImage("image2-uclogo.png", objects, theta);
		scene = 2;
	}

	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		theta = 0;
		scale = 1;
		std::cout << "Key 3 is detected" << std::endl;
		program->getScene()->changeImage("image3-aerial.jpg", objects, theta);
		scene = 3;
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		theta = 0;
		scale = 1;
		std::cout << "Key 4 is detected" << std::endl;
		program->getScene()->changeImage("image4-thirsk.jpg", objects, theta);
		scene = 4;
	}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		theta = 0;
		scale = 1;
		std::cout << "Key 5 is detected" << std::endl;
		program->getScene()->changeImage("image5-pattern.png", objects, theta);
		scene = 5;
	}
	if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
		theta = 0;
		scale = 1;
		std::cout << "Key 6 is detected" << std::endl;
		program->getScene()->changeImage("image6-bubble.png", objects, theta);
		scene = 6;
	}
	if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		theta = 0;
		scale = 1;
		std::cout << "Key 7 is detected" << std::endl;
		program->getScene()->changeImage("image7.jpg", objects, theta);
		scene = 7;
	}
	if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
		theta = 0;
		scale = 1;
		std::cout << "Key 8 is detected" << std::endl;
		program->getScene()->changeImage("image8.jpg", objects, theta);
		scene = 8;
	}


	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
		shiftModifier = true;
	}
	if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS) {
		shiftModifier = true;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && shiftModifier == true) {
		theta -= M_PI / 6;
		std::cout << "theta value " + std::to_string(theta) << std::endl;
		

	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && shiftModifier == true) {
		theta += M_PI / 6;
		std::cout << "theta value " + std::to_string(theta) << std::endl;
		
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS && shiftModifier == true) {
		scale +=0.01;
		std::cout << "scale value " + std::to_string(scale) << std::endl;

	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && shiftModifier == true) {
		scale = std::max(0.0, scale - 0.01);
		std::cout << "scale value " + std::to_string(scale) << std::endl;

	}

	//greyscale
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		std::cout << "Key Q is detected" << std::endl;
		colorState = 2; // L = 0.333R + 0.333G + 0.333B
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		std::cout << "Key W is detected" << std::endl;
		colorState = 3; // L = 0.299R + 0.587G + 0.114B
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		std::cout << "Key E is detected" << std::endl;
		colorState = 4; // L = 0.213R + 0.715G + 0.072B
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		std::cout << "Key R is detected" << std::endl;
		colorState = 5; // inverted color
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		std::cout << "Key T is detected" << std::endl;
		colorState = 6; // sepia effect
	}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		std::cout << "Key Z is detected" << std::endl;
		colorState = 1; // normal
	}


	//Edge effect
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		std::cout << "Key S is detected" << std::endl;
		colorState = 7; // vertical sobel
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		std::cout << "Key D is detected" << std::endl;
		colorState = 8; // horizontal sobel
	}
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		std::cout << "Key F is detected" << std::endl;
		colorState = 9; // horizontal sobel
	}

}

void mouse_callback(GLFWwindow* window, int button, int action, int mods){
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		return;
	}
	//mouse drag
}

