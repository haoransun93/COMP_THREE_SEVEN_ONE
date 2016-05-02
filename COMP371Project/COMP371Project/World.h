#pragma once
#include "Camera.h"
#include "Constants.h"
class World
{
public:
	userInput prevInput;
	Camera * camera;

	World();
	~World();
};

