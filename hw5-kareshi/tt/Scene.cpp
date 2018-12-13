/*
 * Scene.cpp
 *
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#include "Scene.h"

#include <iostream>

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
 //**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "texture.h"
#include <vector>
//#include "parser.h"
// fStream - STD File I/O Library
#include <fstream>
using namespace std;
using namespace glm;
#define PI 3.141592653589793238462643383

std::vector<Geometry>& Scene::getObjects() {
	return this->objects;
}
vec3 getSphereCoords(float u, float v, float center, float radius) {
	return vec3(radius * cos(2.f * PI * u) * sin(PI * v),
		radius * sin(2.f * PI * u) * sin(PI * v),
		radius * cos(PI * v)) + center;
}

void Scene::generateSphere() {
	int divisions = 50;
	this->objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();
	MyTexture texture;
	
	float step = 1.f / (float)divisions;
	float u = 0.f;
	// Traversing the planes of time and space
	for (int i = 0; i < divisions; i++) {
		float v = 0.f;
		//Traversing the planes of time and space (again)
		for (int j = 0; j < divisions; j++) {


			vec3 topLeft = getSphereCoords(u, v, 0, 1);
			vec3 topRight = getSphereCoords(u + step, v, 0, 1);
			vec3 botLeft = getSphereCoords(u, v + step, 0, 1);
			vec3 botRight = getSphereCoords(u + step, v + step, 0, 1);

			rectangle.uvs.push_back(vec2(u, v));
			rectangle.uvs.push_back(vec2(u, v));
			rectangle.uvs.push_back(vec2(u, v));
			rectangle.uvs.push_back(vec2(u, v));
			rectangle.uvs.push_back(vec2(u, v));
			rectangle.uvs.push_back(vec2(u, v));


			rectangle.verts.push_back(topLeft);
			rectangle.verts.push_back(topRight);
			rectangle.verts.push_back(botLeft);

			rectangle.verts.push_back(botLeft);
			rectangle.verts.push_back(topRight);
			rectangle.verts.push_back(botRight);
			v += step;
		}

		u += step;

	}
	int windowHeight = 1024;
	int windowWidth = 1024;
	int max_u;
	int max_v;
	int offsetU;
	int offsetV;
	//aspect ratio
	if (texture.width / texture.height < windowWidth / windowHeight) {
		max_u = windowWidth * texture.height / windowHeight;
		max_v = texture.height;
		offsetU = 0.5*(texture.width - max_u);
		offsetV = 0;
		max_u += offsetU;
		max_v += offsetV;
	}
	else {
		max_u = texture.width;
		max_v = windowHeight * texture.width / windowWidth;
		offsetU = 0;
		offsetV = 0.5 *(texture.height - max_v);
		max_u += offsetU;
		max_v += offsetV;
	}
	rectangle.drawMode = GL_TRIANGLES;
	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(rectangle);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(rectangle);

	//Add the triangle to the scene objects
	objects.push_back(rectangle);

}

Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {
	int divisions = 50;
	objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();
	MyTexture texture;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	float step = 1.f / (float)divisions;
	float u = 0.f;
	// Traversing the planes of time and space
	for (int i = 0; i < divisions; i++) {
		float v = 0.f;
		//Traversing the planes of time and space (again)
		for (int j = 0; j < divisions; j++) {


			vec3 topLeft = getSphereCoords(u, v, 0, 1);
			vec3 topRight = getSphereCoords(u + step, v, 0, 1);
			vec3 botLeft = getSphereCoords(u, v + step, 0, 1);
			vec3 botRight = getSphereCoords(u + step, v + step, 0, 1);

			rectangle.uvs.push_back(vec2(u, v));
			rectangle.uvs.push_back(vec2(u, v));
			rectangle.uvs.push_back(vec2(u, v));
			rectangle.uvs.push_back(vec2(u, v));
			rectangle.uvs.push_back(vec2(u, v));
			rectangle.uvs.push_back(vec2(u, v));


			rectangle.verts.push_back(topLeft);
			rectangle.verts.push_back(topRight);
			rectangle.verts.push_back(botLeft);

			rectangle.verts.push_back(botLeft);
			rectangle.verts.push_back(topRight);
			rectangle.verts.push_back(botRight);
			v += step;
		}

		u += step;

	}

	rectangle.drawMode = GL_TRIANGLES;
	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(rectangle);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(rectangle);

	//Add the triangle to the scene objects
	objects.push_back(rectangle);

	P = glm::perspective(glm::radians(60.f), 1024.f/1024.f, 0.01f, 1000.f);
	M = glm::mat4(1);
	//hacked positions 
	V = glm::lookAt(glm::vec3(3, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.0, 1.0, 0.0));

}

Scene::~Scene() {

}

void Scene::displayScene() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//you gotta fix your code structure, and keep relevant data together easily accessible; Im mostly hacking into stuff to make it work
	
	ArcballCam.get_rotation_matrix(M, V, 1024, 1024);
	
	renderer->RenderScene(objects, M, V, P);
}

