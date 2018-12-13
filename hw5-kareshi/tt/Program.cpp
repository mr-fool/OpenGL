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
#include "global.h"

extern ArcballCamera ArcballCam;


using namespace std;
using namespace glm;


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
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (action == GLFW_PRESS)
	{
		
		ArcballCam.active = true;
		ArcballCam.cur_mpos.x = ArcballCam.last_mpos.x = xpos;
		ArcballCam.cur_mpos.y = ArcballCam.last_mpos.y = ypos;
		std::cout << "arcball active" << std::endl;
		std::cout << std::endl;
		
	}
	else if (action == GLFW_RELEASE)
	{
		ArcballCam.active = false;
		ArcballCam.last_mpos.x = xpos;
		ArcballCam.last_mpos.y = ypos;
		std::cout << "arcball inactive" << std::endl;
		std::cout << std::endl;
	}
}

void cursor_position_callback(GLFWwindow* window, double x, double y) {
	
	
	if (ArcballCam.active == true)
	{
		ArcballCam.last_mpos.x = x;
		ArcballCam.last_mpos.y = y;
		std::cout << "x is : " << ArcballCam.last_mpos.x << std::endl;
		std::cout << "y is : " << ArcballCam.last_mpos.y << std::endl;
	}	
	
	
}
/*void mousePosCallback(GLFWwindow* window, double xpos, double ypos) {
	//mousePressed = (action == GLFW_PRESS);

}*/
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
	window = glfwCreateWindow(width, height, "HW5", 0, 0);
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

	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	
	glfwSetCursorPosCallback(window, cursor_position_callback);

	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
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

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	MyTexture texture;
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	std::vector<Geometry>& objects = program->getScene()->getObjects();


}
