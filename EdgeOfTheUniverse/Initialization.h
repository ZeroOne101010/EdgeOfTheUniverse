#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
class Initialization
{
public:
	Initialization(GLfloat winWidth, GLfloat winHeight, const GLchar* winName);
	GLFWwindow* window;
	static GLfloat winWidth;
	static GLfloat winHeight;
};

