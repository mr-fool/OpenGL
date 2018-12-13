#pragma once
#include <glm/glm.hpp>

extern class ArcballCamera
{
public:
	ArcballCamera();
	~ArcballCamera();
		
	glm::vec3 get_vector(glm::vec2 mpos, float screen_wid, float screen_hei);
	void get_rotation_matrix(glm::mat4& Model, glm::mat4& View, float screen_wid, float screen_hei);

	bool active;
	glm::vec2 cur_mpos;
	glm::vec2 last_mpos;

} ArcballCam;

