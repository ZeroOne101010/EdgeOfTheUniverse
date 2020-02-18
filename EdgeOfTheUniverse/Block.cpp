#include "World.h"
#include "Block.h"
const int Block::sizeBlock = 21;

Block::Block()
{
	world = nullptr;
}

Block::~Block()
{
	if (rect != nullptr)
	{
		delete rect;
	}
}


Block* Block::createBlock(int pX, int pY, bool isBackBlock, World* world)
{
	Block* block = getNewBlock();
	block->id = id;
	block->pX = pX;
	block->pY = pY;
	block->isBackBlock = isBackBlock;
	block->world = world;
	//block->Position = vec2(pX * sizeBlock , pY * sizeBlock);
	return block;
}

void Block::updateTextureBlock()
{
	if (!isUpdatedTexture)
	{
		rect = new RectangleShape(sizeBlock, sizeBlock);
		rect->optimizeMode = optimizeMode;
		rect->Position = vec2(pX * sizeBlock, pY * sizeBlock);
		rect->textureRect = textureRect;
		isUpdatedTexture = true;
		rect->texture = texture;
		rect->Color = color;
	}
}

void Block::update()
{
	//Здесь пока пусто :3
}

void Block::start()
{
	//Здесь пока пусто :3
}

void Block::draw(Renderer* renderer, Alterable alters)
{
	alters *= *this;
	updateTextureBlock();
	renderer->draw(rect, alters);
}

Block* Block::addProperty(int value, int sizeProperty, std::string nameProperty)
{
	propertyManager.addProperty(value, sizeProperty, nameProperty);
	return this;
}

int Block::getValueProperty(std::string nameProperty)
{
	return propertyManager.getValueProperty(nameProperty);
}

void Block::setValueProperty(std::string nameProperty, int value)
{
	propertyManager.setValueProperty(nameProperty, value);;
}
