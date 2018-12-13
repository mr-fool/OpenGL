#include "ArcballCamera.h"

#include <algorithm>
#include <GLM/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <iostream>

ArcballCamera ArcballCam;

ArcballCamera::ArcballCamera()
{
	cur_mpos = last_mpos = glm::vec2(0, 0);
	std::cout << "cur x and y" << cur_mpos.x << " " << cur_mpos.y << std::endl;
}


ArcballCamera::~ArcballCamera()
{
}

glm::vec3 ArcballCamera::get_vector(glm::vec2 mpos, float screen_wid, float screen_hei)
{
	float midW = screen_wid / 2.0f;
	float midH = screen_hei / 2.0f;

	glm::vec3 ret( (mpos.x / midW) - 1.0f, (mpos.y / midH) - 1.0f, 0.0f);
	ret.y = -ret.y;
	float pow = (ret.x * ret.x) + (ret.y * ret.y);
	if (pow <= 1.0f)
	{
		ret.z = sqrt(1.0f - pow);		
	}	
	glm::normalize(ret);	

	return ret;
}

void ArcballCamera::get_rotation_matrix(glm::mat4& Model, glm::mat4& View, float screen_wid, float screen_hei)
{
	if (cur_mpos.x != last_mpos.x || cur_mpos.y != last_mpos.y)
	{
		glm::vec3 v1 = get_vector(cur_mpos, screen_wid, screen_hei);
		glm::vec3 v2 = get_vector(last_mpos, screen_wid, screen_hei);
		float angle = acos(std::min(1.0f, glm::dot(v1, v2)));
		angle *= 0.03f;


		glm::vec3 axis_in_camera = glm::cross(v1, v2);
		glm::mat3 inv_matrix = glm::inverse(glm::mat3(View) * glm::mat3(Model));		
		glm::vec3 axis_in_model = inv_matrix * axis_in_camera;

		Model = glm::rotate(Model, glm::degrees(angle), axis_in_model);

		cur_mpos = last_mpos;
	}	
}

