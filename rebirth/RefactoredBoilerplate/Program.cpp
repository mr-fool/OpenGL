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
#include <glm/gtx/intersect.hpp>
#include "ray.h"
#include "parseFile.h"
#include <algorithm>
//#include "sphere.cpp"

//#include "vld.h"
/*Tirangle
u = v1-v0, v = v2-v0, r(t) = r.o + t * r.d,
Let h = (a,b,t0)^T, M = [ u, v, -d], then:
h = inverse(M) * r.o
intersection with triangle plane: r(t0)
Check whether it is valid: t>0
Check whether inside tri: 0<a, 0<b, a+b<1
the columns of m are made of u, v, -r.d

*/

//float focalLen = 470.0f;

glm::vec3 Program::rayColor(const ray& r) {
    glm::vec3 unit_direction = glm::normalize(r.direction());
    float t = 0.5* (unit_direction.y + 1.0);
    return (1.0 - t)* glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1.0);

}

bool hit_sphere(const glm::vec3& center, float radius, const ray& r, float *t) {
    glm::vec3 rayToCenter = center - r.origin();

    /* calculate coefficients a, b, c from quadratic equation */

    /* float a = dot(ray->dir, ray->dir); // ray direction is normalised, dotproduct simplifies to 1 */
    float b = glm::dot(rayToCenter, r.direction());
    float c = glm::dot(rayToCenter, rayToCenter) - radius*radius;
    float disc = b * b - c; /* discriminant of quadratic formula */

    /* solve for t (distance to hitpoint along ray) */

    if (disc < 0.0f) return false;
    else *t = b - sqrt(disc);

    if (*t < 0.0f){
        *t = b + sqrt(disc);
        if (*t < 0.0f) return false;
    }

    else return true;
}

bool hit_plane(const glm::vec3& p0, glm::vec3 n, const ray& r, float *t) {
    // assuming vectors are all normalized
    if(glm::intersectRayPlane(r.origin(), r.direction(), p0, n, *t)) {
        return true;
    }

    return false;
}

bool hit_triangle(const Triangle tri, const ray& r, float *t) {
    glm::vec3 pt0 = tri.pointA;
    glm::vec3 ut = tri.pointB - tri.pointA;
    glm::vec3 vt = tri.pointC - tri.pointA;
    const float eps = 0.0001f;
    glm::vec3 h = glm::cross(r.direction(), vt);
    const float a = glm::dot(ut, h);
    if(a > -eps && a < eps) {
        return false;
    }
    const float f = 1.0f / a;
    glm::vec3 s = r.origin() - pt0;
    const float u = f * glm::dot(s, h);
    if(u < 0.0f || u > 1.0f) {
        return false;
    }
    glm::vec3 q = glm::cross(s, ut);
    const float v = f * glm::dot(r.direction(), q);
    if(v < 0.0f || u+v > 1.0f) {
        return false;
    }
    const float ts = f * glm::dot(vt, q);
    if(ts < eps) {
        return false;
    }
    *t = ts;
    return true;
}


struct result {
    float t;
    bool hit;
    glm::vec3 normal;
    glm::vec3 color;
    float reflective;
    float gaussian;
    bool metallic;
    float specular;
};

result intersect(Scene s, ray r) {
    result res;
    res.t = INFINITY;
    res.hit = false;
    for(size_t i = 0; i < s.tris->size(); i++) {
        float cur_t;
        if(hit_triangle((*s.tris)[i], r, &cur_t)) {
            if(cur_t < res.t) {
                Triangle tri = (*s.tris)[i];
                res.color =(*s.tris)[i].color;
                res.t = cur_t;
                res.hit = true;
                res.reflective = (*s.tris)[i].reflective;
                res.gaussian = (*s.tris)[i].gaussian;
                res.metallic = (*s.tris)[i].metallic;
                res.specular = (*s.tris)[i].specular;
                glm::vec3 ut = tri.pointB - tri.pointA;
                glm::vec3 vt = tri.pointC - tri.pointA;
                res.normal = glm::normalize(glm::cross(ut,vt));
            }
        }
    }
    for(size_t i = 0; i < s.planes->size(); i++) {
        float cur_t;
        if(hit_plane((*s.planes)[i].point, (*s.planes)[i].normal, r, &cur_t)){
            if(cur_t < res.t) {
                res.color = (*s.planes)[i].color;
                res.t = cur_t;
                res.hit = true;
                res.specular = (*s.planes)[i].specular;
                res.gaussian = (*s.planes)[i].gaussian;
                res.reflective = (*s.planes)[i].reflective;
                res.metallic = (*s.planes)[i].metallic;
                res.normal = (*s.planes)[i].normal;
            }
        }
    }
    for(size_t i = 0; i < s.spheres->size(); i++) {
        float cur_t;
        if(hit_sphere((*s.spheres)[i].c, (*s.spheres)[i].r, r, &cur_t)) {
            if(cur_t < res.t){
                res.color = (*s.spheres)[i].colour;
                res.t = cur_t;
                res.hit = true;
                res.specular = (*s.spheres)[i].specular;
                res.reflective = (*s.spheres)[i].reflective;
                res.gaussian = (*s.spheres)[i].gaussian;
                res.metallic = (*s.spheres)[i].metallic;
                res.normal = glm::normalize(r.point_at_parameter(res.t) - (*s.spheres)[i].c);
            }
        }
    }
    return res;
}

float clip(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}


glm::vec3 shadeRay(result res, ray r, Scene s, int depth) {
    glm::vec3 col(0,0,0);
    if(depth > 3){
        return glm::vec3(0.0f, 0.0f, 0.0f);
    }
    if(res.hit) {
        glm::vec3 hp = r.origin() + res.t*r.direction();
        if(res.reflective > 0.0f) {
            ray ref(hp + res.normal*0.001f, r.direction() - 2*res.normal*glm::dot(r.direction(), res.normal));
            result rref = intersect(s, ref);
            if(rref.hit) {
                glm::vec3 c = shadeRay(rref, ref, s, depth+1);
                col += res.reflective * c;
            }
        }
        for(size_t i = 0; i < (*s.lights).size(); i++) {
            if(glm::dot(res.normal, -r.direction()) < 0) {
                res.normal = -res.normal;
            }
            glm::vec3 lightdir = glm::normalize((*s.lights)[i].postion - hp);
            ray lr(hp + res.normal*0.001f, lightdir);
            result resl = intersect(s, lr);
            float dist = glm::distance(hp, hp + lr.direction()*resl.t) - glm::distance(hp, (*s.lights)[0].postion);
            if(!resl.hit)
                dist = 1.0f;
            glm::vec3 halfangle = glm::normalize(lightdir - r.direction());
            float ahalf = acos(glm::dot(halfangle, res.normal));
            float expn = ahalf / res.gaussian;
            expn = -(expn * expn);
            float gauss = exp(expn);
            col += res.specular * gauss * ((res.metallic) ? res.color : (*s.lights)[i].color);
            col += (1-res.reflective) * res.color * clip(glm::dot(lightdir, res.normal) * (dist > 0.0f), 0.1, 1.0);
        }
    }
    return col;
}

void Program::generateRay(int width, int height, glm::vec3 lookat, glm::vec3 up, glm::vec3 origin, float fov, Scene s) {
    glm::vec3 right = -glm::normalize(glm::cross(up, lookat));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            float u = 2*((float(i) / float(width)) - 0.5) * tan(fov / 2 * M_PI / 180);
            float v = 2*((float(j) / float(height)) - 0.5) * tan(fov / 2 * M_PI / 180);
            ray r = ray(origin, glm::normalize((u * right) + (v * up) + lookat));
            glm::vec3 col = rayColor(r);
            result res = intersect(s, r);
            col = shadeRay(res, r, s, 0);
            //            if(res.hit) {
            //                glm::vec3 hp = r.origin() + res.t*r.direction();
            //                for(size_t i = 0; i < (*s.lights).size(); i++) {
            //                    if(glm::dot(res.normal, -r.direction()) < 0) {
            //                        res.normal = -res.normal;
            //                    }
            //                    glm::vec3 lightdir = glm::normalize((*s.lights)[i].postion - hp);
            //                    ray lr(hp + res.normal*0.001f, lightdir);
            //                    result resl = intersect(s, lr);
            //                    float dist = glm::distance(hp, hp + lr.direction()*resl.t) - glm::distance(hp, (*s.lights)[0].postion);
            //                    if(!resl.hit)
            //                        dist = 1.0f;
            //                    col = res.color * clip(glm::dot(lightdir, res.normal) * (dist > 0.0f), 0.05, 1.0);
            //                }
            //            }

            col.x = pow(col.x, 1 / 2.2f);
            col.y = pow(col.y, 1 / 2.2f);
            col.z = pow(col.z, 1 / 2.2f);
            image.SetPixel(i, j, col);
        }
    }
}

//glm::vec3 sphereColor(const ray& r) {
//    /*glm::vec3 horizontal = glm::vec3(4, 0, 0);
//    glm::vec3 vertical = glm::vec3(0, 2, 0);
//    glm::vec3 lower_left_corner = glm::vec3(-2, -1, -1);
//    glm::vec3 origin = glm::vec3(0, 0, 0);*/
//    //ray r(origin, lower_left_corner + u * horizontal + v * vertical);
//    if (hit_sphere(glm::vec3(0, 0, -1), 0.5, r)) {
//        return glm::vec3(1, 0, 0);
//    }
//    std::cout << "The r.direction is " + glm::to_string( r.direction() ) << std::endl;
//    glm::vec3 unit_direction = glm::normalize(r.direction());
//    float t = 0.5 * (unit_direction.y + 1.0);
//    glm::vec3 result = (1 - t) * glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1.0);
//    std::cout << "The result is " + glm::to_string(result) << std::endl;
//    return (1 - t) * glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1.0);
//}

Program::Program() {
    setupWindow();
}

Program::~Program() {

}

void Program::start() {
    image.Initialize();
    std::cout << "image width is " + std::to_string( image.Width() )<< std::endl;
    std::cout << "image height is " + std::to_string( image.Height() )<< std::endl;
    for (unsigned int i = 0; i < image.Width(); i++) {
        for (unsigned int j = 0; j < image.Height(); j++) {
            //set pixel colors here
            image.SetPixel(i, j, glm::vec3(1.0, 1.0, 1.0));
        }
    }

    std::fstream f;
    std::string sceneselect = "scene2.txt";
    f.open(sceneselect, std::fstream::in);
    Tokenizer t(f);
    Parser p(t);
    std::vector<Triangle> tris;
    std::vector<Light> lights;
    std::vector<Plane> planes;
    std::vector<Sphere> spheres;
    p.ParseFiles(tris, lights, spheres, planes);
    Scene s;
    s.lights = &lights;
    s.planes = &planes;
    s.tris = &tris;
    s.spheres = &spheres;
    if(sceneselect == "scene1.txt") {
        glm::vec3 origin(0,0,-0.75);
        glm::vec3 lookat = origin + glm::vec3(0,0,-1);
        glm::vec3 gup(0,1,0);
        glm::vec3 right = glm::normalize(glm::cross(gup, lookat));
        glm::vec3 up = glm::normalize(glm::cross(lookat, right));
        generateRay(1024, 1024, lookat, up, origin, 90,  s);
    } else {
        glm::vec3 origin(0,0,-0.7);
        glm::vec3 lookat = origin + glm::vec3(0,0,-1);
        glm::vec3 gup(0,1,0);
        glm::vec3 right = glm::normalize(glm::cross(gup, lookat));
        glm::vec3 up = glm::normalize(glm::cross(lookat, right));
        generateRay(1024, 1024, lookat, up, origin, 90, s);
    }
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
    window = glfwCreateWindow(width, height, "HW4", 0, 0);
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
