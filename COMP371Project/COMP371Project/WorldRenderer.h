#pragma once
#include "glew.h"

#include "World.h"
#include "ModelLoader.h"

#include "glut.h"

class WorldRenderer
{
public:

	ModelLoader * modelLoader;

	WorldRenderer();
	~WorldRenderer();

	void RenderWorld(World *);
	void RenderModel(int v_count, float * arr);
	void drawSquare();

};

