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
#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> // glm::mat4

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"

//so I can take image name
#include <string>

std::vector<Geometry>& Scene::getObjects()
{
	return this->objects;
}

void Scene::changeImage(const char* imageName, std::vector<Geometry> &objects, float theta) {

	objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();
	MyTexture texture;
	InitializeTexture(&texture, imageName, GL_TEXTURE_RECTANGLE);

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
	//glm::mat4 trans;
	//trans = glm::rotate(trans, glm::radians(theta), glm::vec3(-0.9f, -0.9f, 1.0f));

	rectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(-0.9f, 0.9f, 1.0f));



	rectangle.drawMode = GL_TRIANGLES;

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


	rectangle.uvs.push_back(glm::vec2(float(offsetU), float(offsetV)));
	rectangle.uvs.push_back(glm::vec2(float(max_u), float(offsetV)));
	rectangle.uvs.push_back(glm::vec2(float(max_u), float(max_v)));
	rectangle.uvs.push_back(glm::vec2(float(offsetU), float(offsetV)));
	rectangle.uvs.push_back(glm::vec2(float(max_u), float(max_v)));
	rectangle.uvs.push_back(glm::vec2(float(offsetU), float(max_v)));

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(rectangle);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(rectangle);

	//Add the triangle to the scene objects
	objects.push_back(rectangle);
}

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

	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}

	// three vertex positions and assocated colours of a triangle
	

	
	rectangle.verts.push_back(glm::vec3( -0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f,  -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( -0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( 0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3( -0.9f, 0.9f, 1.0f));




	rectangle.drawMode = GL_TRIANGLES;
	

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


	rectangle.uvs.push_back(glm::vec2(float(offsetU), float(offsetV)));
	rectangle.uvs.push_back(glm::vec2(float(max_u), float(offsetV)));
	rectangle.uvs.push_back(glm::vec2(float(max_u), float(max_v)));
	rectangle.uvs.push_back(glm::vec2(float(offsetU), float(offsetV)));
	rectangle.uvs.push_back(glm::vec2(float(max_u), float(max_v)));
	rectangle.uvs.push_back(glm::vec2(float(offsetU), float(max_v)));

	/*rectangle.uvs.push_back(glm::vec2( 0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2( float(texture.width), 0.f));
	rectangle.uvs.push_back(glm::vec2( float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2( 0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2( float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, float(texture.height)));*/

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

