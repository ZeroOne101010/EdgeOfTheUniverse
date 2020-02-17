#include "RegisteryEntity.h"

std::vector<Entity*> RegisteryEntity::entity;

void RegisteryEntity::addEntity(Entity* entity)
{
	entity->id = RegisteryEntity::entity.size();
	RegisteryEntity::entity.push_back(entity);
}

Entity* RegisteryEntity::createEntity(World* world, int id)
{
	return RegisteryEntity::entity[id]->createEntity(world);
}

void RegisteryEntity::initEntity()
{
	addEntity(new Slime());
}
