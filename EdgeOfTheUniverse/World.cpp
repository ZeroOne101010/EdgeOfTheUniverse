#include "Map.h"
#include"Game.h"
#include "World.h"

#define OFFSET_CHUNK_DRAW 2
#define OFFSET_BLOCK_DRAW_X 2
#define OFFSET_BLOCK_DRAW_Y 2

const int World::countActiveChunks = 100;

World::World(int seed, Map* map)
{
    this->seed = seed;
    this->map = map;
    countChunks = 0;
    chunk = new Chunk * [countActiveChunks];
    int size = 0;
    for (int x = 0; x < countActiveChunks; x++)
    {
        chunk[x] = nullptr;
    }

    //for (int x = countActiveChunks - 1; x >= 0; x--)
    //{
    //    chunk[x] = ConvertRegionData::getChunkFromDataRegion(x, 0, this);
    //}

    //chunk[0] = new Chunk(this, 0, 0);
    //ConvertRegionData::saveChunkDataToRegion(chunk[0], this);
    //chunk[1] = ConvertRegionData::getChunkFromDataRegion(37, 0, this);
    //int k = 0;

 //   for (int x = 0; x < countActiveChunks; x++)
 //   {
 //       chunk[x] = nullptr;
 //   }
 //   camera = vec2(Chunk::sizeChunk * Block::sizeBlock * 2, 0);
    ////chunk[0] = new Chunk(this, 0, 0);
 //   //chunk[0] = getChunk(0, 0);
 //   //chunkPointer++;

    //6setBlocks(0, 0, 10, 10, 2, false);
    //setBlock(0, 0, false, 2);
}

World::~World()
{

    for (int x = 0; x < countActiveChunks; x++)
    {
        if (chunk[x] != nullptr)
        {
            //if (chunk[x]->chunkX == 0 && chunk[x]->chunkY == 0)
            //{
            //    for (int y = 0; y < Chunk::sizeChunk; y++)
            //    {
            //        for (int z = 0; z < Chunk::sizeChunk; z++)
            //        {
            //            std::cout << chunk[x]->block[z][y]->id;
            //        }
            //        std::cout << std::endl;
            //    }
            //}
            ConvertRegionData::saveChunkDataToRegion(chunk[x], this);
        }
    }
    for (int x = 0; x < countActiveChunks; x++)
    {
        if (chunk[x] != nullptr) delete chunk[x];
    }
}

Entity* World::addEntity(int posX, int posY, int id)
{
    Entity* localEntity = RegisteryEntity::createEntity(this, id);
    localEntity->Position = glm::vec2(posX, posY);
    entity.push_back(localEntity);
    return localEntity;
}

Chunk* World::generationChunk(int chunkX, int chunkY)
{
    return new Chunk(this, chunkX, chunkY);
}

Chunk** World::getChunk(int chunkX, int chunkY)
{

    Chunk** localChunk = nullptr;
    bool chunkFinded = false;

    for (int x = 0; x < countActiveChunks; x++)
    {
        if (chunk[x] != nullptr)
        {
            if (chunkX == chunk[x]->chunkX && chunkY == chunk[x]->chunkY)
            {
                localChunk = &chunk[x];
                chunkFinded = true;
                break;
            }
        }
    }

    if (chunkFinded == false)
    {
        map->chunkThread->addChunkContainer(chunkX, chunkY, this);
    }
    return localChunk;
}

Chunk** World::getChunkWithoutThread(int chunkX, int chunkY)
{
    Chunk* localChunk = nullptr;
    Chunk** ptrActiveChunk = nullptr;
    bool chunkFinded = false;

    //localChunk = chunkTable[new Vector2f(chunkX, chunkY)] as Chunk;

    for (int x = 0; x < countActiveChunks; x++)
    {
        if (chunk[x] != nullptr)
        {
            if (chunkX == chunk[x]->chunkX && chunkY == chunk[x]->chunkY)
            {
                localChunk = chunk[x];
                ptrActiveChunk = &chunk[x];
                chunkFinded = true;
                break;
            }
        }
    }

    if (chunkFinded == false)
    {
        localChunk = ConvertRegionData::getChunkFromDataRegion(chunkX, chunkY, this);

        if (localChunk == nullptr)
        {
            localChunk = generationChunk(chunkX, chunkY);
        }

        chunkPointer++;
        if (chunkPointer > countActiveChunks - 1)
        {
            chunkPointer = 0;
        }

        float chunkPointerFinded = false;

        while (!chunkPointerFinded)
        {
            if (chunk[chunkPointer] == nullptr)
            {
                chunkPointerFinded = true;
            }
            else if (chunk[chunkPointer]->chunkX < rendererChunkX || chunk[chunkPointer]->chunkX > rendererChunkX + rendererCountChunksInCameraX ||
                chunk[chunkPointer]->chunkY < rendererChunkY || chunk[chunkPointer]->chunkY > rendererChunkY + rendererCountChunksInCameraY)
            {
                    chunkPointerFinded = true;
            }
            else
            {
                chunkPointer++;
                if (chunkPointer > countActiveChunks - 1)
                {
                    chunkPointer = 0;
                }
            }
        }

        if (chunk[chunkPointer] != nullptr)
        {
            ConvertRegionData::saveChunkDataToRegion(chunk[chunkPointer], this);
            delete chunk[chunkPointer];

            chunk[chunkPointer] = localChunk;
            ptrActiveChunk = &chunk[chunkPointer];
        }
        else
        {
            chunk[chunkPointer] = localChunk;
            ptrActiveChunk = &chunk[chunkPointer];
        }

    }

    return ptrActiveChunk;

}

Chunk** World::getChunkByBlockPosition(int posX, int posY)
{
    Chunk** localChunk = nullptr;

    int chunkX = 0;
    int chunkY = 0;

    if (posX < 0)
    {
        if (abs(posX * 1.00f / Chunk::sizeChunk) - abs(posX / Chunk::sizeChunk) > 0)
        {
            chunkX = posX / Chunk::sizeChunk - 1;
        }
        else
        {
            chunkX = posX / Chunk::sizeChunk;
        }
    }
    else
    {
        chunkX = posX / Chunk::sizeChunk;
    }


    if (posY < 0)
    {
        if (abs(posY * 1.00f / Chunk::sizeChunk) - abs(posY / Chunk::sizeChunk) > 0)
        {
            chunkY = posY / Chunk::sizeChunk - 1;
        }
        else
        {
            chunkY = posY / Chunk::sizeChunk;
        }
    }
    else
    {
        chunkY = posY / Chunk::sizeChunk;
    }

    localChunk = getChunk(chunkX, chunkY);

    return localChunk;
}

Block** World::getBlockByBlockPosition(int posX, int posY, bool isBackBlock)
{

    Chunk** localChunk = getChunkByBlockPosition(posX, posY);

    if (localChunk != nullptr)
    {
        int blockX = 0;
        int blockY = 0;

        if ((*localChunk)->chunkX < 0)
        {
            blockX = abs((*localChunk)->chunkX * Chunk::sizeChunk) - abs(posX);
        }
        else
        {
            blockX = posX - (*localChunk)->chunkX * Chunk::sizeChunk;
        }




        if ((*localChunk)->chunkY < 0)
        {
            blockY = abs((*localChunk)->chunkY * Chunk::sizeChunk) - abs(posY);
        }
        else
        {
            blockY = posY - (*localChunk)->chunkY * Chunk::sizeChunk;
        }

        if (isBackBlock)
        {
            return &(*localChunk)->backBlock[blockX][blockY];
        }
        else
        {
            return &(*localChunk)->block[blockX][blockY];
        }
    }
    else
    {
        return nullptr;
    }

}

void World::setBlock(int blockX, int blockY, int id, bool isBackBlock)
{
    Chunk** chunk = getChunkWithoutThread(blockX / Chunk::sizeChunk, blockY / Chunk::sizeChunk);
    int blockInChunkX = blockX % Chunk::sizeChunk;
    int blockInChunkY = blockY % Chunk::sizeChunk;

    if (!isBackBlock)
    {
        (*chunk)->block[blockInChunkX][blockInChunkY] = RegisteryBlocks::createBlock((*chunk)->chunkX * Chunk::sizeChunk + blockInChunkX, (*chunk)->chunkY * Chunk::sizeChunk + blockInChunkY, false, this, id);
    }
    else
    {
        (*chunk)->backBlock[blockInChunkX][blockInChunkY] = RegisteryBlocks::createBlock((*chunk)->chunkX * Chunk::sizeChunk + blockInChunkX, (*chunk)->chunkY * Chunk::sizeChunk + blockInChunkY, false, this, id);
    }
}

void World::setBlocks(int blockX, int blockY, int width, int height, int id, bool isBackBlock)
{
    for (int x = blockX; x < blockX + width; x++)
        for (int y = blockY; y < blockY + height; y++)
        {
            setBlock(x, y, id, isBackBlock);
        }
}

void World::updateCloseChunk(Chunk* chunk)
{
    chunk->updateCloseBlocks();
    std::vector<Entity*> entityInChunk;
    ConvertChunkToData::getCountEntitys(chunk, this, &entityInChunk);
    for (int x = 0; x < entityInChunk.size(); x++)
    {
        ICloseObject* closeObject = dynamic_cast<ICloseObject*>(entityInChunk[x]);
        if (closeObject != nullptr)
        {
            closeObject->updateObject();
        }
    }
    delete chunk;
    //�������� entity �� ���������, �� ��� ���������� � ����������� ~vector
}

void World::rendererBlock(Block* block, Renderer* renderer, Alterable alters)
{
    block->updateTextureBlock();
    renderer->draw(block->rect, alters);
}

//void World::renderChunk(Renderer* renderer, Alterable alters)
//{
//    for (int i = 0; i < chunkRendererSize; i++)
//    {
//        if (chunkRenderer[i] != nullptr)
//            if (*(chunkRenderer[i]) != nullptr)
//            {
//                int chunkBlockXToRender = 0;
//                int chunkBlockYToRender = 0;
//
//                int chunkMaxBlockXToRenderer = Chunk::sizeChunk;
//                int chunkMaxBlockYToRenderer = Chunk::sizeChunk;
//
//                /*int chunkBlockX = (*(chunkRenderer[i]))->chunkX * Chunk::sizeChunk;
//                int chunkBlockY = (*(chunkRenderer[i]))->chunkY * Chunk::sizeChunk;*/
//                int chunkBlockX = 0;
//                int chunkBlockY = 0;
//
//                int maxPositionCameraBlockX = 0;
//                int maxPositionCameraBlockY = 0;
//
//
//
//                for (int x = 0; x < 30; x++)
//                    for (int y = 0; y < 30; y++)
//                    {
//                        renderer->draw((*(chunkRenderer[i]))->block[x][y], alters);
//                    }
//
//
//            }
//    }
//}

void World::draw(Renderer* renderer, Alterable alters)
{
    alters *= *this;

    float speed = 20;

    if (RenderWindow::getKeyState(GLFW_KEY_W))
    {
        camera += vec2(0, -speed);
    }
    else if (RenderWindow::getKeyState(GLFW_KEY_S))
    {
        camera += vec2(0, speed);
    }

    if (RenderWindow::getKeyState(GLFW_KEY_D))
    {
        camera += vec2(speed, 0);
    }
    else if (RenderWindow::getKeyState(GLFW_KEY_A))
    {
        camera += vec2(-speed, 0);
    }



    vec2 sizeCamera = vec2(RenderWindow::width, RenderWindow::height);
    leftTopAngleCamera = camera - vec2(sizeCamera.x / 2, sizeCamera.y / 2);

    if (oldWidth - sizeCamera.x != 0 || oldHeight - sizeCamera.y != 0)
    {
        RenderWindow::changeWindow = true;
        oldWidth = sizeCamera.x;
        oldHeight = sizeCamera.y;

        rendererBlockX = leftTopAngleCamera.x / Block::sizeBlock;
        rendererBlockY = leftTopAngleCamera.y / Block::sizeBlock;

        rendererChunkX = rendererBlockX / Chunk::sizeChunk;
        rendererChunkY = rendererBlockY / Chunk::sizeChunk;

        rendererCountBlocksInCameraX = oldWidth / Block::sizeBlock + OFFSET_BLOCK_DRAW_X * 2;
        rendererCountBlocksInCameraY = oldHeight / Block::sizeBlock + OFFSET_BLOCK_DRAW_Y * 2;

        rendererCountChunksInCameraX = rendererCountBlocksInCameraX / Chunk::sizeChunk + OFFSET_CHUNK_DRAW;
        rendererCountChunksInCameraY = rendererCountBlocksInCameraY / Chunk::sizeChunk + OFFSET_CHUNK_DRAW;

        delete[chunkRendererSize] chunkRenderer;

        chunkRendererSize = rendererCountChunksInCameraX * rendererCountChunksInCameraY;

        chunkRenderer = new Chunk * *[chunkRendererSize];
    }

    map->chunkThread->threadLocator.lock();
    rendererBlockX = leftTopAngleCamera.x / Block::sizeBlock - OFFSET_BLOCK_DRAW_X;
    rendererBlockY = leftTopAngleCamera.y / Block::sizeBlock - OFFSET_BLOCK_DRAW_Y;

    rendererChunkX = rendererBlockX / Chunk::sizeChunk;
    rendererChunkY = rendererBlockY / Chunk::sizeChunk;
    map->chunkThread->threadLocator.unlock();

    if (rendererChunkX <= 0)
    {
        rendererChunkX--;
    }

    if (rendererChunkY <= 0)
    {
        rendererChunkY--;
    }

    int id = 0;
    int maxChunkX = rendererChunkX + rendererCountChunksInCameraX;
    int maxChunkY = rendererChunkY + rendererCountChunksInCameraY;

    for (int x = rendererChunkX; x < maxChunkX; x++)
        for (int y = rendererChunkY; y < maxChunkY; y++)
        {
            chunkRenderer[id] = getChunk(x, y);
            id++;
        }

    int maxBlockXInCamera = rendererBlockX + rendererCountBlocksInCameraX;
    int maxBlockYInCamera = rendererBlockY + rendererCountBlocksInCameraY;

    for (int x = 0; x < chunkRendererSize; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
            for (int z = 0; z < Chunk::sizeChunk; z++)
            {
                if (chunkRenderer[x] != nullptr)
                {
                    if (*chunkRenderer[x] != nullptr)
                    {
                        Block* block = (*chunkRenderer[x])->block[y][z];
                        Block* backBlock = (*chunkRenderer[x])->backBlock[y][z];
                        if (block != nullptr)
                        {
                            if (block->pX > rendererBlockX && block->pX < maxBlockXInCamera)
                            {
                                if (block->pY > rendererBlockY && block->pY < maxBlockYInCamera)
                                {
                                    if (backBlock != nullptr)
                                    {
                                        backBlock->updateTextureBlock();
                                        rendererBlock(backBlock, renderer, alters);
                                    }

                                    block->updateTextureBlock();
                                    rendererBlock(block, renderer, alters);
                                }
                            }
                        }
                    }
                }
            }


    Position = -leftTopAngleCamera;
}
