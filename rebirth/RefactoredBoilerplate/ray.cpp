#include <iostream>
#include "ray.h"

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>


glm::vec3 color(const ray& r) {
	glm::vec3 unit_direction = glm::normalize(r.direction());
	float t = 0.5* (unit_direction.y + 1.0);
	return (1.0 - t )* glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1.0);
}
