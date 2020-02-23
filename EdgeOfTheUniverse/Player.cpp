#include "Player.h"

Player::Player()
{
	mainInventory = new Inventory(20);
	inventories.push_back(mainInventory);
	Wf = -10;
	moveSpeed = 7;
	rect->Size = glm::vec2(Block::sizeBlock, Block::sizeBlock * 2);
}

Entity* Player::getNewEntity()
{
	return new Player;
}

Alterable Player::draw(Renderer* renderer, Alterable alters)
{
	InventoredMob::draw(renderer, alters);
	return alters;
}
