#pragma once
#include "AlterableHeader.h"
#include "glm/vec2.hpp"
#include "OpenGLEngine/RenderWindow.h"
#include "UI.h"
class Cursor
{
public:
	static bool Intersect(Alterable* alterable, float offsetX, float offsetY, GLFWwindow* window);
	static bool Intersect(UI* ui, GLFWwindow* window);
	static glm::vec2 getMousePosition(GLFWwindow* window);
};

