#include "RenderWindow.h"
GLFWwindow* RenderWindow::window;
float RenderWindow::width;
float RenderWindow::height;
 glm::vec2 RenderWindow::correctSize;
 bool RenderWindow::changeWindow = true;

const int RenderWindow::sizeKeyState = 256;
bool* RenderWindow::keyState = new bool[RenderWindow::sizeKeyState];

bool RenderWindow::mouseLeft;
bool RenderWindow::mouseRight;

void RenderWindow::updateKeyState(RenderWindow* window)
{
	for (int x = 0; x < sizeKeyState; x++)
	{
		keyState[x] = glfwGetKey(window->window, x) == 1 ? true : false;
	}
}

// оды клавишь написанны в макросах из библиотеки GLFW
bool RenderWindow::getKeyState(int keyCode)
{
	return keyState[keyCode];
}

void RenderWindow::mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (GLFW_PRESS == action)
		{
			mouseLeft = true;
		}
		else
		{
			mouseLeft = false;
		}
	}
}

RenderWindow::RenderWindow(GLfloat width, GLfloat height, const GLchar* winName)
{
	if (!glfwInit())
	{
		std::cout << "Failed to init glfw!" << std::endl;
		glfwTerminate();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
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
	glfwSetMouseButtonCallback(window, mouse_callback);
	setViewPort();
	glShadeModel(GL_FLAT);
	//glEnable(GL_CULL_FACE);
	//glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glDisable(GL_NORMALIZE);
}

RenderWindow::~RenderWindow()
{
	delete window;
}

void RenderWindow::PollEvents()
{
	glfwPollEvents();
	updateKeyState(this);
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
	if (width - kwindth != 0 || height - kheight != 0)
	{
		width = kwindth;
		height = kheight;
		correctSize = glm::vec2(1.0f / RenderWindow::width, 1.0f / RenderWindow::height);
		glViewport(0, 0, kwindth, kheight);
	}
}

