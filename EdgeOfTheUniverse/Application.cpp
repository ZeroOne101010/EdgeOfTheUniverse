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
	//FloatRect floatRect1 = FloatRect(0, 24, 21, 21);
	//FloatRect floatRect2 = FloatRect(0, 0, 21, 48);

	//std::cout << floatRect1.Intersects(floatRect2) << std::endl;


	while (!glfwWindowShouldClose(window->window))
	{
		window->PollEvents();
		window->Clear(glm::vec3(107, 155, 238));

		window->draw(game);

		window->Display();
	}
	glfwTerminate();
}
