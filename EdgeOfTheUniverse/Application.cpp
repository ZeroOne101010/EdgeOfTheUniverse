#include "Application.h"

Application::Application()
{
	window = new RenderWindow(1920, 1080, "EdgeOfTheUniverse");

	//hero = new RectangleShape(500, 500);
	//hero->position = glm::vec2(500, 500);
	//hero->originPos = glm::vec2(-hero->size.x / 2, -hero->size.y / 2); 
	//hero->color = glm::vec4(1, 0.5f, 0.5f, 1);
    k = new Container();
	k->Position = glm::vec2(500, 500);
	//k->position = glm::vec2(-2, -2);
	//obj = new RectangleShape(500, 500);
	//obj->position = glm::vec2(500, 500);
	//obj->originPos = glm::vec2(-obj->size.x / 2, -obj->size.y / 2);
	//obj->color = glm::vec4(1, 0.5f, 0.5f, 1);
}

void Application::GameLoop()
{

	float size = 0.5f;

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


	GLfloat kVBO[] = {
	  0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
	};
	GLuint kIBO[] = {
	0, 1, 3,
	1, 2, 3
	};


	VBO modelVBO(sizeof(GLfloat) * 12, vertices, GL_STREAM_DRAW);
	IBO modelIBO(sizeof(GLuint) * 6, indices, GL_STREAM_DRAW);

	RectangleShape* g = new RectangleShape(200, 200);
	g->Position = glm::vec2(500, 500);
	g->Origin = glm::vec2(-100, -100);
	g->color = glm::vec4(1, 1, 1, 1);

	while (!glfwWindowShouldClose(window->window))
	{
		window->PollEvents();
		window->Clear(glm::vec3(20, 20, 20));
		k->Rotation = glm::rotate(k->Rotation, 1.0f, glm::vec3(0, 0, 1));
		k->RelSize += glm::vec2(0.001f, 0.01f);
		k->Position += glm::vec2(1, 0);
		//window->draw(hero);
		//k->Position += glm::vec2(1, 0);
		//k->RelSize += glm::vec2(0.001f, 0.001f);
		//k->Origin += glm::vec2(1, 1);
		g->RelSize += glm::vec2(0.01f, 0.01f);
		window->draw(k);
		//window->draw(g);
		window->Display();
	}
	glfwTerminate();
}
