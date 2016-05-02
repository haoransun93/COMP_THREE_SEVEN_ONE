#pragma once
#include "World.h"
#include "Camera.h"
#include "WorldRenderer.h"
#include "CameraRenderer.h"

class RenderEngine
{
public:
	CameraRenderer * cameraRenderer;
	WorldRenderer * worldRenderer;

	RenderEngine();
	~RenderEngine();

	void Init();
	void RenderScene(World *);

private:
	//inside a renderScene, you will need:
	void RenderScene_Init();
	void RenderScene_CameraLookAt();
	void RenderScene_SetViewPort();
	void RenderScene_RenderGame();
	void RenderScene_End();
};

