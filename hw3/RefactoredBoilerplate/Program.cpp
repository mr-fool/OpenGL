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
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "RenderingEngine.h"
#include "Scene.h"

#include "global.h"
Scene* currentScene;

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

	currentScene = scene;

	//Main render loop
	while(!glfwWindowShouldClose(window)) {
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
	window = glfwCreateWindow(width, height, "HW3", 0, 0);
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
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	std::vector<Geometry>& objects = program->getScene()->getObjects();
	RenderingEngine* renderingEngine;

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		scrolling = 1;
		std::cout << "Key 1 is detected" << std::endl;
		mode = 1;
		program->getScene()->firstSetBezierCurves(objects);
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		scrolling = 1;
		std::cout << "Key 2 is detected" << std::endl;
		mode = 2;
		program->getScene()->secondSetBezierCurves(objects);
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		scrolling = 1;
		std::cout << "Key 3 is detected" << std::endl;
		program->getScene()->setText("John Smith", objects);


	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		scrolling = 1;
		std::cout << "Key 4 is detected" << std::endl;
		program->getScene()->setOTFText("John Smith", objects);
	}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		scrolling = 1;
		std::cout << "Key 5 is detected" << std::endl;
		program->getScene()->setThirdText("John Smith", objects);
	}
	if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
		std::cout << "Key 6 is detected" << std::endl;
		scrolling = 0;
		program->getScene()->setAlexText("The quick brown fox jumps over the lazy dog.", objects);
	}
	if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		std::cout << "Key 7 is detected" << std::endl;
		scrolling = 0;
		program->getScene()->setInconsolataText("The quick brown fox jumps over the lazy dog.", objects);
	}
	if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
		std::cout << "Key 8 is detected" << std::endl;
		scrolling = 0;
		program->getScene()->setGreatVibeText("The quick brown fox jumps over the lazy dog.", objects);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		std::cout << "Key UP is detected" << std::endl;
		scrolling = 2;
		
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		std::cout << "Key Down is detected" << std::endl;
		scrolling = 0;

	}
}

