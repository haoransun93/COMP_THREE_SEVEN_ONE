#include "RenderModel.h"


RenderModel::RenderModel()
{
	can_rotate = true;
	can_translate = true;
	can_scale = true;
	selected = false;
	rotate_axis = glm::vec3(0.0f, 0.0f, 1.0f);
}


RenderModel::~RenderModel()
{
}

glm::mat4 RenderModel::return_model_matrix()
{
	glm::mat4 Model = glm::mat4(1.0f);

	if (can_rotate)
	{
		Model = glm::rotate(Model, this->rotate_amount, this->rotate_axis);
	}
	if (can_translate)
	{
		Model = glm::translate(Model, this->pos_from_origin);
		Model = glm::translate(Model, this->pos_to_translate);
	}
	if (can_scale)
	{
	
	}

	return Model;
}

glm::vec3 RenderModel::return_model_location()
{
	glm::vec3 Model;
	glm::mat4 ReturnedMatrix = return_model_matrix();
	Model.x = ReturnedMatrix[3].x;
	Model.y = ReturnedMatrix[3].y;
	Model.y = ReturnedMatrix[3].z;
	return Model;
}
