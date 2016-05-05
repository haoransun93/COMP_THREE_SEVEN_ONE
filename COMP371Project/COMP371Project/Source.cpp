// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <ctime>

// Include GLEW
#define GLEW_STATIC
#include <glew.h>

// Include GLFW
#include <glfw3.h>
#include <glut.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

#include "Constants.h"
#include "RenderModel.h"

GLFWwindow* window;
GLuint programID;
GLuint MatrixID;

glm::mat4 Projection;
glm::vec3 cam;
glm::vec3 look;
glm::vec3 up;
glm::vec3 lookat;
glm::mat4 View;

float rotate_amount = 0.0f;
float rotate_speed = 0.003f;

std::vector<RenderModel> models;
std::map<std::string, GLuint> buffers;

MODE_MOVE move_mode = MODE_MOVE::CAMERA;
int selected_index;

std::clock_t creation;

float check_collision_between_camera_sight_and_model(RenderModel model)
{
	glm::vec3 direction_unit = convert_to_unit_vector(&lookat);
	glm::vec3 origin_difference = cam - (model.pos_to_translate);
	float rad_sq = pow(model.radius, 2);
	float ioc = dot_product(&direction_unit, &origin_difference);
	float ioc_sq = pow(ioc, 2);
	float ocnorm_sq = pow(vector_norm(&origin_difference), 2);
	float under_root = ioc_sq - ocnorm_sq + rad_sq;

	if (under_root < 0.0f)
	{
		return -1.0f;
	}

	else 
	{
		float root = sqrt(under_root);
		float first = abs(ioc - root);
		float second = abs(ioc + root);

		return max(first, second);
	}
	//get the smallest in absolute value;
}

glm::vec3 handleinput_move_camera()
{
	glm::vec3 temp;

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		temp = SPEED_UP * LOOK_AT_MOVE * glm::normalize(glm::cross(lookat, AXIS_Y));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		temp = -1.0f * SPEED_UP * LOOK_AT_MOVE * glm::normalize(glm::cross(lookat, AXIS_Y));
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		temp = SPEED_UP * LOOK_AT_MOVE * lookat;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		temp = -1.0f * SPEED_UP * LOOK_AT_MOVE * lookat;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
		temp = -1.0f * SPEED_UP * LOOK_AT_MOVE * glm::normalize(glm::cross(lookat, glm::normalize(glm::cross(lookat, AXIS_Y))));
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
		temp = 1.0f * SPEED_UP * LOOK_AT_MOVE * glm::normalize(glm::cross(lookat, glm::normalize(glm::cross(lookat, AXIS_Y))));
	}
	return temp;
}

int handleinput_change_viewdirection()
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		//lookat = rotate_roll(SPEED_UP * -0.1f, &lookat);
		lookat = rotate_given_angle_axis(SPEED_UP * -0.01f, lookat, ROTATE_AXIS_X);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		lookat = rotate_given_angle_axis(SPEED_UP * 0.01f, lookat, ROTATE_AXIS_X);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		lookat = rotate_given_angle_axis(SPEED_UP * 0.01f, lookat, ROTATE_AXIS_Y);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		lookat = rotate_given_angle_axis(SPEED_UP * -0.01f, lookat, ROTATE_AXIS_Y);
	}
	look = cam + lookat;
	return 0;
}

int handleinput_change_state()
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
		rotate_speed += SPEED_UP * 0.00001f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
		rotate_speed -= SPEED_UP * 0.00001f;
	}
	return 0;
}

int handleinput_build_new_object()
{
	//create object
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){

		if ((clock() - creation) < 500.0f)
		{
			return 1;
		};

		creation = clock();
		
		RenderModel temp;
		temp.vertex = buffers[std::string("CUBE")];
		temp.color = buffers[std::string("BLACK")];
		temp.radius = 0.6f;
		temp.rotate_amount = -1;
		temp.can_rotate = false;
		temp.pos_from_origin = glm::vec3(-0.5f);
		temp.pos_to_translate = cam + 4.0f * lookat;
		models.push_back(temp);
	}

	return 0;
}

int deselect_all_models()
{
	move_mode = MODE_MOVE::CAMERA;
	selected_index = -1;
	for (int i = 0; i < models.size(); ++i)
	{
		models[i].selected = false;
	}
	return 0;
}

int handleinput_selection()
{
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){
		deselect_all_models();
		int index = -1;
		float min = 10000.0f;
		for (int i = 0; i < models.size(); ++i)
		{
			float distance = check_collision_between_camera_sight_and_model(models[i]);
			if (distance > 0.0f && distance < min)
			{
				min = distance;
				index = i;
			}
		}

		if (index != -1)
		{
			move_mode = MODE_MOVE::OBJECT;
			models[index].selected = true;
			selected_index = index;
			//select that model to be the correct one;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		deselect_all_models();
	}

	return 0;
}


int handleinput()
{
	glm::vec3 move = handleinput_move_camera();
	if (move_mode == MODE_MOVE::CAMERA)
	{
		cam += move;
	}
	else if (move_mode == MODE_MOVE::OBJECT)
	{
		models[selected_index].pos_to_translate += move;
	}

	handleinput_change_viewdirection();
	handleinput_change_state();
	handleinput_build_new_object();

	handleinput_selection();
	return 0;
}

int draw_pointer()
{
	glm::mat4 Model = glm::mat4(1.0f);
	glm::vec3 PointerLook = cam + 2.0f * lookat;
	//Model = glm::scale(Model, glm::vec3(0.05f));
	Model = glm::translate(Model, PointerLook);
	Model = glm::scale(Model, glm::vec3(0.05f));
	DrawObject(buffers["POINTER"], buffers["POINTER_COLOR"], MatrixID, (Projection * View * Model));
	return 0;
}

int main(void)
{
	creation = clock();

	// Initialise GLFW
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1024, 768, "COMP371 PROJECT", NULL, NULL);
	if (window == NULL){
		return -1;
	}
	glfwMakeContextCurrent(window);


	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		return -1;
	}


	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
	MatrixID = glGetUniformLocation(programID, "MVP");

	Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	cam = glm::vec3(0.0f, 0, -4.0f);
	look = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 1, 0);
	lookat = glm::vec3(0.0f, 0.0f, 1.0f);

	View = glm::lookAt(cam, look, up);

	GLuint pointerbuffer = LoadBuffer(pointer_data);
	buffers.insert(std::pair<std::string, GLuint>(std::string("POINTER"), pointerbuffer));

	GLuint pointer_colorbuffer = LoadBuffer(pointer_color);
	buffers.insert(std::pair<std::string, GLuint>(std::string("POINTER_COLOR"), pointer_colorbuffer));
	
	GLuint vertexbuffer = LoadBuffer(g_vertex_buffer_data);
	buffers.insert(std::pair<std::string, GLuint>(std::string("CUBE"), vertexbuffer));

	GLuint colorbuffer = LoadBuffer(g_color_buffer_data);
	buffers.insert(std::pair<std::string, GLuint>(std::string("BLACK"), colorbuffer));

	GLuint colorbuffergrey = LoadBuffer(g_color_buffer_data_grey);
	buffers.insert(std::pair<std::string, GLuint>(std::string("GREY"), colorbuffergrey));

	GLuint colorbufferselected = LoadBuffer(g_color_buffer_selected);
	buffers.insert(std::pair<std::string, GLuint>(std::string("SELECTED"), colorbufferselected));

	RenderModel temp;
	temp.vertex = buffers[std::string("CUBE")];
	temp.color = buffers[std::string("BLACK")];
	temp.rotate_amount = 0;
	temp.radius = 0.6f;
	temp.rotate_axis = ROTATE_AXIS_Z;
	temp.pos_from_origin = glm::vec3(-0.5f);
	temp.pos_to_translate = glm::vec3(0.0f);
	models.push_back(temp);

	RenderModel temp2;
	temp2.vertex = buffers[std::string("CUBE")];
	temp2.color = buffers[std::string("GREY")];
	temp2.radius = 0.6f;
	temp2.rotate_amount = 0;
	temp2.rotate_axis = ROTATE_AXIS_Z;
	temp2.pos_from_origin = glm::vec3(-0.5f);
	temp2.pos_to_translate = glm::vec3(5.0f, 0.0f, 0.0f);
	models.push_back(temp2);

	// Use our shader
	glUseProgram(programID);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	do
	{
		rotate_amount += rotate_speed;

		View = glm::lookAt(cam, look, up);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use our shader
		glUseProgram(programID);

		for (int i = 0; i < models.size(); ++i)
		{
			draw_pointer();

			models[i].rotate_amount = rotate_amount;
			glm::mat4 Model = models[i].return_model_matrix();
			glm::mat4 MVP = Projection * View * Model;
			if (models[i].selected)
			{
				DrawObject(models[i].vertex, buffers["SELECTED"], MatrixID, MVP);
			}
			else {
				DrawObject(models[i].vertex, models[i].color, MatrixID, MVP);
			}
		}

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		handleinput();
	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&	glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

