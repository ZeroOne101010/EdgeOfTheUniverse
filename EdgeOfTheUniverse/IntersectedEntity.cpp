#include "World.h"
#include "IntersectedEntity.h"

//float IntersectedEntity::G = 0.003f;
float IntersectedEntity::G = 0.003f;
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
        pX = (int)abs(Position.x) % Block::sizeBlock > 0 ? Position.x / Block::sizeBlock - 1 : Position.x / Block::sizeBlock;
    }
    else pX = Position.x / Block::sizeBlock;


    int pY = 0;
    if (Position.y < 0)
    {
        pY = (int)abs(Position.y) % Block::sizeBlock > 0 ? Position.y / Block::sizeBlock - 1 : Position.y / Block::sizeBlock;
    }
    else pY = Position.y / Block::sizeBlock;

    glm::vec2 sizeEntityInBlockSize = glm::vec2((int)(size.x / Block::sizeBlock), (int)(size.y / Block::sizeBlock));

    for (int x = 0; x < sizeEntityInBlockSize.x; x++)
        for (int y = 0; y < sizeEntityInBlockSize.y; y++)
        {
            int blockX = pX + (x - sizeEntityInBlockSize.x / 2);
            int blockY = pY + (y - sizeEntityInBlockSize.y / 2);
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

                        float offsetTileX = abs(dVelocity.x);
                        float offsetTileY = abs(dVelocity.y);
                        if (entityRect.positionX < blockRect.positionX + blockRect.sizeX - offsetTileX && entityRect.positionX + entityRect.sizeX - offsetTileX > blockRect.positionX && entityRect.positionY + entityRect.sizeY <= blockRect.positionY + offsetTileY)
                        {
                            velocity = glm::vec2(velocity.x, 0);
                            float offset = blockRect.positionY - (entityRect.positionY + entityRect.sizeY);
                            Position += glm::vec2(0, offset);
                        }

                        if (entityRect.positionX < blockRect.positionX + blockRect.sizeX - offsetTileX && entityRect.positionX + entityRect.sizeX - offsetTileX > blockRect.positionX&& entityRect.positionY >= blockRect.positionY + blockRect.sizeY - offsetTileY)
                        {
                            velocity = glm::vec2(velocity.x, 1);
                            float offset = (blockRect.positionY + blockRect.sizeY) - entityRect.positionY;
                            Position += glm::vec2(0, offset);
                        }

                        if (entityRect.positionX + entityRect.sizeX <= blockRect.positionX + offsetTileX && entityRect.positionY + offsetTileY < blockRect.positionY + blockRect.sizeY && entityRect.positionY + entityRect.sizeY - offsetTileY > blockRect.positionY)
                        {
                            velocity = glm::vec2(0, velocity.y);
                            float offset = blockRect.positionX - (entityRect.positionX + entityRect.sizeX);
                            Position += glm::vec2(offset, 0);
                        }

                        if (entityRect.positionX >= blockRect.positionX + blockRect.sizeX - offsetTileX && entityRect.positionY + offsetTileY < blockRect.positionY + blockRect.sizeY && entityRect.positionY + entityRect.sizeY - offsetTileY > blockRect.positionY)
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

