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

//For debugging
#include <string>
#include <iostream>

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
	int width = 720;
	int height = 720;
	window = glfwCreateWindow(width, height, "CPSC 453 HW1", 0, 0);
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

// --------------------------------------------------------------------------
// GLFW callback functions
static int level = 1;
static int scene = 1;
static int reloadLevel = 2000;
// handles keyboard input events
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	Program* program = (Program*)glfwGetWindowUserPointer(window);
	std::vector<Geometry>& objects = program->getScene()->getObjects();

	//for debugging
	std::cout << level << std::endl;
	std::cout << scene << std::endl;
	std::cout << reloadLevel << std::endl;


	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		level = 1;
		program->getScene()->diamondAndSquare(level, objects);
		scene = 1;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		level = 2;
		program->getScene()->createSpiral(level, objects);
		scene = 2;
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		level = 0;
		program->getScene()->sierpinjski(level, objects);
		scene = 3;
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		program->getScene()->sierpinjskiReloaded(reloadLevel, objects);
		scene = 4;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		//program->getScene()->iterationUp();
		level++;
		//reloadLevel = reloadLevel + 500;
		switch (scene) {
			case 1:
				program->getScene()->diamondAndSquare(level, objects);
				break;
			case 2:
				program->getScene()->createSpiral(level, objects);
				break;
			case 3:
				program->getScene()->sierpinjski(level, objects);
				break;
			/*case 4: //for debugging
				program->getScene()->sierpinjskiReloaded(reloadLevel, objects);
				break;*/
		}
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && level > 0) {
		//program->getScene()->iterationDown();
		//reloadLevel = reloadLevel - 500;
		level--;
		switch (scene) {
		case 1:
			program->getScene()->diamondAndSquare(level, objects);
			break;
		case 2:
			program->getScene()->createSpiral(level, objects);
			break;
		/*case 3:
			program->getScene()->sierpinjski(reloadLevel, objects);
			break;*/
		}
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && reloadLevel > 0) {
		//program->getScene()->iterationDown();
		reloadLevel = reloadLevel - 500;
		program->getScene()->sierpinjskiReloaded(reloadLevel, objects);
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		//program->getScene()->iterationDown();
		reloadLevel = reloadLevel + 500;
		program->getScene()->sierpinjskiReloaded(reloadLevel, objects);
	}
}
