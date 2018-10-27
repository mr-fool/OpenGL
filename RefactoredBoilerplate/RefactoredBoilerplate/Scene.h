/*
 * Scene.h
 *	Class for storing objects in a scene
 *  Created on: Sep 10, 2018
 *      Author: cb-ha
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "Geometry.h"

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;

class Scene {
public:
	Scene(RenderingEngine* renderer);
	virtual ~Scene();

	//Send geometry to the renderer
	void displayScene();
	void firstSetBezierCurves(std::vector<Geometry> &objects);
	void secondSetBezierCurves(std::vector<Geometry> &objects);
	float renderingFonts(char c, glm::vec2 offset, std::vector<Geometry> &objects);
	float renderingOTFFonts(char c, glm::vec2 offset, std::vector<Geometry> &objects);
	float renderingThirdFonts(char c, glm::vec2 offset, std::vector<Geometry> &objects);
	float renderingAlexFonts(char c, glm::vec2 offset, std::vector<Geometry> &objects);
	float setText(std::string s, std::vector<Geometry> &objects);
	float setAlexText(std::string s, std::vector<Geometry> &objects);
	float setOTFText(std::string s, std::vector<Geometry> &objects);
	float setThirdText(std::string s, std::vector<Geometry> &objects);
	std::vector<Geometry>& getObjects();
private:
	RenderingEngine* renderer;

	Geometry spiral;
	Geometry line;
	//list of objects in the scene
	std::vector<Geometry> objects;
};

#endif /* SCENE_H_ */
