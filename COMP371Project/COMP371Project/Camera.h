#pragma once
#include <glm\glm.hpp>
class Camera
{
public:

	glm::vec3 position;
	glm::vec3 direction;
	/*
	GLfloat posX;
	GLfloat posY;
	GLfloat posZ;

	GLfloat lookX;
	GLfloat lookY;
	GLfloat lookZ;
	

	Gldouble rotX;
	Gldouble rotY;
	Gldouble rotZ;
	*/

	Camera();
	void LookAt();

	~Camera();
};

