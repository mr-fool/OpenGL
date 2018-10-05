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

//For debugging
#include <string>
#include <iostream>


//Random
#include <stdlib.h>

// vec2 and vec3 are part of the glm math library.
using namespace std;
using namespace glm;

extern int level;
extern int scene;
extern int reloadLevel;

std::vector<Geometry>& Scene::getObjects()
{
	return this->objects;
}

Geometry* Scene::createSquare(double side_length) {

	Geometry *square = new Geometry();

	//Create the first iteration of square and diamond
	square->verts.push_back(vec3(-side_length, -side_length, 1.0f));
	square->verts.push_back(vec3(-side_length, side_length, 1.0f));
	square->verts.push_back(vec3(side_length, side_length, 1.0f));
	square->verts.push_back(vec3(side_length, -side_length, 1.0f));

	// set initial dimensions of the square
	square->drawMode = GL_LINE_LOOP;
	square->colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	square->colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	square->colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	square->colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	return square;
}
Geometry* Scene::createDiamond(double side_length) {

	Geometry *diamond = new Geometry();

	//Create the first iteration of square and diamond
	diamond->verts.push_back(vec3(0.0, -side_length , 1.0f));
	diamond->verts.push_back(vec3(-side_length, 0.0f , 1.0f));
	diamond->verts.push_back(vec3(0.0 , side_length , 1.0f));
	diamond->verts.push_back(vec3(side_length, 0.0f, 1.0f));


	// set initial dimensions of the square
	diamond->drawMode = GL_LINE_LOOP;
	diamond->colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	diamond->colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	diamond->colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	diamond->colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	
	return diamond;
}


void Scene::diamondAndSquare(int level, vector<Geometry> &objects) {
	objects.clear();
	double side_length = 1.5;
	double size = side_length / 2;

	for (int i = 1; i <= level; i++) {
		Geometry square = *Scene::createSquare(size);
		Geometry diamond =  *Scene::createDiamond(size);

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

void Scene::createTriangle(int level, vec3 pointA, vec3 pointB, vec3 pointC, vec3 color){

	if (level <= 0) {
		//Create a base triangle
		//Additional triangles can be created by pushing groups of three more vertices into the verts vector
		Geometry triangle;
		triangle.verts.push_back(pointA);
		triangle.verts.push_back(pointB);
		triangle.verts.push_back(pointC);

		//Colors are stored per vertex in the order of the vertices
		triangle.colors.push_back(color);
		triangle.colors.push_back(color);
		triangle.colors.push_back(color);

		triangle.drawMode = GL_TRIANGLES;

		//Construct vao and vbos for the triangle
		RenderingEngine::assignBuffers(triangle);

		//Send the triangle data to the GPU
		//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
		RenderingEngine::setBufferData(triangle);

		//Add the triangle to the scene objects
		objects.push_back(triangle);
	}
	else {
		createTriangle(level - 1, pointA, vec3((pointA.x + pointB.x) / 2, (pointA.y + pointB.y) / 2, 1.0f), vec3((pointA.x + pointC.x) / 2, (pointA.y + pointC.y) / 2, 1.0f), vec3(1.0, 0.0, 0.0));
		createTriangle(level - 1, pointB, vec3((pointB.x + pointA.x) / 2, (pointB.y + pointA.y) / 2, 1.0f), vec3((pointB.x + pointC.x) / 2, (pointB.y + pointC.y) / 2, 1.0f), vec3(0.8, 1.2, 0.0));
		createTriangle(level - 1, pointC, vec3((pointC.x + pointA.x) / 2, (pointC.y + pointA.y) / 2, 1.0f), vec3((pointC.x + pointB.x) / 2, (pointC.y + pointB.y) / 2, 1.0f), vec3(0.8, 0.8, 1.2));
	}
}

void Scene::sierpinjski(int level , vector<Geometry> &objects) {
	objects.clear();

	//Base Triangle point
	vec3 pointA = vec3(-0.6f, -0.4f, 1.0f);
	vec3 pointB = vec3(0.0f, 0.6f, 1.0f);
	vec3 pointC = vec3(0.6f, -0.4f, 1.0f);

	//Base color
	vec3 color = vec3(1.0f, 0.0f, 0.0f);
	createTriangle(level, pointA, pointB, pointC, color);
}

void Scene::createTriangleReloaded(int reloadLevel, vec3 pointA, vec3 pointB, vec3 pointC, vec3 color ) {
	objects.clear();
	//Step 1
	vec3 currentPoint = pointA;
	Geometry triangle;
	triangle.verts.push_back(currentPoint);
	triangle.colors.push_back(color);
	triangle.drawMode = GL_POINTS;
	/*RenderingEngine::assignBuffers(triangle);
	RenderingEngine::setBufferData(triangle);
	objects.push_back(triangle);*/

	for(int i = 0; i < reloadLevel; i++) {
		//Step 2
		int choice = rand() % 3;
		vec3 randomPoint;
		if (choice == 0) {
			randomPoint = pointB;
		}
		else if (choice == 1) {
			randomPoint = pointC;
		}
		else {
			randomPoint = pointA;
		}
		vec3 midpoint = vec3((currentPoint.x + randomPoint.x) / 2, (currentPoint.y + randomPoint.y)/2, 1.0f);
		triangle.verts.push_back(midpoint);
		triangle.colors.push_back(color);
		triangle.drawMode = GL_POINTS;
		
		//Step 3
		currentPoint = midpoint;
	}
	RenderingEngine::assignBuffers(triangle);
	RenderingEngine::setBufferData(triangle);
	objects.push_back(triangle);
	
}
void Scene::sierpinjskiReloaded(int reloadLevel, vector<Geometry> &objects) {
	objects.clear();

	//Base Triangle point
	vec3 pointA = vec3(-0.6f, -0.4f, 1.0f);
	vec3 pointB = vec3(0.0f, 0.6f, 1.0f);
	vec3 pointC = vec3(0.6f, -0.4f, 1.0f);

	vec3 color = vec3(1.0f, 0.0f, 0.0f);
	createTriangleReloaded(reloadLevel, pointA, pointB, pointC, color);
}

void Scene::iterationUp()
{
	level++;
}

void Scene::iterationDown()
{
	level--;
}


Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {
	//createTriangle();
	diamondAndSquare(1, objects);
	//createSpiral(5, objects);

}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

