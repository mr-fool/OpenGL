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
	line.verts.clear();
	spiral.type =  2;
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
	line.verts.clear();
	spiral.type = 3;
	//first set buttom curve
	spiral.verts.push_back(glm::vec3(1.0, 1.0, 1.0f));
	spiral.verts.push_back(glm::vec3(4.0, 0.0, 1.0f));
	spiral.verts.push_back(glm::vec3(6.0, 2.0, 1.0f));
	spiral.verts.push_back(glm::vec3(9.0, 1.0, 1.0f));

	//second set upper curve
	spiral.verts.push_back(glm::vec3(8.0, 2.0, 1.0f));
	spiral.verts.push_back(glm::vec3(0.0, 8.0, 1.0f));
	spiral.verts.push_back(glm::vec3(0.0, -2.0, 1.0f));
	spiral.verts.push_back(glm::vec3(8.0, 4.0, 1.0f));

	//third set inside right curve
	spiral.verts.push_back(glm::vec3(5.0, 3.0, 1.0f));
	spiral.verts.push_back(glm::vec3(3.0, 2.0, 1.0f));
	spiral.verts.push_back(glm::vec3(3.0, 3.0, 1.0f));
	spiral.verts.push_back(glm::vec3(5.0, 2.0, 1.0f));

	//fourth set inside left curve
	spiral.verts.push_back(glm::vec3(3.0, 2.2, 1.0f));
	spiral.verts.push_back(glm::vec3(3.5, 2.7, 1.0f));
	spiral.verts.push_back(glm::vec3(3.5, 3.3, 1.0f));
	spiral.verts.push_back(glm::vec3(3.0, 3.8, 1.0f));

	//fifth set fish head
	spiral.verts.push_back(glm::vec3(2.8, 3.5, 1.0f));
	spiral.verts.push_back(glm::vec3(2.4, 3.8, 1.0f));
	spiral.verts.push_back(glm::vec3(2.4, 3.2, 1.0f));
	spiral.verts.push_back(glm::vec3(2.8, 3.5, 1.0f));



	spiral.drawMode = GL_PATCHES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(spiral);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(spiral);

	//Add the triangle to the scene objects
	objects.push_back(spiral);
}
float charSize = 0;
float Scene::renderingFonts(char c, glm::vec2 offset, std::vector<Geometry> &objects) {
	GlyphExtractor g;
	g.LoadFontFile("fonts/lora/Lora-Regular.ttf");
	MyGlyph a = g.ExtractGlyph(c);
	for (unsigned int i = 0; i < a.contours.size(); i++) {
		//std::cout << "Contour " << i << std::endl;
		for (unsigned int j = 0; j < a.contours[i].size(); j++) {
			for (unsigned int k = 0; k <= a.contours[i][j].degree; k++) {
				if (a.contours[i][j].degree == 2) {
					mode = 3;
					spiral.type = 2;
					spiral.verts.push_back(glm::vec3(a.contours[i][j].x[k] + offset.x, a.contours[i][j].y[k], 1.0f));
				}
				if (a.contours[i][j].degree == 1) {
					linearTracker = 1;
					mode = 0;
					line.type = 1;
					line.verts.push_back(glm::vec3(a.contours[i][j].x[k] + offset.x, a.contours[i][j].y[k], 1.0f));
				}
				spiral.drawMode = GL_PATCHES;
				line.drawMode = GL_PATCHES;

				//Construct vao and vbos for the triangle
				RenderingEngine::assignBuffers(spiral);
				RenderingEngine::assignBuffers(line);
				//Send the triangle data to the GPU
				//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
				RenderingEngine::setBufferData(spiral);
				RenderingEngine::setBufferData(line);
				//Add the triangle to the scene objects
				objects.push_back(spiral);
				objects.push_back(line);

			}
		}
	}
	charSize = a.advance;
	return a.advance;
}
float Scene::renderingThirdFonts(char c, glm::vec2 offset, std::vector<Geometry> &objects) {
	GlyphExtractor g;
	g.LoadFontFile("fonts/amatic/Amatic-Bold.ttf");
	MyGlyph a = g.ExtractGlyph(c);
	for (unsigned int i = 0; i < a.contours.size(); i++) {
		//std::cout << "Contour " << i << std::endl;
		for (unsigned int j = 0; j < a.contours[i].size(); j++) {
			for (unsigned int k = 0; k <= a.contours[i][j].degree; k++) {
				if (a.contours[i][j].degree == 2) {
					mode = 3;
					spiral.type = 2;
					spiral.verts.push_back(glm::vec3(a.contours[i][j].x[k] + offset.x, a.contours[i][j].y[k], 1.0f));
				}
				if (a.contours[i][j].degree == 1) {
					linearTracker = 1;
					mode = 0;
					line.type = 1;
					line.verts.push_back(glm::vec3(a.contours[i][j].x[k] + offset.x, a.contours[i][j].y[k], 1.0f));
				}
				spiral.drawMode = GL_PATCHES;
				line.drawMode = GL_PATCHES;

				//Construct vao and vbos for the triangle
				RenderingEngine::assignBuffers(spiral);
				RenderingEngine::assignBuffers(line);
				//Send the triangle data to the GPU
				//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
				RenderingEngine::setBufferData(spiral);
				RenderingEngine::setBufferData(line);
				//Add the triangle to the scene objects
				objects.push_back(spiral);
				objects.push_back(line);

			}
		}
	}
	charSize = a.advance;
	return a.advance;
}
float Scene::renderingOTFFonts(char c, glm::vec2 offset, std::vector<Geometry> &objects) {
	GlyphExtractor g;
	g.LoadFontFile("fonts/source-sans-pro/SourceSansPro-Regular.otf");
	MyGlyph a = g.ExtractGlyph(c);
	for (unsigned int i = 0; i < a.contours.size(); i++) {
		//std::cout << "Contour " << i << std::endl;
		for (unsigned int j = 0; j < a.contours[i].size(); j++) {
			for (unsigned int k = 0; k <= a.contours[i][j].degree; k++) {
				if (a.contours[i][j].degree == 3) {
					mode = 4;
					spiral.type = 3;
					spiral.verts.push_back(glm::vec3(a.contours[i][j].x[k] + offset.x, a.contours[i][j].y[k], 1.0f));
				}
				if (a.contours[i][j].degree == 1) {
					linearTracker = 1;
					mode = 0;
					line.type = 1;
					line.verts.push_back(glm::vec3(a.contours[i][j].x[k] + offset.x, a.contours[i][j].y[k], 1.0f));
				}
				spiral.drawMode = GL_PATCHES;
				line.drawMode = GL_PATCHES;

				//Construct vao and vbos for the triangle
				RenderingEngine::assignBuffers(spiral);
				RenderingEngine::assignBuffers(line);
				//Send the triangle data to the GPU
				//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
				RenderingEngine::setBufferData(spiral);
				RenderingEngine::setBufferData(line);
				//Add the triangle to the scene objects
				objects.push_back(spiral);
				objects.push_back(line);

			}
		}
	}
	charSize = a.advance;
	return a.advance;
}
float Scene::renderingAlexFonts(char c, glm::vec2 offset, std::vector<Geometry> &objects) {
	GlyphExtractor g;
	g.LoadFontFile("fonts/alex-brush/AlexBrush-Regular.ttf");
	MyGlyph a = g.ExtractGlyph(c);
	for (unsigned int i = 0; i < a.contours.size(); i++) {
		//std::cout << "Contour " << i << std::endl;
		for (unsigned int j = 0; j < a.contours[i].size(); j++) {
			for (unsigned int k = 0; k <= a.contours[i][j].degree; k++) {
				if (a.contours[i][j].degree == 2) {
					mode = 5;
					spiral.type = 2;
					spiral.verts.push_back(glm::vec3(a.contours[i][j].x[k] + offset.x, a.contours[i][j].y[k], 1.0f));
				}
				if (a.contours[i][j].degree == 1) {
					linearTracker = 1;
					mode = 6;
					line.type = 1;
					line.verts.push_back(glm::vec3(a.contours[i][j].x[k] + offset.x, a.contours[i][j].y[k], 1.0f));
				}
				spiral.drawMode = GL_PATCHES;
				line.drawMode = GL_PATCHES;

				//Construct vao and vbos for the triangle
				RenderingEngine::assignBuffers(spiral);
				RenderingEngine::assignBuffers(line);
				//Send the triangle data to the GPU
				//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
				RenderingEngine::setBufferData(spiral);
				RenderingEngine::setBufferData(line);
				//Add the triangle to the scene objects
				objects.push_back(spiral);
				objects.push_back(line);

			}
		}
	}
	charSize = a.advance;
	return a.advance;
}
float Scene::setText(std::string s , std::vector<Geometry> &objects) {
	objects.clear();
	spiral.verts.clear();
	line.verts.clear();
	int str_off = s.size() / 2;
	glm::vec2 testing = glm::vec2(-str_off, 0);
	float textLength = 0;
	float x = 0;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		x = renderingOTFFonts(s[i], testing, objects);
		testing += glm::vec2(x, 0);
		textLength += x;
	}
	return textLength;
}
float Scene::setOTFText(std::string s, std::vector<Geometry> &objects) {
	objects.clear();
	spiral.verts.clear();
	line.verts.clear();
	int str_off = s.size() / 2;
	glm::vec2 testing = glm::vec2(-str_off, 0);
	float textLength = 0;
	float x = 0;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		x = renderingFonts(s[i], testing, objects);
		testing += glm::vec2(x, 0);
		textLength += x;
	}
	return textLength;
}
float Scene::setThirdText(std::string s, std::vector<Geometry> &objects) {
	objects.clear();
	spiral.verts.clear();
	line.verts.clear();
	int str_off = s.size() / 2;
	glm::vec2 testing = glm::vec2(-str_off, 0);
	float textLength = 0;
	float x = 0;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		x = renderingThirdFonts(s[i], testing, objects);
		testing += glm::vec2(x, 0);
		textLength += x;
	}
	return textLength;
}
float Scene::setAlexText(std::string s, std::vector<Geometry> &objects) {
	objects.clear();
	spiral.verts.clear();
	line.verts.clear();
	int str_off = s.size() / 5;
	glm::vec2 testing = glm::vec2(-str_off, 0);
	float textLength = 0;
	
	for (unsigned int i = 0; i < s.size(); i++)
	{
		offsetX = renderingAlexFonts(s[i], testing, objects);
		testing += glm::vec2(offsetX, 0);
		textLength += offsetX;
	}
	char space = '1';
	int counter = 0;
	/*while (true) {
		x = renderingAlexFonts(space, testing, objects);
		testing += glm::vec2(x, 0);
		textLength += x;
		//counter += 1;
		//std::cout << "counter is " << counter << std::endl;
	}*/
	return textLength;
}
Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {
	objects.clear();
	spiral.verts.clear();
	line.verts.clear();
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


	spiral.drawMode = GL_PATCHES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(spiral);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(spiral);

	//Add the triangle to the scene objects
	objects.push_back(spiral);


}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

