#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

using namespace glm;

class Camera {
public:
	vec3 direction;
	vec3 up;
	vec3 right;
	vec3 pos;
	vec3 polarPos;
	vec3 lookingAt;
	float zoomLimit;

	Camera();
	Camera(vec3 _polarPos, vec3 _lookingAt, float _zoomLimit);

	void pol2cart();
	mat4 getMatrix();

	void translateCamera(float up, float around, float theOtherOne);

};
#endif /* CAMERA_H */