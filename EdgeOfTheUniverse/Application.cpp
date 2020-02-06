#include "Application.h"

Application::Application()
{
	initialization = new Initialization(800, 600, "EdgeOfTheUniverse");
}

void Application::GameLoop()
{
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

	GLuint indices[] = {  
	0, 1, 3,   
	1, 2, 3    
	};

	VBO modelVBO(sizeof(vertices), vertices, GL_STATIC_DRAW);
	VBO colorVBO(sizeof(colors), colors, GL_STREAM_DRAW);
	IBO modelIBO(sizeof(indices), indices, GL_STATIC_DRAW);

	VAO vao(modelVBO, modelIBO);
	vao.setColor(0.5f, 0.5f, 1, 0);
	while (!glfwWindowShouldClose(initialization->window))
	{
		glfwPollEvents();

		glClearColor(r / 255.00f, g / 255.00f, b / 255.00f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		vao.draw();
		glfwSwapBuffers(initialization->window);
	}
	glfwTerminate();
}
