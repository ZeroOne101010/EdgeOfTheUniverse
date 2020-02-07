#include "Application.h"

Application::Application()
{
	initialization = new Initialization(1920, 1080, "EdgeOfTheUniverse");
}

void Application::GameLoop()
{
	float r = 20;
	float g = 20;
	float b = 20;
	//GLfloat vertices[] = {
	//	 0.5f,  0.5f, 0.0f,  
	//	 0.5f, -0.5f, 0.0f, 
	//	-0.5f, -0.5f, 0.0f, 
	//	-0.5f,  0.5f, 0.0f, 
	//};

	float size = 0.05f;

	GLfloat vertices[] = {
	 size,  size, 0.0f,
	 size, -size, 0.0f,
	-size, -size, 0.0f,
	-size,  size, 0.0f,
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

	VBO modelVBO(sizeof(vertices), vertices, GL_STREAM_DRAW);
	VBO colorVBO(sizeof(colors), colors, GL_STREAM_DRAW);
	IBO modelIBO(sizeof(indices), indices, GL_STREAM_DRAW);
	GLfloat k = 0;
	VAO vao(modelVBO, modelIBO);

	GLuint id = glGetUniformLocation(vao.shader->shaderProgram, "v");

	float* m = new float[300];

	while (!glfwWindowShouldClose(initialization->window))
	{
		glfwPollEvents();

		glClearColor(r / 255.00f, g / 255.00f, b / 255.00f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		k += 0.01f;
		vao.rotationMatrix = glm::rotate(vao.rotationMatrix, 1.0f, glm::vec3(0, 0, 1));
		vao.color = glm::vec4(1, 0.5f, 1, 1);


		for (int x = 0; x < 4100; x++)
		{
			glUniform1fv(id, 300, m);
			vao.position = glm::vec2(cos(k) / 2, 0);
			vao.draw();
		}

		int b = 0;

		glfwSwapBuffers(initialization->window);
	}
	glfwTerminate();
}
