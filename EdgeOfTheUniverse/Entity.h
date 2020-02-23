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
	Entity(FloatRect textureRect, TBO* texture);
	Entity(TBO* texture);
	virtual void A(float speed);
	virtual void D(float speed);
	virtual void W(float hightJump);
	virtual void S(float downSpeed);
	float moveSpeed;
	float flySpeed;
	float Af;
	float Df;
	float Wf;
	float Sf;
	~Entity();
	int id = 0;
	bool saveInChunk = true;
	PropertyManager propertyManager;
	RectangleShape* rect = new RectangleShape(glm::vec2(Block::sizeBlock, Block::sizeBlock));;
	World* world = nullptr;
	glm::vec2 velocity;
	FloatRect textureRect = FloatRect(0, 0, Block::sizeBlock, Block::sizeBlock);
	//TBO* texture = Content::defaultTexture;
	virtual void start();
	void setTexture(TBO* texture);
	void setAllTexture(int textureID = 0);

	Entity* addProperty(int value, int sizeProperty, std::string nameProperty);
	int getValueProperty(std::string nameProperty);
	void SetValueProperty(std::string nameProperty, int value);

	virtual Entity* getNewEntity() = 0;
	Entity* createEntity(World* world);

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

