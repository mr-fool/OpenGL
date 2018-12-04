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
using namespace std;
using namespace glm;
//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;

class Scene {
public:
	Scene(RenderingEngine* renderer);
	virtual ~Scene();

	//Send geometry to the renderer
	void displayScene();
	std::vector<Geometry>& getObjects();
	void generateSphere(vector<vec3>& positions, vector<vec3>& normals, vector<vec2>& uvs, vector<unsigned int>& indices, vec3 center, float radius, int divisions);
private:
	RenderingEngine* renderer;

	Geometry rectangle;

	//list of objects in the scene
	std::vector<Geometry> objects;
};

#endif /* SCENE_H_ */