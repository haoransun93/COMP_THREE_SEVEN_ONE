#pragma once
#include <glm\glm.hpp>
#include <math.h>


const float PI = 3.141;
const float DEGREE_TO_RAD = 0.0174;

const int GLOBAL_WIDTH = 900;
const int GLOBAL_HEIGHT = 900;

class userInput
{
public:
	int mouseX;
	int mouseY;
	bool clicked;
	char c;
};

inline float angle_to_rad(float angle)
{
	return angle * DEGREE_TO_RAD;
}
//A yaw is a counterclockwise rotation of $ \alpha$ about the $ z$ - axis.The rotation matrix is given by
inline void rotate_yaw(float angle, glm::vec3 * vec)
{
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

	vec->x = temp.x;
	vec->y = temp.y;
	vec->z = temp.z;
};

inline void rotate_pitch(float angle, glm::vec3 * vec)
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

	vec->x = temp.x;
	vec->y = temp.y;
	vec->z = temp.z;
};

inline void rotate_roll(float angle, glm::vec3 * vec)
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

	vec->x = temp.x;
	vec->y = temp.y;
	vec->z = temp.z;
};