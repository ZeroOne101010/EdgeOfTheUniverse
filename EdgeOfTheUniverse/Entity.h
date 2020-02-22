#pragma once
#include "AlterableHeader.h"
#include "OpenGLEngine/RectangleShape.h"
#include "PropertyManager.h"
#include "Block.h"

class World;

class Entity : public Alterable, public IDraw
{
public:
	Entity();
	~Entity();
	int id = 0;
	bool saveInChunk = true;
	PropertyManager propertyManager;
	RectangleShape* rect = new RectangleShape(glm::vec2(Block::sizeBlock, Block::sizeBlock));;
	World* world = nullptr;
	glm::vec2 velocity;

	virtual void start();
	virtual void update();

	Entity* addProperty(int value, int sizeProperty, std::string nameProperty);
	int getValueProperty(std::string nameProperty);
	void SetValueProperty(std::string nameProperty, int value);

	virtual Entity* getNewEntity() = 0;
	Entity* createEntity(World* world);

	virtual void draw(Renderer* renderer, Alterable alters) override;
};

