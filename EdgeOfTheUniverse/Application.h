#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Initialization.h"
#include "VAO.h"
#include "VBO.h"
#include <vector>
class Application
{
public:
	Application();
	void GameLoop();
	Initialization* initialization;
};

