#include "Player.h"

Player::Player()
{
	Wf = -7;
	moveSpeed = 7;
	rect->Size = glm::vec2(Block::sizeBlock, Block::sizeBlock * 2);
}

Entity* Player::getNewEntity()
{
	return new Player;
}
