#include "Application.h"

Application::Application()
{
	window = new RenderWindow(1280, 720, "EdgeOfTheUniverse");
	Content::load();
	Registery::load();
	game = new Game(window);
}

Application::~Application()
{
	delete game;
}



void Application::GameLoop()
{

	while (!glfwWindowShouldClose(window->window))
	{
		window->PollEvents();

		window->Clear(glm::vec3(107, 155, 238));

		window->draw(game);

		window->Display();
	}
	glfwTerminate();
}
