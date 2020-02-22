#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
struct FloatRect
{
	FloatRect();
	FloatRect(GLfloat positionX, GLfloat positionY, GLfloat sizeX, GLfloat sizeY);
	FloatRect(glm::vec2 position, GLfloat sizeX, GLfloat sizeY);
	FloatRect(GLfloat positionX, GLfloat positionY, glm::vec2 size);
	FloatRect(glm::vec2 position, glm::vec2 size);
	bool Intersects(FloatRect rect);
	GLfloat positionX = 0;
	GLfloat positionY = 0;
	GLfloat sizeX = 0;
	GLfloat sizeY = 0;
};