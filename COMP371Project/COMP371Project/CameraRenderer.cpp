#include "CameraRenderer.h"


CameraRenderer::CameraRenderer()
{
}


CameraRenderer::~CameraRenderer()
{
}


void CameraRenderer::RenderCameraPOV(Camera * camera)
{
	
	gluLookAt(	camera->position.x, 
				camera->position.y, 
				camera->position.z, 
				camera->direction.x,
				camera->direction.y,
				camera->direction.z,
				0.0, 1.0, 0.0);
	//do the glulookat
}