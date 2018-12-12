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
#include <glad/glad.h>
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
void Scene::generateSphere(vector<vec3>& positions, vector<vec3>& normals, vector<vec2>& uvs, vector<unsigned int>& indices, vec3 center, float radius, int divisions) {
	objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();
	MyTexture texture;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	float step = 1.f / (float)(divisions - 1);
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
			vec3 pos = vec3(u, v, 0.0f);
			vec3 normal = normalize(pos - center);

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
}
/*void Scene::sphere() {
	objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();
	MyTexture texture;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Initialize Loader
	objl::Loader Loader;

	// Load .obj File
	bool loadout = Loader.LoadFile("sphere.obj");
	for (int i = 0; i < Loader.LoadedMeshes[0].Vertices.size(); i++) {
		cout << Loader.LoadedMeshes[i].Vertices[i].Position.X << endl;
	}
}*/
Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {

	MyTexture texture;
	InitializeTexture(&texture, "image1-mandrill.png", GL_TEXTURE_RECTANGLE);

	//Load texture uniform
	//Shaders need to be active to load uniforms
	glUseProgram(renderer->shaderProgram);
	//Set which texture unit the texture is bound to
	glActiveTexture(GL_TEXTURE0);
	//Bind the texture to GL_TEXTURE0
	glBindTexture(GL_TEXTURE_RECTANGLE, texture.textureID);
	//Get identifier for uniform
	GLuint uniformLocation = glGetUniformLocation(renderer->shaderProgram, "imageTexture");
	//Load texture unit number into uniform
	glUniform1i(uniformLocation, 0);

	if (renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}

	// three vertex positions and assocated colours of a triangle
	rectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(-0.9f, 0.9f, 1.0f));



	rectangle.drawMode = GL_TRIANGLES;

	rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), 0.f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, float(texture.height)));

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(rectangle);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(rectangle);

	//Add the triangle to the scene objects
	objects.push_back(rectangle);

}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

