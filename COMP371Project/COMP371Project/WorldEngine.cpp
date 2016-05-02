#include "WorldEngine.h"


WorldEngine::WorldEngine()
{
	this->BuildWorld(); // build the world;
}


WorldEngine::~WorldEngine()
{
}

void WorldEngine::BuildWorld()
{
	this->world = new World();
	//update whatever, etc;
}

World * WorldEngine::Update()
{
	if (&this->world->prevInput)
	{
		float moveX = ((GLOBAL_WIDTH / 2) - this->world->prevInput.mouseX) / 300;
		float moveY = ((GLOBAL_HEIGHT / 2) - this->world->prevInput.mouseY) / 300;

		rotate_pitch(moveX, &this->world->camera->direction);
		rotate_yaw(moveY, &this->world->camera->direction);
	}
	//update the camera
	this->world->camera->LookAt();
	//update the player
	//update player actions, etc
	//update everything else;

	return this->world;
}

void WorldEngine::GivenUserInput(userInput input)
{
	this->world->prevInput = input;
}