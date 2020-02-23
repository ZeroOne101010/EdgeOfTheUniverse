#pragma once
#include <vector>
#include "World.h"

#include "Mob.h"
#include "Player.h"
#include "Slime.h"

#include "Item.h"
#include "Amnis.h"

class RegisteryEntity
{
public:
	static std::vector<Entity*> entity;
	static void InitEntity(Entity* entity);
	static Entity* addEntity(World* world, int id, glm::vec2 pos = glm::vec2(0, 0));
	static Entity* addMob(World* world, int id, glm::vec2 pos = glm::vec2(0, 0));
	static Entity* addItem(World* world, int id, glm::vec2 pos = glm::vec2(0, 0));
	static Entity* createEntity(World* world, int id);
	static Entity* createMob(World* world, int id);
	static Entity* createItem(World* world, int id);
	static void initEntity();

private:
	static void initMob();
	static void initItem();
	static int mobsCount;
	static int itemsCount;
};

