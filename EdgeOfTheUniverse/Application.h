#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "OpenGLEngine/RectangleShape.h"
#include "OpenGLEngine/RenderWindow.h"
#include "Registery.h"
#include <vector>
#include "Game.h"
#include "Content.h"
#include "UICanvas.h"
class Application
{
public:
	Application();
	~Application();
	void GameLoop();
	UICanvas* uiCanvas;
	RenderWindow* window;
	Game* game;

};

