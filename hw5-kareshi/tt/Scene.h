/*
 * Scene.h
 *	Class for storing objects in a scene
 *  Created on: Sep 10, 2018
 *      Author: cb-ha
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <glm/glm.hpp>
#include <GLM/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Geometry.h"
#include "ArcballCamera.h"

extern ArcballCamera ArcballCam;

using namespace std;
using namespace glm;
//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;

class Scene {
public:
	void generateSphere();
	Scene(RenderingEngine* renderer);
	virtual ~Scene();

	//Send geometry to the renderer
	void displayScene();
	std::vector<Geometry>& getObjects();
private:
	RenderingEngine* renderer;

	Geometry rectangle;

	//list of objects in the scene
	std::vector<Geometry> objects;
	glm::mat4 M;
	glm::mat4 V;
	glm::mat4 P;
};

#endif /* SCENE_H_ */
