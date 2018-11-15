/*
 * Program.cpp
 *
 *  Created on: Sep 10, 2018
 *      Author: John Hall
 */

#include "Program.h"

#include <iostream>
#include <string>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
//#include "vld.h"

//Different Objects and Shapes
struct Ray {
	glm::vec3 origin;
	glm::vec3 direction;
};

struct Sphere {
	glm::vec3 center;
	float radius;
	glm::vec3 color;
	int material;   // 0 = phong, 1 = transparent, 2 = mirror
	float Kd;       // diffuse, refraction index, or
	float Ks;
	float n;
	float Ir;
};

struct Triangle {
	glm::vec3 p0;
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 color;
	int material;
	float Kd;
	float Ks;
	float n;
	float Ir;
};

struct Plane {
	glm::vec3 point;
	glm::vec3 normal;
	glm::vec3 color;
	int material;
	float Kd;
	float Ks;
	float n;
	float Ir;
};

//normalizing
float norm(glm::vec3 a) {
	return (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
}
glm::vec3 normalize(glm::vec3 a) {
	float n = norm(a);
	if (n > 0) {
		float w = 1 / sqrt(n);
		a.x *= w;
		a.y *= w;
		a.z *= w;
	}
	return a;
}
float findMagnitude(glm::vec3 v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

glm::vec3 crossProduct(glm::vec3 a, glm::vec3 b) {
	return glm::vec3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

float dotProduct(glm::vec3 a, glm::vec3 b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float findDiscriminant(float a, float b, float c) {
	return pow(b, 2) - a * c;
}

void Program::generateRay(int width, int height) {
	Ray ray;
	float mag = findMagnitude(ray.direction);
	ray.direction.x /= mag;
	ray.direction.y /= mag;
	ray.direction.z /= mag;
	std::cout << "generate ray is being called";
}
//testing normalization
glm::vec3 testing = glm::vec3(0,2.5,-7.75);
glm::vec3 normalizeValue = normalize(testing);

/*
Not exactly sure how to implementing it yet
class Ray {
public:
	vec3 origin;
	vec3 direction;
	Ray(vec3 o, vec3 d): origin(o), direction(d){}
	void normalize() {
		float mag = findMagnitude(direction);
		direction.x /= mag;
		direction.y /= mag;
		direction.z /= mag;
	}
};
class Light {
public:
	vec3 position;
	float intensity;
	Light(vec3 p, float i): position(p), intensity(i) {}
};

class Shape {
public:
	vec3 colour;
	vec3 specColour;
	Shape(vec3 c, vec3 spc): colour(c), specColour(spc) {}
	virtual float intersect(Ray r, float min) = 0;
	virtual vec3 getNormal(vec3 point) = 0;
	virtual ~Shape() {}
};
class Sphere: public Shape {
public:
	vec3 center;
	float radius;
	Sphere(vec3 c, float r, vec3 co, vec3 spc): Shape(co, spc), center(c), radius(r) {}
	float intersect(Ray r, float min) {
		vec3 originToCenter = r.origin - center;

		float a = dotProduct(r.direction, r.direction);
		float b = dotProduct(r.direction, originToCenter);
		float c = dotProduct(originToCenter, originToCenter) - pow(radius, 2);

		float discriminant = findDiscriminant(a, b, c);
		if (discriminant < 0) {
			return INFINITY;
		}

		float t;
		float t0 = (-b + sqrt(discriminant)) /  a;
		float t1 = (-b - sqrt(discriminant)) / a;

		(t0 < t1) ? t = t0 : t = t1;
		if (t < min) {
			return INFINITY;
		}

		return t;
	}

	vec3 getNormal(vec3 point) {
		return point - center;
	}
};

class Plane: public Shape {
public:
	vec3 normal;
	vec3 pointQ;
	Plane(vec3 n, vec3 q, vec3 co, vec3 spc): Shape(co, spc), normal(n), pointQ(q) {}
	float intersect(Ray r, float min) {
		float bottom = dot(r.direction, normal);
		if (bottom == 0) {
			return INFINITY;
		}

		float t = dot(pointQ, normal) / bottom;
		if (t > min) {
			return t;
		}
		return INFINITY;
	}

	vec3 getNormal(vec3 point) {
		return normal;
	}
};

class Triangle: public Shape {
public:
	vec3 pointA;
	vec3 pointB;
	vec3 pointC;
	Triangle(vec3 a, vec3 b, vec3 c, vec3 co, vec3 spc):
		Shape(co, spc), pointA(a), pointB(b), pointC(c) {}
	float intersect(Ray r, float min) {
		vec3 ve = r.origin;
		vec3 vd = r.direction;
		vec3 pa = pointA;
		vec3 pb = pointB;
		vec3 pc = pointC;

		float a = pa.x - pb.x;
		float b = pa.y - pb.y;
		float c = pa.z - pb.z;
		float d = pa.x - pc.x;
		float e = pa.y - pc.y;
		float f = pa.z - pc.z;
		float g = vd.x;
		float h = vd.y;
		float i = vd.z;
		float j = pa.x - ve.x;
		float k = pa.y - ve.y;
		float l = pa.z - ve.z;

		float M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);

		float t = -(f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / M;
		float u = (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / M;
		float v = (j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g)) / M;

		if (t < min || u < 0 || u > 1 || v < 0 || (u + v) > 1) {
			return INFINITY;
		}

		return t;
	}

	vec3 getNormal(vec3 point) {
		vec3 vab = pointB - pointA;
		vec3 vac = pointC - pointA;
		return crossProduct(vab, vac);
	}
};
*/
Program::Program() {
        setupWindow();
}

Program::~Program() {
  
}

void Program::start() {
	image.Initialize();
	for (unsigned int i = 0; i < image.Width(); i++) {
		for (unsigned int j = 0; j < image.Height(); j++) {
			//set pixel colors here
			image.SetPixel(i, j, glm::vec3(1.0, 1.0, 1.0));
		}
	}
	generateRay(1, 2);
	/*Need some kind for loop and some functions like 
	vec3 getPixelColour(Ray r, vector<Shape*> shapes, Light light, int count) {
    vec3 kd;
    vec3 ks;
    vec3 normal;
    vec3 incidentPoint;

    float I = light.intensity;
    float Ia = 0.5;
    float closert = INFINITY;

    for(int i = 0; i < shapes.size(); i++){
        float t = shapes.at(i)->intersect(r, 0);
        if(t < closert){
            closert = t;
            incidentPoint = closert * r.direction;
            kd = shapes.at(i)->colour;
            ks = shapes.at(i)->specColour;
            normal = shapes.at(i)->getNormal(incidentPoint);
        }
    }

    vec3 l = light.position - incidentPoint;

    l /= findMagnitude(l);
    vec3 v = -incidentPoint / findMagnitude(incidentPoint);
    normal /= findMagnitude(normal);

    vec3 h = (v + l) / findMagnitude(v + l);
    vec3 ka = kd;

    vec3 L = ka * Ia + kd * I * max(0, dot(normal, l)) + ks * I * max(0, pow(dot(normal, h), 100));

    Ray shadowRay = Ray(incidentPoint, l);
    shadowRay.normalize();
    for (int i = 0; i < shapes.size(); i++) {
        vec3 intersectP = shapes.at(i)->intersect(shadowRay, 0.0001f) * shadowRay.direction;
        if (findMagnitude(intersectP) < findMagnitude(light.position - shadowRay.origin)) {
            L = ka * Ia;
        }
    }

    vec3 rhs = 2 * dot(r.direction, normal) *  normal;
    Ray reflectedRay = Ray(incidentPoint, r.direction - rhs);
    reflectedRay.origin += 0.0001f * reflectedRay.direction;
    reflectedRay.normalize();

    if (findMagnitude(ks) > 0 && count < 10) {
        vec3 ref = getPixelColour(reflectedRay, shapes, light, ++count);
        L = L + ks * ref;
    }

    return L;
}

void generateRays(vector<vec2>* pts, vector<vec3>* colours, vector<Shape*> s, Light l, int w, int h, float f) {
    pts->clear();
    colours-> clear();

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            float x = -w / 2 + i + 0.5;
            float y = h / 2 - j + 0.5;
            float z = -f;

            Ray r = Ray(vec3(0, 0, 0), vec3(x, y, z));
            r.normalize();

            vec3 colour = getPixelColour(r, s, l, 0);

            pts->push_back(vec2(x/(w/2), y/(h/2)));
            colours->push_back(colour);
        }
    }
}*/
	std::cout << "normalize value " + glm::to_string(normalizeValue) << std::endl;

	

	//Main render loop
	while(!glfwWindowShouldClose(window)) {
	        image.Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

void Program::setupWindow() {
	//Initialize the GLFW windowing system
	if (!glfwInit()) {
		std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
		return;
	}

	//Set the custom error callback function
	//Errors will be printed to the console
	glfwSetErrorCallback(ErrorCallback);

	//Attempt to create a window with an OpenGL 4.1 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 1024;
	int height = 1024;
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}

	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);

	//Bring the new window to the foreground (not strictly necessary but convenient)
	glfwMakeContextCurrent(window);

	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
	if (!gladLoadGL()) {
		std::cout << "GLAD init failed" << std::endl;
		return;
	}

	//Query and print out information about our OpenGL environment
	QueryGLVersion();
}



void Program::QueryGLVersion() {
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

	std::cout << "OpenGL [ " << version << " ] "
		<< "with GLSL [ " << glslver << " ] "
		<< "on renderer [ " << renderer << " ]" << std::endl;
}

void ErrorCallback(int error, const char* description) {
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		std::cout << "Key 1 is pressed" << std::endl;
	}
}
