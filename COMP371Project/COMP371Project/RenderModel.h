#pragma once

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"


class RenderModel
{
public:

	float rotate_amount;
	glm::vec3 rotate_axis;

	glm::vec3 pos_from_origin;
	glm::vec3 pos_to_translate;

	GLuint vertex;
	GLuint color;
	GLuint texture;

	//Model model = NULL;
 
	glm::mat4 return_model_matrix();
	glm::vec3 return_model_location();

	bool can_rotate;
	bool can_translate;
	bool can_scale;
	bool selected;

	float radius;

	RenderModel();
	~RenderModel();
};

