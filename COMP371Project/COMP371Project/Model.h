#pragma once
#include <glm\glm.hpp>
#include <vector>
#include <string>
#include <iostream>

class Model
{
public:
	std::string component;
	std::vector<glm::vec3> * vertices;
	std::vector<glm::vec2> * uvs;
	std::vector<glm::vec3> * normals;

	std::vector<glm::ivec3> * face_vn;
	std::vector<glm::ivec3> * face_v;
	std::vector<glm::ivec3> * face_vt;

	int tri_count;

	int offset_v;
	int offset_vt;
	int offset_vn;

	float * v;
	float * vt;
	float * vn;

	Model();
	~Model();

	void PostProcess();

};

