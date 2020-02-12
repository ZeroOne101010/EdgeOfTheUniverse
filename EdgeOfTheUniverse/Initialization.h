#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "RenderWindow.h"
class Initialization
{
public:
	Initialization(GLfloat winWidth, GLfloat winHeight, const GLchar* winName);
	~Initialization();
	GLFWwindow* window;
	GLint winWidth, winHeight;
};

