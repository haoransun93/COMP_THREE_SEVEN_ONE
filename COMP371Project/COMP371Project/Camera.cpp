#include "Camera.h"


Camera::Camera()
{
	this->direction.x = 1;
	this->direction.y = 0;
	this->direction.z = 0;

	this->position.x = 0;
	this->position.y = 0;
	this->position.z = 0;
}


Camera::~Camera()
{
}

//change the location of the camera ONLY;
void Camera::LookAt()
{
}
