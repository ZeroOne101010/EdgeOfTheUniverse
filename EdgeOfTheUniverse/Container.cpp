#include "Container.h"

Container::Container()
{
	obj = new RectangleShape(100, 100);
	obj->position = glm::vec2(0, 0);
	obj->color = glm::vec4(0.5f, 1, 0.8f, 1);
	obj->origin = glm::vec2(-obj->size.x / 2, -obj->size.y / 2);
	b = new box();
	b->Position = glm::vec2(0, 0);
	
}

void Container::draw(Renderer* renderer, Alterable alters)
{
	//alters.alter *= getAlters();
	alters *= *this;
	//obj->position += glm::vec2(1, 0);
	renderer->draw(obj, alters);
	renderer->draw(b, alters);
}
