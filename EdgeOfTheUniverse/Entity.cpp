#include "World.h"
#include "Entity.h"

Entity::Entity()
{
	rect->tbo = Content::defaultTexture;
}

Entity::Entity(FloatRect textureRect, TBO* texture)
{
	this->textureRect = textureRect;
	rect->tbo = texture;
}

Entity::Entity(TBO* texture)
{
	rect->tbo = texture;
	setAllTexture();
}

void Entity::A(float speed)
{
	velocity = glm::vec2(speed - this->moveSpeed - flySpeed, velocity.y);
}

void Entity::D(float speed)
{
	velocity = glm::vec2(speed + this->moveSpeed + flySpeed, velocity.y);
}

void Entity::W(float hightJump)
{
	velocity = glm::vec2(velocity.x, hightJump - flySpeed);
}

void Entity::S(float downSpeed)
{
	velocity = glm::vec2(velocity.x, downSpeed + flySpeed);
}

Entity::~Entity()
{
	delete rect;
}


void Entity::start()
{
	//Здесь пока ничего нету :3
}

void Entity::setTexture(TBO* texture)
{
	rect->tbo = texture;
}

void Entity::setAllTexture(int textureID)
{
	textureRect = FloatRect(0, 0, rect->tbo->sizeTexture[textureID].x, Content::sprite_AmnisItem->sizeTexture[textureID].y);
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

Alterable Entity::draw(Renderer* renderer, Alterable alters)
{
	alters *= this;
	rect->textureRect = textureRect;
	renderer->draw(rect, alters);
	return alters;
}
