#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "OpenGLEngine/RectangleShape.h"
#include "OpenGLEngine/RenderWindow.h"
#include "Registery.h"
#include <vector>
#include "Game.h"
#include "Content.h"
class Application
{
public:
	Application();
	void GameLoop();
	RenderWindow* window;
	Game* game;

};

