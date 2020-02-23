#include "World.h"
#include "IntersectedEntity.h"

float IntersectedEntity::G = 0.10f;
IntersectedEntity::IntersectedEntity()
{
	
}

void IntersectedEntity::collisionUpdate()
{
    float k = 2;
    glm::vec2 size = rect->Size * 2.0f * k;

    int pX = 0;
    if (Position.x < 0)
    {
        if ((int)abs(Position.x) % Block::sizeBlock > 0)
        {
            pX = (int)abs(Position.x) % Block::sizeBlock > 0 ? Position.x / Block::sizeBlock - 1 : 0;
        }
    }
    else pX = Position.x / Block::sizeBlock;


    int pY = 0;
    if (Position.y < 0)
    {
        if ((int)abs(Position.y) % Block::sizeBlock > 0)
        {
            pY = (int)abs(Position.y) % Block::sizeBlock > 0 ? Position.y / Block::sizeBlock - 1 : 0;
        }
    }
    else pY = Position.y / Block::sizeBlock;


    for (int x = 0; x < size.x; x++)
        for (int y = 0; y < size.y; y++)
        {
            int blockX = pX + x - size.x / 2;
            int blockY = pY + y - size.y / 2;
            Block** checkingBlock = world->getBlockNotGeneration(blockX, blockY, false);
            glm::vec2 blockPosition = glm::vec2(blockX * Block::sizeBlock, blockY * Block::sizeBlock);
            if (checkingBlock != nullptr)
            {
                if ((*checkingBlock)->isCanCollision)
                {
                    FloatRect entityRect = FloatRect(Position - Origin, rect->Size);
                    FloatRect blockRect = FloatRect(blockPosition, glm::vec2(Block::sizeBlock, Block::sizeBlock));
                    if (entityRect.Intersects(blockRect))
                    {
                        glm::vec2 dVelocity = velocity;
                        if (dVelocity.x >= Block::sizeBlock)
                        {
                            dVelocity.x = Block::sizeBlock - 1;
                        }
                        else if (dVelocity.x <= -Block::sizeBlock)
                        {
                            dVelocity.x = -Block::sizeBlock + 1;
                        }

                        if (dVelocity.y >= Block::sizeBlock)
                        {
                            dVelocity.y = Block::sizeBlock - 1;
                        }
                        else if (dVelocity.y <= -Block::sizeBlock)
                        {
                            dVelocity.y = -Block::sizeBlock + 1;
                        }

                        float offsetTileX = abs(dVelocity.x) + 1;
                        float offsetTileY = abs(dVelocity.y) + 1;
                        if (entityRect.positionX < entityRect.positionX + blockRect.sizeX && entityRect.positionX + entityRect.sizeX > blockRect.positionX&& entityRect.positionY + entityRect.sizeY < blockRect.positionY + offsetTileY)
                        {
                            velocity = glm::vec2(velocity.x, 0);
                            float offset = blockRect.positionY - (entityRect.positionY + entityRect.sizeY);
                            Position += glm::vec2(0, offset);
                        }

                        if (entityRect.positionX + offsetTileX < blockRect.positionX + blockRect.sizeX && entityRect.positionX + entityRect.sizeX > blockRect.positionX + offsetTileX && entityRect.positionY > blockRect.positionY + blockRect.sizeY - offsetTileY)
                        {
                            velocity = glm::vec2(velocity.x, 1);
                            float offset = (blockRect.positionY + blockRect.sizeY) - entityRect.positionY;
                            Position += glm::vec2(0, offset);
                        }

                        if (entityRect.positionX + entityRect.sizeX < blockRect.positionX + offsetTileX && entityRect.positionY + offsetTileY < blockRect.positionY + blockRect.sizeY && entityRect.positionY + entityRect.sizeY - offsetTileY > blockRect.positionY)
                        {
                            velocity = glm::vec2(0, velocity.y);
                            float offset = blockRect.positionX - (entityRect.positionX + entityRect.sizeX);
                            Position += glm::vec2(offset, 0);
                        }

                        if (entityRect.positionX > blockRect.positionX + blockRect.sizeX - offsetTileX && entityRect.positionY + offsetTileY < blockRect.positionY + blockRect.sizeY && entityRect.positionY + entityRect.sizeY - offsetTileY > blockRect.positionY)
                        {
                            velocity = glm::vec2(0, velocity.y);
                            float offset = (blockRect.positionX + blockRect.sizeX) - entityRect.positionX;
                            Position += glm::vec2(offset, 0);
                        }
                    }
                }
            }

        }
}


void IntersectedEntity::draw(Renderer* renderer, Alterable alters)
{
 
    velocity.y += G;
    Position += velocity;
    collisionUpdate();
    Entity::draw(renderer, alters);
}

