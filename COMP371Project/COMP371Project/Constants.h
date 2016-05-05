#pragma once
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// Include GLEW
#define GLEW_STATIC
#include <GL\glew.h>

// Include GLFW
#include <GLFW\glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


const float PI = 3.141;
const float DEGREE_TO_RAD = 0.0174;

const int GLOBAL_WIDTH = 900;
const int GLOBAL_HEIGHT = 900;


const float LOOK_AT_MOVE = 0.01f;

const glm::vec3 ROTATE_AXIS_X = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 ROTATE_AXIS_Y = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 ROTATE_AXIS_Z = glm::vec3(0.0f, 0.0f, 1.0f);

const glm::vec3 AXIS_X = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 AXIS_Y = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 AXIS_Z = glm::vec3(0.0f, 0.0f, 1.0f);

class userInput
{
public:
	int mouseX;
	int mouseY;
	bool clicked;
	char c;
};

enum MODE_MOVE
{
	CAMERA,
	OBJECT,
};

enum MODE_SELECT
{
	COLOR,
	TEXTURE,
};

inline float angle_to_rad(float angle)
{
	return angle * DEGREE_TO_RAD;
}

inline float vector_norm(glm::vec3 * vec)
{
	return sqrt(pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2));
}


inline glm::vec3 convert_to_unit_vector(glm::vec3 * vec)
{
	float base = vector_norm(vec);
	glm::vec3 temp;
	temp.x = vec->x / base;
	temp.y = vec->y / base;
	temp.z = vec->z / base;
	return temp;
}

inline float dot_product(glm::vec3 * vec1, glm::vec3 * vec2)
{
	return ((vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z));
}
// Z ^
//   |
//   |
//   |
//   ---------> Y
inline glm::vec3 rotate_fixed_x(float angle, glm::vec3 * vec)
{
	float y = vec->y;
	float z = vec->z;

	float current_angle = atan((y / z));
	float new_angle = current_angle + angle;
	float radius = sqrt(pow(y, 2) + pow(z, 2));

	glm::vec3 temp;
	temp.x = vec->x;
	temp.y = radius * cos(new_angle);
	temp.z = radius * sin(new_angle);

	return temp;
};

//A yaw is a counterclockwise rotation of $ \alpha$ about the $ z$ - axis.The rotation matrix is given by
inline glm::vec3 rotate_yaw(float angle, glm::vec3 * vec)
{
	/*
	float a1, a2, a3;
	float b1, b2, b3;
	float c1, c2, c3;

	float rad = angle_to_rad(angle);

	a1 = cos(rad);	a2 = -1 * sin(rad); a3 = 0;
	b1 = sin(rad);	b2 = cos(rad);		b3 = 0;
	c1 = 0;			c2 = 0;				c3 = 1;

	glm::vec3 temp;
	temp.x = a1 * vec->x + a2 * vec->y + a3 * vec->z;
	temp.y = b1 * vec->x + b2 * vec->y + b3 * vec->z;
	temp.z = c1 * vec->x + c2 * vec->y + c3 * vec->z;
	*/
};

inline glm::vec3 rotate_given_angle_axis(float angle, glm::vec3 vec, glm::vec3 axis)
{
	glm::vec4 tempv4(vec, 0);

	glm::mat4 rotateyaw = glm::rotate(glm::mat4(1.0f), angle, axis);

	glm::vec4 temp = rotateyaw * tempv4;

	glm::vec3 tempv3;
	tempv3.x = temp.x;
	tempv3.y = temp.y;
	tempv3.z = temp.z;
	return tempv3;
}

inline glm::vec3 rotate_pitch(float angle, glm::vec3 * vec)
{
	float a1, a2, a3;
	float b1, b2, b3;
	float c1, c2, c3;

	float rad = angle_to_rad(angle);

	a1 = cos(rad);		a2 = 0;				a3 = sin(rad);
	b1 = 0;				b2 = 1;				b3 = 0;
	c1 = -1*sin(rad);	c2 = 0;				c3 = cos(rad);

	glm::vec3 temp;
	temp.x = a1 * vec->x + a2 * vec->y + a3 * vec->z;
	temp.y = b1 * vec->x + b2 * vec->y + b3 * vec->z;
	temp.z = c1 * vec->x + c2 * vec->y + c3 * vec->z;

	return temp;
};

inline glm::vec3 rotate_roll(float angle, glm::vec3 * vec)
{
	float a1, a2, a3;
	float b1, b2, b3;
	float c1, c2, c3;

	float rad = angle_to_rad(angle);

	a1 = 1;			a2 = 0;				a3 = 0;
	b1 = 0;			b2 = cos(rad);		b3 = -1 * sin(rad);
	c1 = 0;			c2 = sin(rad);		c3 = cos(rad);

	glm::vec3 temp;
	temp.x = a1 * vec->x + a2 * vec->y + a3 * vec->z;
	temp.y = b1 * vec->x + b2 * vec->y + b3 * vec->z;
	temp.z = c1 * vec->x + c2 * vec->y + c3 * vec->z;

	return temp;
};

void DrawObject(GLuint vertexbuffer, GLuint colorbuffer, GLuint MatrixID, glm::mat4 MVP)
{
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()){
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else{
		printf("Impossible to open %s.", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()){
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

GLuint LoadBuffer(std::vector<GLfloat> vector)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vector.size(), &vector[0], GL_STATIC_DRAW);

	return buffer;
}
std::vector<GLfloat> g_vertex_buffer_data = {

	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,


	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 0.0f,

	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,


	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,

	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	1.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f,

};

// One color for each vertex. They were generated randomly.
std::vector<GLfloat> g_color_buffer_data_grey = {
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,

	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
	0.4f, 0.4f, 0.4f,
};

// One color for each vertex. They were generated randomly.
std::vector<GLfloat> g_color_buffer_data = {
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,

	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
	0.7f, 0.7f, 0.7f,
};

// One color for each vertex. They were generated randomly.
std::vector<GLfloat> g_color_buffer_selected = {
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
};

// One color for each vertex. They were generated randomly.
std::vector<GLfloat> pointer_data = {
	0.0f, 0.1f, 0.0f,
	-0.1f, -0.1f, 0.0f,
	0.1f, -0.1f, 0.0f,
};

std::vector<GLfloat> pointer_color = {
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
};