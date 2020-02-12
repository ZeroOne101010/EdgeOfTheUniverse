#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"

class RenderWindow : public Renderer
{
public:
	RenderWindow(GLfloat width, GLfloat height, const GLchar* winName);
	~RenderWindow();
	GLFWwindow* window;
	static float width, height;
	static const float sizeConst;
	void PollEvents();
	void Clear(glm::vec3 color);
	void Display();
private:
	void setViewPort();
};

