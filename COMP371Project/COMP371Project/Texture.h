#pragma once
#include <glut.h>

#include <glm\glm.hpp>
#include <string>
class Texture
{
public:
	std::string name;

	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
	glm::vec3 Ni;
	glm::vec4 Ns_Ni_d;
	int illuml;
	GLuint id;

	Texture();
	~Texture();
};

