#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Alter
{
public:

	glm::vec2 position;
	glm::vec2 originPos;
	glm::vec2 relSize = glm::vec2(1, 1);
	glm::vec2 size;
	int sizeConst;
	float winWidth;
	float winHeight;
	glm::vec2 correctSize;
	Alter operator *= (Alter alter);
};

