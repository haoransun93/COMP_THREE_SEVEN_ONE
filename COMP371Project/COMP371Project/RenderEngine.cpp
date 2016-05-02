#include "RenderEngine.h"
#include "Constants.h"
#include <glut.h>


RenderEngine::RenderEngine()
{
	this->worldRenderer = new WorldRenderer();
	this->cameraRenderer = new CameraRenderer();
}


RenderEngine::~RenderEngine()
{
	delete this->worldRenderer;
	delete this->cameraRenderer;
}

void RenderEngine::Init()
{
}

void RenderEngine::RenderScene(World * world)
{
	this->RenderScene_Init();

	this->cameraRenderer->RenderCameraPOV(world->camera); //set camera

	this->worldRenderer->RenderWorld(world);

	this->RenderScene_End();
}

void RenderEngine::RenderScene_Init()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderEngine::RenderScene_End()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)GLOBAL_WIDTH / GLOBAL_HEIGHT, 0.0, 100);

	glutSwapBuffers();
	glutPostRedisplay();
}

void RenderEngine::RenderScene_CameraLookAt()
{
}
void RenderEngine::RenderScene_SetViewPort()
{
	//does viewport change? need some constants
}
void RenderEngine::RenderScene_RenderGame(){}

