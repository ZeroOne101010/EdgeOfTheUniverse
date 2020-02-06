#include "Initialization.h"
GLfloat Initialization::winWidth;
GLfloat Initialization::winHeight;
Initialization::Initialization(GLfloat winWidth, GLfloat winHeight, const GLchar* winName)
{
	if (!glfwInit())
	{
		std::cout << "Failed to init glfw!" << std::endl;
		glfwTerminate();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(winWidth, winHeight, winName, nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init GLEW!" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	this->winWidth = width;
	this->winHeight = height;
}
