#ifndef PARSEFILE_H
#define PARSEFILE_H
#include <fstream>
#include "Program.h"
#include <iostream>
enum Token {
    Number,
    OpenBracket,
    CloseBracket,
    LightT,
    SphereT,
    TriangleT,
    PlaneT,
    TheEnd,
    Color,
    Reflect,
    Gaussian,
    Metallic,
    Specular
};

static glm::vec3 color2color(glm::vec3 c) {
    c.x = c.x/255.0f;
    c.y = c.y/255.0f;
    c.z = c.z/255.0f;
    c.x = pow(c.x, 1/2.2f);
    c.y = pow(c.y, 1/2.2f);
    c.z = pow(c.z, 1/2.2f);
    return c;
}

class Tokenizer {
public:
    Tokenizer(std::fstream &file) {
        f = std::move(file);
    }

    Token getNextToken() {
        std::string s;
skip:
        int c;
        c = f.get();
        while ((c != EOF) && (c != ' ') && (c != '\n')) {
            s.push_back(c);
            c = f.get();
        }
        if (c == EOF)
            return TheEnd;
        if (s[0] == '#') {
            if (c == '\n')
                s = "";
            goto skip;
        }
        if (s == "") {
            goto skip;
        }
        if(s == " ")
            goto skip;
        if (s == "{")
            return OpenBracket;
        if (s == "}")
            return CloseBracket;
        if (s == "light")
            return LightT;
        if (s == "sphere")
            return SphereT;
        if (s == "triangle")
            return TriangleT;
        if (s == "plane")
            return PlaneT;
        if (s == "reflect")
            return Reflect;
        if (s == "color")
            return Color;
        if (s == "gaussian")
            return Gaussian;
        if (s == "metallic")
            return Metallic;
        if (s == "specular")
            return Specular;
        bool isnum = true;
        for (char c : s) {
            if ((c != '-') && (c != '.') && (!isdigit(c)))
                isnum = false;
        }
        if (!isnum) {
            return (Token)-1;
        }
        v = stof(s);
        return Number;
    }

    float getValue() {
        return v;
    }

private:
    float v;
    std::fstream f;

};

class Parser {
public:
    Parser(Tokenizer &tok) : t(tok) {}

    void ParseFiles(std::vector<struct Triangle> &tris, std::vector<Light> &lights, std::vector<Sphere> &spheres, std::vector<Plane> &planes) {
        Token tok = t.getNextToken();
        while (tok != TheEnd) {
            if (tok == TriangleT) {
                tok = t.getNextToken();
                glm::vec3 p0;
                glm::vec3 p1;
                glm::vec3 p2;
                tok = t.getNextToken();
                p0.x = t.getValue();
                tok = t.getNextToken();
                p0.y = t.getValue();
                tok = t.getNextToken();
                p0.z = t.getValue();
                tok = t.getNextToken();
                p1.x = t.getValue();
                tok = t.getNextToken();
                p1.y = t.getValue();
                tok = t.getNextToken();
                p1.z = t.getValue();
                tok = t.getNextToken();
                p2.x = t.getValue();
                tok = t.getNextToken();
                p2.y = t.getValue();
                tok = t.getNextToken();
                p2.z = t.getValue();
                struct Triangle t;
                tok = this->t.getNextToken();
                t.pointA = p0;
                t.pointB = p1;
                t.pointC = p2;
                t.color = glm::vec3(1.0f, 1.0f, 1.0f);
                t.reflective = 0.0f;
                t.gaussian = 0.0f;
                t.specular = 1.0f;
                t.metallic = false;
                while(tok == Color || tok == Reflect || tok == Gaussian || tok == Metallic || tok == Specular) {
                    switch(tok) {
                    case Reflect:
                        tok = this->t.getNextToken();
                        t.reflective = this->t.getValue();
                        tok = this->t.getNextToken();
                        break;
                    case Specular:
                        tok = this->t.getNextToken();
                        t.specular = this->t.getValue();
                        tok = this->t.getNextToken();
                        break;
                    case Color:
                        tok = this->t.getNextToken();
                        t.color.x = this->t.getValue();
                        tok = this->t.getNextToken();
                        t.color.y = this->t.getValue();
                        tok = this->t.getNextToken();
                        t.color.z = this->t.getValue();
                        tok = this->t.getNextToken();
                        t.color = color2color(t.color);
                        break;
                    case Gaussian:
                        tok = this->t.getNextToken();
                        t.gaussian = this->t.getValue();
                        tok = this->t.getNextToken();
                        break;
                    case Metallic:
                        t.metallic = true;
                        tok = this->t.getNextToken();
                        break;
                    }
                }
                tris.push_back(t);
                tok = this->t.getNextToken();
            }
            if (tok == LightT) {
                tok = t.getNextToken();
                glm::vec3 p0;
                tok = t.getNextToken();
                p0.x = t.getValue();
                tok = t.getNextToken();
                p0.y = t.getValue();
                tok = t.getNextToken();
                p0.z = t.getValue();
                tok = t.getNextToken();
                struct Light l;
                l.postion = p0;
                l.color = glm::vec3(1.0f, 1.0f, 1.0f);
                lights.push_back(l);
                tok = t.getNextToken();
            }
            if (tok == SphereT) {
                tok = t.getNextToken();
                glm::vec3 p0;
                float radius;
                tok = t.getNextToken();
                p0.x = t.getValue();
                tok = t.getNextToken();
                p0.y = t.getValue();
                tok = t.getNextToken();
                p0.z = t.getValue();
                tok = t.getNextToken();
                radius = t.getValue();
                tok = t.getNextToken();
                struct Sphere s;
                s.c = p0;
                s.colour = glm::vec3(1.0f, 1.0f, 1.0f);
                s.r = radius;
                s.reflective = 0.0f;
                s.gaussian = 0.0f;
                s.specular = 1.0f;
                s.metallic = false;
                while(tok == Color || tok == Reflect || tok == Gaussian || tok == Metallic || tok == Specular) {
                    switch(tok) {
                    case Reflect:
                        tok = this->t.getNextToken();
                        s.reflective = this->t.getValue();
                        tok = this->t.getNextToken();
                        break;
                    case Specular:
                        tok = this->t.getNextToken();
                        s.specular = this->t.getValue();
                        tok = this->t.getNextToken();
                        break;
                    case Color:
                        tok = this->t.getNextToken();
                        s.colour.x = this->t.getValue();
                        tok = this->t.getNextToken();
                        s.colour.y = this->t.getValue();
                        tok = this->t.getNextToken();
                        s.colour.z = this->t.getValue();
                        tok = this->t.getNextToken();
                        s.colour = color2color(s.colour);
                        break;
                    case Gaussian:
                        tok = this->t.getNextToken();
                        s.gaussian = t.getValue();
                        tok = this->t.getNextToken();
                        break;
                    case Metallic:
                        s.metallic = true;
                        tok = t.getNextToken();
                        break;
                    }
                }
                spheres.push_back(s);
                tok = t.getNextToken();
            }
            if (tok == PlaneT) {
                tok = t.getNextToken();
                glm::vec3 p0;
                glm::vec3 n;
                tok = t.getNextToken();
                n.x = t.getValue();
                tok = t.getNextToken();
                n.y = t.getValue();
                tok = t.getNextToken();
                n.z = t.getValue();
                tok = t.getNextToken();
                p0.x = t.getValue();
                tok = t.getNextToken();
                p0.y = t.getValue();
                tok = t.getNextToken();
                p0.z = t.getValue();
                tok = t.getNextToken();
                struct Plane p;
                p.color = glm::vec3(1.0f, 1.0f, 1.0f);
                p.point = p0;
                p.normal = n;
                p.reflective = 0.0f;
                p.gaussian = 0.0f;
                p.metallic = false;
                p.specular = 1.0f;
                while(tok == Color || tok == Reflect || tok == Gaussian || tok == Metallic || tok == Specular) {
                    switch(tok) {
                    case Reflect:
                        tok = this->t.getNextToken();
                        p.reflective = this->t.getValue();
                        tok = this->t.getNextToken();
                        break;
                    case Specular:
                        tok = this->t.getNextToken();
                        p.specular = this->t.getValue();
                        tok = this->t.getNextToken();
                        break;
                    case Color:
                        tok = this->t.getNextToken();
                        p.color.x = this->t.getValue();
                        tok = this->t.getNextToken();
                        p.color.y = this->t.getValue();
                        tok = this->t.getNextToken();
                        p.color.z = this->t.getValue();
                        tok = this->t.getNextToken();
                        p.color = color2color(p.color);
                        break;
                    case Gaussian:
                        tok = this->t.getNextToken();
                        p.gaussian = t.getValue();
                        tok = this->t.getNextToken();
                        break;
                    case Metallic:
                        p.metallic = true;
                        tok = t.getNextToken();
                        break;
                    }
                }
                planes.push_back(p);
                tok = t.getNextToken();
            }
        }
    }

private:
    Tokenizer &t;
};
#endif
