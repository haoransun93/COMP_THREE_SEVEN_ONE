#include "GameEngine.h"


GameEngine::GameEngine()
{
	mapEngine = new MapEngine();
	renderEngine = new RenderEngine();
	worldEngine = new WorldEngine();
}


GameEngine::~GameEngine()
{
	delete mapEngine;
	delete renderEngine;
	delete worldEngine;
}

void GameEngine::Start()
{
}

void GameEngine::MainLoop()
{
	World * world = this->worldEngine->Update();
	this->renderEngine->RenderScene(world);
}

void GameEngine::GivenUserInput(userInput input)
{
	//pass input to WorldEngine;
	this->worldEngine->GivenUserInput(input);
}
