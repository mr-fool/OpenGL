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
//#include "vld.h"


float focalLen = 470.0f;

//Different Objects and Shapes
struct Ray {
	glm::vec3 origin;
	glm::vec3 direction;
};

struct Sphere {
	glm::vec3 center;
	float radius;
	glm::vec3 color;
	int material;   // 0 = phong, 1 = transparent, 2 = mirror
	float Kd;       // diffuse, refraction index, or
	float Ks;
	float n;
	float Ir;
};

struct Triangle {
	glm::vec3 p0;
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 color;
	int material;
	float Kd;
	float Ks;
	float n;
	float Ir;
};

struct Plane {
	glm::vec3 point;
	glm::vec3 normal;
	glm::vec3 color;
	int material;
	float Kd;
	float Ks;
	float n;
	float Ir;
};

//normalizing
float norm(glm::vec3 a) {
	return (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
}
glm::vec3 normalize(glm::vec3 a) {
	float n = norm(a);
	if (n > 0) {
		float w = 1 / sqrt(n);
		a.x *= w;
		a.y *= w;
		a.z *= w;
	}
	return a;
}
float findMagnitude(glm::vec3 v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

glm::vec3 crossProduct(glm::vec3 a, glm::vec3 b) {
	return glm::vec3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

float dotProduct(glm::vec3 a, glm::vec3 b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float findDiscriminant(float a, float b, float c) {
	return pow(b, 2) - a * c;
}

void Program::generateRay(int width, int height, int fov) {

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			float x = -width / 2 + i + 0.5;
			float y = height / 2 - j + 0.5;
			float z = -fov;
			//float z = (width / 2) / tan(fov * 180 / 3.14159265358979323846);
			Ray ray;
			ray.origin = glm::vec3(0, 0, 0);
			ray.direction = glm::vec3(x, y, z);
			float mag = findMagnitude(ray.direction);
			ray.direction.x /= mag;
			ray.direction.y /= mag;
			ray.direction.z /= mag;

			//Need to do some color magic

			image.SetPixel(x / (width / 2), y / (height / 2) , glm::vec3(1,0,0) );
		}
	}
	std::cout << "generate ray is being called" << std::endl;
}

//testing normalization
glm::vec3 testing = glm::vec3(0,2.5,-7.75);
glm::vec3 normalizeValue = normalize(testing);


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
	generateRay(100, 100,focalLen);
	std::cout << "normalize value " + glm::to_string(normalizeValue) << std::endl;

	

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
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
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
