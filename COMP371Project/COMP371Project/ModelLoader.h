#pragma once
#include "glew.h"
#include "glm\glm.hpp"
#include "glut.h"

#include "Model.h"
#include "ModelRoot.h"
#include "Texture.h"

#include <vector>
#include <iostream>
#include <map>
#include <string>

class ModelLoader
{
public:

	std::vector<ModelRoot *> * models;
	std::map<std::string, Texture> * textures;

	ModelLoader();	
	~ModelLoader();

	void LoadModel(char * input);
	char * ModelLoader::LoadModelComponent(FILE * file, Model * model, int * finished, int &, int &, int &);
	int ModelLoader::LoadTexture(const char * imagepath);
};

