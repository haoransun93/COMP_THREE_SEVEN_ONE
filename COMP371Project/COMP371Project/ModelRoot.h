#pragma once
#include "Model.h"
#include <vector>
class ModelRoot
{
public:
	std::vector<Model*> * models;
	ModelRoot();
	~ModelRoot();
};

