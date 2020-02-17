#pragma once
#include "AlterableHeader.h"
#include "OpenGLEngine/RectangleShape.h"
#include "PropertyManager.h"

class World;

class Entity : public Alterable, public IDraw
{
public:
	Entity();

	int id = 0;
	bool saveInChunk = true;
	PropertyManager propertyManager;
	RectangleShape rect = RectangleShape(glm::vec2(16, 16));;
	World* world = nullptr;

	virtual void start();
	virtual void update();

	Entity* addProperty(int value, int sizeProperty, std::string nameProperty);
	int getValueProperty(std::string nameProperty);
	void SetValueProperty(std::string nameProperty, int value);

	virtual Entity* getNewEntity() = 0;
	Entity* createEntity(World* world);

	virtual void draw(Renderer* renderer, Alterable alters) override;
};

