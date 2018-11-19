#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

class Sphere {
public:
	glm::vec3 center; /// position of the sphere
	float radius, radius2; /// sphere radius and radius^2
	glm::vec3 surfaceColor, emissionColor; /// surface color and emission (light)
	float transparency, reflection; /// surface transparency and reflectivity
	Sphere(
		const glm::vec3 &c,
		const float &r,
		const glm::vec3 &sc,
		const float &refl = 0,
		const float &transp = 0,
		const glm::vec3 &ec = 0) :
		center(c), radius(r), radius2(r * r), surfaceColor(sc), emissionColor(ec),
		transparency(transp), reflection(refl)
	}
bool intersect(const glm::vec3 &rayorig, const glm::vec3 &raydir, float &t0, float &t1) const
{
	glm::vec3 l = center - rayorig;
	float tca = l.glm::dot(raydir);
	if (tca < 0) return false;
	float d2 = l.dot(l) - tca * tca;
	if (d2 > radius2) return false;
	float thc = sqrt(radius2 - d2);
	t0 = tca - thc;
	t1 = tca + thc;

	return true;
}
};
