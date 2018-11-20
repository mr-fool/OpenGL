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
	TheEnd
};
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
		bool isnum = true;
		for (char c : s) {
			if ((c != '.') && (!isdigit(c)))
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
		Token tok;
		while ((tok = t.getNextToken()) != TheEnd) {
			if (tok == TriangleT) {
				t.getNextToken();
				glm::vec3 p0;
				glm::vec3 p1;
				glm::vec3 p2;
				t.getNextToken();
				p0.x = t.getValue();
				t.getNextToken();
				p0.y = t.getValue();
				t.getNextToken();
				p0.z = t.getValue();
				t.getNextToken();
				p1.x = t.getValue();
				t.getNextToken();
				p1.y = t.getValue();
				t.getNextToken();
				p1.z = t.getValue();
				t.getNextToken();
				p2.x = t.getValue();
				t.getNextToken();
				p2.y = t.getValue();
				t.getNextToken();
				p2.z = t.getValue();
				struct Triangle t;
				this->t.getNextToken();
				t.pointA = p0;
				t.pointB = p1;
				t.pointC = p2;
				t.color = glm::vec3(1.0f, 1.0f, 1.0f);
				tris.push_back(t);
				this->t.getNextToken();
			}
			if (tok == LightT) {
				t.getNextToken();
				glm::vec3 p0;
				t.getNextToken();
				p0.x = t.getValue();
				t.getNextToken();
				p0.y = t.getValue();
				t.getNextToken();
				p0.z = t.getValue();
				t.getNextToken();
				struct Light l;
				l.postion = p0;
				l.color = glm::vec3(1.0f, 1.0f, 1.0f);
				lights.push_back(l);
				t.getNextToken();
			}
			if (tok == SphereT) {
				t.getNextToken();
				glm::vec3 p0;
				float radius;
				t.getNextToken();
				p0.x = t.getValue();
				t.getNextToken();
				p0.y = t.getValue();
				t.getNextToken();
				p0.z = t.getValue();
				t.getNextToken();
				radius = t.getValue();
				t.getNextToken();
				struct Sphere s;
				s.c = p0;
				s.colour = glm::vec3(0.0f, 0.0f, 0.0f);
				s.r = radius;
				spheres.push_back(s);
				t.getNextToken();
			}
			if (tok == PlaneT) {
				t.getNextToken();
				glm::vec3 p0;
				glm::vec3 n;
				float radius;
				t.getNextToken();
				n.x = t.getValue();
				t.getNextToken();
				n.y = t.getValue();
				t.getNextToken();
				n.z = t.getValue();
				t.getNextToken();
				p0.x = t.getValue();
				t.getNextToken();
				p0.y = t.getValue();
				t.getNextToken();
				p0.z = t.getValue();
				t.getNextToken();
				struct Plane p;
				p.color = glm::vec3(1.0f, 1.0f, 1.0f);
				p.point = p0;
				p.normal = n;
				planes.push_back(p);
				t.getNextToken();
			}
		}
	}

private:
	Tokenizer &t;
};
