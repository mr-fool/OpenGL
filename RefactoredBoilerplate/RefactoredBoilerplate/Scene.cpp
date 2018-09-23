/*
* Scene.cpp
*
*  Created on: Sep 10, 2018
*  Author: John Hall
*/
#define _USE_MATH_DEFINES

#include "Scene.h"

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include <GLFW/glfw3.h>

//so I can use the pi flag 
#include <cmath>

// vec2 and vec3 are part of the glm math library.
using namespace std;
using namespace glm;

extern int s;
extern int level;



Geometry&  Scene::createSquare(double side_length) {

	Geometry square;

	//Create the first iteration of square and diamond
	square.verts.push_back(vec3(-side_length, -side_length, 1.0f));
	square.verts.push_back(vec3(-side_length, side_length, 1.0f));
	square.verts.push_back(vec3(side_length , side_length , 1.0f));
	square.verts.push_back(vec3(side_length, -side_length, 1.0f));

	// set initial dimensions of the square
	square.drawMode = GL_LINE_LOOP;
	square.colors.push_back(glm::vec3(0.0f,1.0f,0.0f));
	square.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	square.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	square.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	return square;
}
Geometry& Scene::createDiamond(double side_length) {

	Geometry diamond;

	//Create the first iteration of square and diamond
	diamond.verts.push_back(vec3(0.0, -side_length , 1.0f));
	diamond.verts.push_back(vec3(-side_length, 0.0f , 1.0f));
	diamond.verts.push_back(vec3(0.0 , side_length , 1.0f));
	diamond.verts.push_back(vec3(side_length, 0.0f, 1.0f));


	// set initial dimensions of the square
	diamond.drawMode = GL_LINE_LOOP;
	diamond.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	diamond.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	diamond.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	diamond.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	
	return diamond;
}


void Scene::diamondAndSquare(int level, vector<Geometry> &objects) {
	objects.clear();
	double side_length = 0.9;
	double size = side_length / 2;

	for (int i = 1; i <= level; i++) {
		Geometry square = Geometry(Scene::createSquare(size));
		Geometry diamond = Geometry(Scene::createDiamond(size));

		RenderingEngine::assignBuffers(square);
		RenderingEngine::assignBuffers(diamond);

		RenderingEngine::setBufferData(square);
		RenderingEngine::setBufferData(diamond);
		objects.push_back(square);
		objects.push_back(diamond);
		size = size/2;
	}
	
}

void Scene::createSpiral(int level , vector<Geometry> &objects) {
	objects.clear();
	vec3 startColor(0.0, 1.0, 0.5);
	vec3 endColor(1.0, 0.0, 0.5);

	double side_length = level * 0.9;

	Geometry spiral;
	float t = 0;
	double bound = side_length * 2 * M_PI;
	double interval = 0.01;
	float a = (1 / bound);
	for (t = 0; t<bound; t += interval) {
		spiral.verts.push_back(vec3(a*t*cos(t-2.5), -a*t*sin(t-2.5),1.0f));
		spiral.colors.push_back(startColor*(1 - (a*t)) + endColor * (a*t));
	}
	RenderingEngine::assignBuffers(spiral);

	RenderingEngine::setBufferData(spiral);

	objects.push_back(spiral);
}

void Scene::iterationUp()
{
	//do something
}

void Scene::iterationDown()
{
//do something
}
Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {
	//pick(scene, level);
	//diamondAndSquare(6, objects);
	createSpiral(5, objects);
}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

