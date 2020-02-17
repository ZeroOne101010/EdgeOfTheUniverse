#pragma once
#include <vector>
#include "Slime.h"
class RegisteryEntity
{
public:
	static std::vector<Entity*> entity;

	static void addEntity(Entity* entity);
	static Entity* createEntity(World* world, int id);
	static void initEntity();
};

