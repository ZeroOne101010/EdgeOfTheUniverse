#include "World.h"
#include "Entity.h"

Entity::Entity()
{

}

void Entity::start()
{
	//Здесь пока ничего нету :3
}

void Entity::update()
{
	//Здесь пока ничего нету :3
}

Entity* Entity::addProperty(int value, int sizeProperty, std::string nameProperty)
{
	propertyManager.addProperty(value, sizeProperty, nameProperty);
	return this;
}

int Entity::getValueProperty(std::string nameProperty)
{
	return propertyManager.getValueProperty(nameProperty);
}

void Entity::SetValueProperty(std::string nameProperty, int value)
{
	propertyManager.setValueProperty(nameProperty, value);
}

Entity* Entity::createEntity(World* world)
{
	Entity* entity = getNewEntity();;
	entity->world = world;
	entity->id = id;
	return entity;
}

void Entity::draw(Renderer* renderer, Alterable alters)
{
	alters *= *this;
	renderer->draw(&rect, alters);
}
