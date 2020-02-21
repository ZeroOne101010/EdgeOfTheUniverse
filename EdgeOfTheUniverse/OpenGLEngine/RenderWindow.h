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
	static const int sizeKeyState;
	static bool* keyState;
	static void updateKeyState(RenderWindow* window);
	static bool getKeyState(int keyCode);
	static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
	static bool mouseLeft;
	static bool mouseRight;

	RenderWindow(GLfloat width, GLfloat height, const GLchar* winName);
	~RenderWindow();
	static GLFWwindow* window;
	static float width, height;
	static glm::vec2 correctSize;
	static bool changeWindow;
	void PollEvents();
	void Clear(glm::vec3 color);
	void Display();
	void setViewPort();
};

