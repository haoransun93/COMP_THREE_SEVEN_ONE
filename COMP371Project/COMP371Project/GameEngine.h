#pragma once

#include "MapEngine.h"
#include "RenderEngine.h"
#include "WorldEngine.h"
#include "Constants.h"
class GameEngine
{

private:
	MapEngine * mapEngine;
	RenderEngine * renderEngine;
	WorldEngine * worldEngine;
public:
	GameEngine();

	//setup
	void Start();
	void MainLoop();

	//pass userinput
	void GivenUserInput(userInput input);

	~GameEngine();
};

