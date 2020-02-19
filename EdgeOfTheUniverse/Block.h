#pragma once
#include "Content.h"
#include "AlterableHeader.h"
#include"OpenGLEngine/RectangleShape.h"
#include "PropertyManager.h"

class World;

class Block : public Alterable, public IDraw
{
public:
	Block();
	Block(glm::vec4 color, Texture* texture, FloatRect textureRect);
	~Block();

	static const int sizeBlock;

	glm::vec4 color = glm::vec4(255, 255, 255, 255);
	FloatRect textureRect = FloatRect(0, 0, sizeBlock, sizeBlock);
	Texture* texture = Content::defaultTexture;
	bool isUpdatedTexture = false;
	bool canUpdateTexture = true;
	bool isUpdatedViewTexture = false;
	RectangleShape* rect = nullptr;

	PropertyManager propertyManager;
	bool isBackBlock = false;
	World* world;
	int pX = 0;
	int pY = 0;
	int id;
	bool optimizeMode = true;

	virtual Block* getNewBlock() = 0;
	Block* createBlock(int pX, int pY, bool isBackBlock, World* world);

	void updateTextureBlock();

	virtual void update();
	virtual void start();
	virtual void updateTextureRect();

	//ќбнавл€ет внешность блока(обновл€ет текстурку и т.д)
	void updateViewBlock();

	virtual void draw(Renderer* renderer, Alterable alters) override;
protected:
	Block* addProperty(int value, int sizeProperty, std::string nameProperty);
	int getValueProperty(std::string nameProperty);
	void setValueProperty(std::string nameProperty, int value);

};

