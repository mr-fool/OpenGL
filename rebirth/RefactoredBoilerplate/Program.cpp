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
#include <glm/ext.hpp>
#include "ray.h"

//#include "vld.h"
/*Tirangle
u = v1-v0, v = v2-v0, r(t) = r.o + t * r.d,
Let h = (a,b,t0)^T, M = [ u, v, -d], then:
h = inverse(M) * r.o
intersection with triangle plane: r(t0)
Check whether it is valid: t>0
Check whether inside tri: 0<a, 0<b, a+b<1
the columns of m are made of u, v, -r.d

*/

float focalLen = 470.0f;

glm::vec3 Program::rayColor(const ray& r) {
	glm::vec3 unit_direction = glm::normalize(r.direction());
	float t = 0.5* (unit_direction.y + 1.0);
	return (1.0 - t)* glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1.0);

}

void Program::generateRay(int width, int height, glm::vec3 lower_left_corner, glm::vec3 horizontal, glm::vec3 vertical, glm::vec3 origin) {
	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {
			float u = float(i) / float(width);
			float v = float(j) / float(height);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			glm::vec3 col = rayColor(r);
			image.SetPixel(i, j, col);

		}
	}
	//Main render loop
	while (!glfwWindowShouldClose(window)) {
		image.Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

bool hit_sphere(const glm::vec3& center, float radius, const ray& r) {
	glm::vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc  , r.direction()  );
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	return (discriminant > c);
	
}
glm::vec3 sphereColor(const ray& r) {
	/*glm::vec3 horizontal = glm::vec3(4, 0, 0);
	glm::vec3 vertical = glm::vec3(0, 2, 0);
	glm::vec3 lower_left_corner = glm::vec3(-2, -1, -1);
	glm::vec3 origin = glm::vec3(0, 0, 0);*/
	//ray r(origin, lower_left_corner + u * horizontal + v * vertical);
	if (hit_sphere(glm::vec3(0, 0, -1), 0.5, r)) {
		return glm::vec3(1, 0, 0);
	}
	std::cout << "The r.direction is " + glm::to_string( r.direction() ) << std::endl;
	glm::vec3 unit_direction = glm::normalize(r.direction());
	float t = 0.5 * (unit_direction.y + 1.0);
	glm::vec3 result = (1 - t) * glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1.0);
	std::cout << "The result is " + glm::to_string(result) << std::endl;
	return (1 - t) * glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1.0);
}

Program::Program() {
        setupWindow();
}

Program::~Program() {
  
}

void Program::start() {
	image.Initialize();
	std::cout << "image width is " + std::to_string( image.Width() )<< std::endl;
	std::cout << "image height is " + std::to_string( image.Height() )<< std::endl;
	for (unsigned int i = 0; i < image.Width(); i++) {
		for (unsigned int j = 0; j < image.Height(); j++) {
			//set pixel colors here
			image.SetPixel(i, j, glm::vec3(1.0, 1.0, 1.0));
		}
	}
	glm::vec3 horizontal = glm::vec3(4, 0, 0);
	glm::vec3 vertical = glm::vec3(0, 2, 0);
	glm::vec3 lower_left_corner = glm::vec3(-2, -1, -1);
	glm::vec3 origin = glm::vec3(0, 0, 0);
	ray testing = ray(origin, lower_left_corner + horizontal + vertical);
	sphereColor(testing);
	generateRay(200, 100, glm::vec3(-2, -1, -1), glm::vec3(4, 0, 0), glm::vec3(0, 2, 0), glm::vec3(0, 0, 0));

	//Main render loop
	while(!glfwWindowShouldClose(window)) {
	    image.Render();
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
	window = glfwCreateWindow(width, height, "HW4", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}

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

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		std::cout << "Key 1 is pressed" << std::endl;
	}
}
