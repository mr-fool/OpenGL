//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
class ray {
public:
	glm::vec3 ray_origin;
	glm::vec3 ray_direction;

	ray() {}
	ray(const glm::vec3& a, const glm::vec3 &b) {
		ray_origin = a;
		ray_direction = b;
	}
	glm::vec3 origin() const {
		return ray_origin;
	}
	glm::vec3 direction() const {
		return ray_direction;
	}
	glm::vec3 point_at_parameter(float t) const {
		return ray_origin + t * ray_direction;
	}
	glm::vec3 color(const ray& r);
};
