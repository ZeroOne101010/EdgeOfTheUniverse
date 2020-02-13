#include "Application.h"

Application::Application()
{
	window = new RenderWindow(1280, 720, "EdgeOfTheUniverse");

    k = new Container();
	k->Position = glm::vec2(500, 500);
}

void Application::GameLoop()
{
	while (!glfwWindowShouldClose(window->window))
	{
		window->PollEvents();
		window->Clear(glm::vec3(20, 20, 20));

 		window->draw(k);

		window->Display();
	}
	glfwTerminate();
}
