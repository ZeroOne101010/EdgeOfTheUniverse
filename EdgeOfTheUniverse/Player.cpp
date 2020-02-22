#include "Player.h"

Player::Player()
{
	flySpeed = 5;
	rect->Size = glm::vec2(Block::sizeBlock, Block::sizeBlock * 2);
}

Entity* Player::getNewEntity()
{
	return new Player;
}
