#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Initialization.h"
#include "VAO.h"
#include "VBO.h"
#include <vector>
#include "RectangleShape.h"
#include "RenderWindow.h"
#include "Container.h"
class Application
{
public:
	Application();
	void GameLoop();
	//Initialization* initialization = new Initialization(1000, 1000, "EdgeOfTheUniverse");
	RenderWindow* window;
	//GLFWwindow* window;
	RectangleShape* hero;
	RectangleShape* obj;
	Container* k;

};

