#pragma once
#include "World.h"
#include "Constants.h"
class WorldEngine
{
public:
	WorldEngine();
	~WorldEngine();

	void BuildWorld();
	World * Update();

	//given userInput
	void GivenUserInput(userInput);

private:
	World * world;
};

