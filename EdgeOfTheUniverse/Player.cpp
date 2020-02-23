#include "Player.h"

Player::Player()
{
	mainInventory = new Inventory(rect);
	inventories.push_back(mainInventory);
	Wf = -10;
	moveSpeed = 7;
	rect->Size = glm::vec2(Block::sizeBlock, Block::sizeBlock * 2);
}

Entity* Player::getNewEntity()
{
	return new Player;
}
