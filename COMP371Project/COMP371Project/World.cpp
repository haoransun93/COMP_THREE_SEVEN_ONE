#include "World.h"


World::World()
{
	this->camera = new Camera(); // what kind of camera
}


World::~World()
{
	delete camera;
}
