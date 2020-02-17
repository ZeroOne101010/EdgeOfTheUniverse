#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Alter.h"
class Alterable
{
public:
	static Alterable Default;
	glm::vec2 Position;
	glm::vec2 Origin;
	glm::vec2 RelSize = glm::vec2(1, 1);
	GLfloat Angle;
	Alterable operator *= (Alterable alter);
};

