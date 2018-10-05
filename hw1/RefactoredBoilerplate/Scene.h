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
	Geometry* createSquare(double side_length);
	Geometry* createDiamond(double side_length);

	void diamondAndSquare(int level, std::vector<Geometry> &objects);
	void createSpiral(int level, std::vector<Geometry> &objects);

	void iterationUp();
	void iterationDown();
	std::vector<Geometry>& getObjects();
	void createTriangle(int level, glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC, glm::vec3 color);
	void sierpinjski(int level, std::vector<Geometry> &objects);

	void createTriangleReloaded(int reloadLevel, glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC, glm::vec3 color);
	void sierpinjskiReloaded(int reloadLevel, std::vector<Geometry> &objects);
private:
	RenderingEngine * renderer;
	int scene, level, reloadLevel;
	//list of objects in the scene
	std::vector<Geometry> objects;
};

#endif /* SCENE_H_ */