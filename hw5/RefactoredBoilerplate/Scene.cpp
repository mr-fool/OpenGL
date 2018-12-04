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

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include <vector>
using namespace std;
using namespace glm;
#define PI 3.141592653589793238462643383

std::vector<Geometry>& Scene::getObjects(){
	return this->objects;
}

void Scene::generateSphere(vector<vec3>& positions, vector<vec3>& normals,vector<vec2>& uvs, vector<unsigned int>& indices,vec3 center, float radius, int divisions){
	objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();
	MyTexture texture;
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
	float step = 1.f / (float)(divisions - 1);
	float u = 0.f;

	// Traversing the planes of time and space
	for (int i = 0; i < divisions; i++) {
		float v = 0.f;

		//Traversing the planes of time and space (again)
		for (int j = 0; j < divisions; j++) {
			vec3 pos = vec3(radius * cos(2.f * PI * u) * sin(PI * v),
				radius * sin(2.f * PI * u) * sin(PI * v),
				radius * cos(PI * v)) + center;

			vec3 normal = normalize(pos - center);

			rectangle.verts.push_back(pos);
			rectangle.verts.push_back(normal);
			rectangle.uvs.push_back(vec2(u, v));

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
Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {
	vec3 center = vec3(0.0);
	vector<vec3> earthPoints;
	vector<vec3> earthNormals;
	vector<vec2> earthUvs;
	float distScale = 35.0 / 149597870.7; // AU in km
	float radScale = 1.0 / 6378.1; // E in km
	vector<unsigned int> earthIndices;
	center = vec3(distScale * 149597890, 0.0, 0.0);
	float radius = pow(radScale * 6378.1, 0.5);
	int divisions = 72;
	MyTexture texture;
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
	float step = 1.f / (float)(divisions - 1);
	float u = 0.f;

	// Traversing the planes of time and space
	for (int i = 0; i < divisions; i++) {
		float v = 0.f;

		//Traversing the planes of time and space (again)
		for (int j = 0; j < divisions; j++) {
			vec3 pos = vec3(radius * cos(2.f * PI * u) * sin(PI * v),
				radius * sin(2.f * PI * u) * sin(PI * v),
				radius * cos(PI * v)) + center;

			vec3 normal = normalize(pos - center);

			rectangle.verts.push_back(pos);
			rectangle.verts.push_back(normal);
			rectangle.uvs.push_back(vec2(u, v));

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

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

