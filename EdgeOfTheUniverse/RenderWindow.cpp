#include "RenderWindow.h"
float RenderWindow::width;
float RenderWindow::height;
const float RenderWindow::sizeConst = 1000;
RenderWindow::RenderWindow(GLfloat width, GLfloat height, const GLchar* winName)
{
	this->width = width;
	this->height = height;
	if (!glfwInit())
	{
		std::cout << "Failed to init glfw!" << std::endl;
		glfwTerminate();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, winName, nullptr, nullptr);
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
		glfwTerminate();
	}
	setViewPort();
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

RenderWindow::~RenderWindow()
{
	delete window;
}

void RenderWindow::PollEvents()
{
	glfwPollEvents();
}

void RenderWindow::Clear(glm::vec3 color)
{
	glClearColor(color.x / 255.00f, color.y / 255.00f, color.z / 255.00f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderWindow::Display()
{
	setViewPort();
	glfwSwapBuffers(window);
}
void RenderWindow::setViewPort()
{
	int kwindth, kheight;
	glfwGetFramebufferSize(window, &kwindth, &kheight);
	width = kwindth;
	height = kheight;
	glViewport(0, 0, kwindth, kheight);
}
