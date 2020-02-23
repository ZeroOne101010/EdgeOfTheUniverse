
#include "RegisteryEntity.h"

std::vector<Entity*> RegisteryEntity::entity;
int RegisteryEntity::mobsCount;
int RegisteryEntity::itemsCount;
void RegisteryEntity::InitEntity(Entity* entity)
{
	if (dynamic_cast<Mob*>(entity)) {
		entity->id = mobsCount;
		mobsCount++;
	}
	if (dynamic_cast<Item*>(entity)) {
		entity->id = itemsCount;
		itemsCount++;
	}
	RegisteryEntity::entity.push_back(entity);
}
Entity* RegisteryEntity::addEntity(World* world, int id, glm::vec2 pos)
{
	Entity* localEntity = RegisteryEntity::createEntity(world, id);
	localEntity->Position = glm::vec2(pos.x, pos.y);
	world->entity.push_back(localEntity);
	return localEntity;
}
Entity* RegisteryEntity::addMob(World* world, int id, glm::vec2 pos)
{
	Entity* localEntity = RegisteryEntity::createMob(world, id);
	localEntity->Position = glm::vec2(pos.x, pos.y);
	world->entity.push_back(localEntity);
	return localEntity;
}

Entity* RegisteryEntity::addItem(World* world, int id, glm::vec2 pos)
{
	Entity* localEntity = RegisteryEntity::createItem(world, id);
	localEntity->Position = glm::vec2(pos.x, pos.y);
	world->entity.push_back(localEntity);
	return localEntity;
}

Entity* RegisteryEntity::createEntity(World* world, int id)
{
	return RegisteryEntity::entity[id]->createEntity(world);
}

Entity* RegisteryEntity::createMob(World* world, int id)
{
	return RegisteryEntity::entity[id]->createEntity(world);
}

Entity* RegisteryEntity::createItem(World* world, int id)
{
	int itemID = id + mobsCount;
	return RegisteryEntity::entity[itemID]->createEntity(world);
}

void RegisteryEntity::initEntity()
{
	initMob();
	initItem();
}

void RegisteryEntity::initMob()
{
	InitEntity(new Player());
	InitEntity(new Slime());
}

void RegisteryEntity::initItem()
{
	InitEntity(new Amnis());
}
