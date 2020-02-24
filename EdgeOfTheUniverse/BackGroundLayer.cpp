#include "World.h"
#include "BackGroundLayer.h"
BackGroundLayer::BackGroundLayer(World* world, glm::vec2 speed, glm::vec2 size)
{
	this->speed = speed;
	layer.Size = size;
	this->world = world;
	layer.Angle = 0;
}

Alterable BackGroundLayer::draw(Renderer* renderer, Alterable alters)
{
	layer.textureRect = FloatRect(world->Position.x * -speed.x, world->Position.y * -speed.y, layer.Size.x, layer.Size.y);
	renderer->draw(&layer);
	return alters;
}
