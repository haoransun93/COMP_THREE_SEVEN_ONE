#pragma once
#include "Camera.h"
#include "glut.h"
class CameraRenderer
{
public:

	CameraRenderer();

	void RenderCameraPOV(Camera *);

	~CameraRenderer();
};

