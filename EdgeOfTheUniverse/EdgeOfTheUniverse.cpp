#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "Shader.h"
#include <iostream>
#include <string>
#include "VAO.h"

int main()
{
	Application* application = new Application();
	application->GameLoop();
	delete application;
	return 0;
}
