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

#include "GlyphExtractor.h"
#include "global.h"

std::vector<Geometry>& Scene::getObjects(){
	return this->objects;
}

void Scene::firstSetBezierCurves(std::vector<Geometry> &objects) {
	objects.clear();
	spiral.verts.clear();
	//first set
	spiral.verts.push_back(glm::vec3(1.0, 1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(2.0, -1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(0.0, -1.0, 1.0f));

	//second set
	spiral.verts.push_back(glm::vec3(0.0, -1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(-2.0, -1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(-1.0, 1.0, 1.0f));

	//third set
	spiral.verts.push_back(glm::vec3(-1.0, 1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(0.0, 1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(1.0, 1.0, 1.0f));
	//fourth set
	spiral.verts.push_back(glm::vec3(1.2, 0.5, 1.0f));
	spiral.verts.push_back(glm::vec3(2.5, 1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(1.3, -0.4, 1.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.drawMode = GL_PATCHES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(spiral);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(spiral);

	//Add the triangle to the scene objects
	objects.push_back(spiral);
}

void Scene::secondSetBezierCurves(std::vector<Geometry> &objects) {
	objects.clear();
	spiral.verts.clear();
	//first set
	spiral.verts.push_back(glm::vec3(1.0, 1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(4.0, 0.0, 1.0f));
	spiral.verts.push_back(glm::vec3(6.0, 2.0, 1.0f));
	spiral.verts.push_back(glm::vec3(9.0, 1.0, 1.0f));

	//second set
	spiral.verts.push_back(glm::vec3(8.0, 2.0, 1.0f));
	spiral.verts.push_back(glm::vec3(0.0, 8.0, 1.0f));
	spiral.verts.push_back(glm::vec3(0.0, -2.0, 1.0f));
	spiral.verts.push_back(glm::vec3(8.0, 4.0, 1.0f));

	//third set
	spiral.verts.push_back(glm::vec3(5.0, 3.0, 1.0f));
	spiral.verts.push_back(glm::vec3(3.0, 2.0, 1.0f));
	spiral.verts.push_back(glm::vec3(3.0, 3.0, 1.0f));
	spiral.verts.push_back(glm::vec3(5.0, 2.0, 1.0f));

	//fourth set
	spiral.verts.push_back(glm::vec3(3.0, 2.2, 1.0f));
	spiral.verts.push_back(glm::vec3(3.5, 2.7, 1.0f));
	spiral.verts.push_back(glm::vec3(3.5, 3.3, 1.0f));
	spiral.verts.push_back(glm::vec3(3.0, 3.8, 1.0f));

	//fifth set
	spiral.verts.push_back(glm::vec3(2.8, 3.5, 1.0f));
	spiral.verts.push_back(glm::vec3(2.4, 3.8, 1.0f));
	spiral.verts.push_back(glm::vec3(2.4, 3.2, 1.0f));
	spiral.verts.push_back(glm::vec3(2.8, 3.5, 1.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.drawMode = GL_PATCHES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(spiral);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(spiral);

	//Add the triangle to the scene objects
	objects.push_back(spiral);
}

void Scene::renderingFonts(std::vector<Geometry> &objects) {
	objects.clear();
	spiral.verts.clear();
	GlyphExtractor g;
	g.LoadFontFile("fonts/alex-brush/AlexBrush-Regular.ttf");
	MyGlyph a = g.ExtractGlyph('a');
	for (unsigned int i = 0; i < a.contours.size(); i++) {
		std::cout << "Contour " << i << std::endl;
		for (unsigned int j = 0; j < a.contours[i].size(); j++) {
			std::cout << "Bezier curve " << j << std::endl;
			for (unsigned int k = 0; k <= a.contours[i][j].degree; k++) {
				std::cout << "x " << a.contours[i][j].x[k] << std::endl;
				std::cout << "y " << a.contours[i][j].y[k] << std::endl;
				std::cout << std::endl;
			}
		}
	}
}

Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {

	//first set
	spiral.verts.push_back(glm::vec3(1.0, 1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(2.0, -1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(0.0, -1.0, 1.0f));

	//second set
	spiral.verts.push_back(glm::vec3(0.0, -1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(-2.0, -1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(-1.0, 1.0, 1.0f));

	//third set
	spiral.verts.push_back(glm::vec3(-1.0, 1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(0.0, 1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(1.0, 1.0, 1.0f));
	//fourth set
	spiral.verts.push_back(glm::vec3(1.2, 0.5, 1.0f));
	spiral.verts.push_back(glm::vec3(2.5, 1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(1.3, -0.4, 1.0f));

	spiral.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3( 1.0f,  0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	spiral.drawMode = GL_PATCHES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(spiral);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(spiral);

	//Add the triangle to the scene objects
	objects.push_back(spiral);

	/*GlyphExtractor g;
	g.LoadFontFile("fonts/alex-brush/AlexBrush-Regular.ttf");
	MyGlyph a = g.ExtractGlyph('a');*/

	/*for (unsigned int i = 0; i < a.contours.size(); i++) {
		std::cout << "Contour " << i << std::endl;
		for(unsigned int j = 0; j < a.contours[i].size(); j++) {
			std::cout << "Bezier curve " << j << std::endl;
			for(unsigned int k = 0; k <= a.contours[i][j].degree; k++) {
				std::cout << "x " << a.contours[i][j].x[k] << std::endl;
				std::cout << "y " << a.contours[i][j].y[k] << std::endl;
				std::cout << std::endl;
			}
		}
	}*/

}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

