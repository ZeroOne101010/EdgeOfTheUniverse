#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>
#include <string>
#include "VAO.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "EdgtOfTheUniverse", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glfwSetKeyCallback(window, key_callback);


	float r = 20;
	float g = 20;
	float b = 20;

	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,  
		 0.5f, -0.5f, 0.0f, 
		-0.5f, -0.5f, 0.0f, 
		-0.5f,  0.5f, 0.0f, 
	};

	GLfloat colors[] = {
	 1.0f, 1.0f, 1.0f, 
	 1.0f, 1.0f, 1.0f, 
	 0.0f, 0.0f, 0.0f,  
	 0.0f, 0.0f, 0.0f  
	};

	GLfloat colors2[] = {
	1.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f
	};

	GLuint indices[] = {  
	0, 1, 3,   
	1, 2, 3    
	};
	const GLchar* vertexShaderSource =
		"#version 330 core \n"
		"layout (location = 0) in vec3 position; \n"
		"layout (location = 1) in vec3 color; \n"
		"out vec3 ourColor; \n"
		"out vec3 pixelPos; \n"
		"uniform vec4 pos; \n"
		"void main() \n"
		"{ \n"
		"ourColor = color; \n"
		"pixelPos = position; \n"
		"gl_Position = pos + vec4(position, 1.0); \n"
		"} \n";

	const GLchar* fragmentShaderSource =
		"#version 330 core \n"
		"in vec3 ourColor; \n"
		"in vec3 pixelPos; \n"
		"out vec4 color; \n"
		"void main() \n"
		"{ \n"
		"float distance = sqrt(pixelPos.x * pixelPos.x + pixelPos.y * pixelPos.y) * 2; \n"
		//"color = vec4(distance, distance, 1, 1.0f); \n"
		"color = vec4(ourColor.z, ourColor.y, 1, 1.0f); \n"
		"} \n";


	VBO modelVBO(sizeof(vertices), vertices, GL_STATIC_DRAW);
	VBO colorVBO(sizeof(colors), colors, GL_STREAM_DRAW);

	IBO modelIBO(sizeof(indices), indices, GL_STATIC_DRAW);


	Shader shader(vertexShaderSource, fragmentShaderSource);
	shader.addAttribute(colorVBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);

	VAO vao(modelVBO, modelIBO);

	//vao.updateData(1, sizeof(colors2), colors2, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(r / 255.00f, g / 255.00f, b / 255.00f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		std::cout << "kek" << std::endl;
		vao.draw();


		glfwSwapBuffers(window);
	}
	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
