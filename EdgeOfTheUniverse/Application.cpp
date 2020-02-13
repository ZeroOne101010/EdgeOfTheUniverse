#include "Application.h"

Application::Application()
{
	window = new RenderWindow(1280, 720, "EdgeOfTheUniverse");

    k = new Container();
	k->Position = glm::vec2(500, 500);

}

Application::~Application()
{
	delete hero;
	delete obj;
	delete k;
}

void Application::GameLoop()
{
	RectangleShape* g = new RectangleShape(200, 200);
	g->Position = glm::vec2(500, 500);
	g->Origin = glm::vec2(-100, -100);
	g->Color = glm::vec4(1, 1, 1, 1);

	while (!glfwWindowShouldClose(window->window))
	{
		window->PollEvents();
		window->Clear(glm::vec3(20, 20, 20));
		k->Angle += 0.01f;
		//k->Position += glm::vec2(-1, 0);
		//g->rotation = glm::rotate(g->rotation, 1.0f, glm::vec3(0, 0, 1));
		g->Position += glm::vec2(1, 0);

		//g->Angle += 0.01f;

		//glm::mat2 opa = glm::rotate(opa, 1.0f, glm::vec2(0, 0));
 		window->draw(k);

		int n = 0;

		//for (int i = 0; i < 8100; i++) 
		//{
			//window->draw(g);
		//}


		n = 0;
		//window->draw(g);
		window->Display();
	}
	glfwTerminate();
}
