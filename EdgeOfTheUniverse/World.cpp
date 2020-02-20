#include "Map.h"
#include"Game.h"
#include "RegisteryBiome.h"
#include "World.h"

#define OFFSET_CHUNK_DRAW 2
#define OFFSET_BLOCK_DRAW_X 2
#define OFFSET_BLOCK_DRAW_Y 2

const int World::countActiveChunks = 100;

World::World(int seed, Map* map)
{
    rand = new RandomCoor(10000, seed);
    this->seed = seed;
    this->map = map;
    countChunks = 0;
    chunk = new Chunk * [countActiveChunks];
    int size = 0;
    for (int x = 0; x < countActiveChunks; x++)
    {
        chunk[x] = nullptr;
    }

    //for (int x = 0; x < 28; x++)
    //{
    //    if (x == 26)
    //    {
    //        int k = 1;
    //    }
    //    chunk[x] = new Chunk(this, x, 0);
    //    ConvertRegionData::saveChunkDataToRegion(chunk[x], this);
    //}

    //int k = 1;

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

    //setBlocks(0, 0, 10, 10, 2, false);
    //setBlock(0, 0, false, 2);
}

World::~World()
{

    for (int x = 0; x < countActiveChunks; x++)
    {
        if (chunk[x] != nullptr)
        {
            if (chunk[x]->chunkX == 0 && chunk[x]->chunkY == 0)
            {
                int k = 1;
            }
            ConvertRegionData::saveChunkDataToRegion(chunk[x], this);
        }
    }
    for (int x = 0; x < countActiveChunks; x++)
    {
        if (chunk[x] != nullptr) delete chunk[x];
    }
    delete rand;
    delete defaulBiome;
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
    Chunk* chunk = nullptr;
    chunk = getChunkBiome(chunkX, chunkY)->generateChunk(chunkX, chunkY, this);
    return chunk;
}

void World::addBiome(Biome* biome)
{
    biome->id = this->biome.size() + 1;
    this->biome.push_back(biome);
}

Biome* World::getChunkBiome(int chunkX, int chunkY)
{
    Biome* findedBiome = defaulBiome;

    int maxHigh = 0;

    for (int x = 0; x < biome.size(); x++)
    {
        if (biome[x]->toSpawnBiome(chunkX, chunkY, this->rand))
        {
            findedBiome = biome[x];
        }
    }
    return findedBiome;
}

Biome* World::getBlockBiome(int posX, int posY)
{
    int chunkX = 0;
    int chunkY = 0;

    if (posX < 0)
    {
        posX = abs(posX) % Chunk::sizeChunk > 0 ? chunkX = posX / Chunk::sizeChunk - 1 : chunkX = posX / Chunk::sizeChunk;
    }
    else
    {
        chunkX = posX / Chunk::sizeChunk;
    }


    if (posY < 0)
    {
        posY = abs(posY) % Chunk::sizeChunk > 0 ? chunkY = posY / Chunk::sizeChunk - 1 : chunkY = posY / Chunk::sizeChunk;
    }
    else
    {
        chunkX = posX / Chunk::sizeChunk;
    }

    int rpX = posX - chunkX * Chunk::sizeChunk;
    int rpY = posY - chunkY * Chunk::sizeChunk;


    Biome* biomeUp = getChunkBiome(chunkX, chunkY - 1);
    Biome* biomeRight = getChunkBiome(chunkX + 1, chunkY);
    Biome* biomeDown = getChunkBiome(chunkX, chunkY + 1);
    Biome* biomeLeft = getChunkBiome(chunkX - 1, chunkY);

    Biome* centreBiome = getChunkBiome(chunkX, chunkY);

    int side = 4;

    if (rpY < biomeUp->offsetSmoothBorder)
    {
        if (centreBiome->id < biomeUp->id)
        {
            side = 0;
        }
    }
    else if (rpX > Chunk::sizeChunk - biomeRight->offsetSmoothBorder)
    {
        if (centreBiome->id < biomeRight->id)
        {
            side = 1;
        }
    }
    else if (rpY > Chunk::sizeChunk - biomeDown->offsetSmoothBorder)
    {
        if (centreBiome->id < biomeDown->id)
        {
            side = 2;
        }
    }
    else if (rpX < biomeLeft->offsetSmoothBorder)
    {
        if (centreBiome->id < biomeLeft->id)
        {
            side = 3;
        }
    }

    Biome* biome = centreBiome;

    if (side == 0)
    {
        biome = biomeUp;
    }
    else if (side == 1)
    {
        biome = biomeRight;
    }
    else if (side == 2)
    {
        biome = biomeDown;
    }
    else if (side == 3)
    {
        biome = biomeLeft;
    }

    return biome;
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

Chunk** World::getChunkWithoutThreadByBlockPosition(int blockX, int blockY)
{
    int chunkX = 0;
    int chunkY = 0;
    if (blockX < 0)
    {
        chunkX = abs(blockX) % Chunk::sizeChunk > 0 ? blockX / Chunk::sizeChunk - 1 : blockX / Chunk::sizeChunk;
    }
    else
    {
        chunkX = blockX / Chunk::sizeChunk;
    }

    if (blockY < 0)
    {
        chunkY = abs(blockY) % Chunk::sizeChunk > 0 ? blockY / Chunk::sizeChunk - 1 : blockY / Chunk::sizeChunk;
    }
    else
    {
        chunkY = blockY / Chunk::sizeChunk;
    }
    Chunk** chunk = getChunkWithoutThread(chunkX, chunkY);
    return chunk;
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

Chunk** World::getChunkNotGeneration(int chunkX, int chunkY)
{
    Chunk** localChunk = nullptr;

    for (int x = 0; x < countActiveChunks; x++)
    {
        if (chunk[x] != nullptr)
        {
            if (chunkX == chunk[x]->chunkX && chunkY == chunk[x]->chunkY)
            {
                localChunk = &chunk[x];
                break;
            }
        }
    }


    return localChunk;
}

Chunk** World::getChunkByBlockPositionNotGenerationWithoutThread(int blockX, int blockY)
{
    int chunkX = 0;
    int chunkY = 0;
    if (blockX < 0)
    {
        chunkX = abs(blockX) % Chunk::sizeChunk > 0 ? blockX / Chunk::sizeChunk - 1 : blockX / Chunk::sizeChunk;
    }
    else
    {
        chunkX = blockX / Chunk::sizeChunk;
    }

    if (blockY < 0)
    {
        chunkY = abs(blockY) % Chunk::sizeChunk > 0 ? blockY / Chunk::sizeChunk - 1 : blockY / Chunk::sizeChunk;
    }
    else
    {
        chunkY = blockY / Chunk::sizeChunk;
    }
    Chunk** chunk = getChunkWithoutThreadNotGeneration(chunkX, chunkY);
    return chunk;
}

Chunk** World::getChunkWithoutThreadNotGeneration(int chunkX, int chunkY)
{
    Chunk** localChunk = nullptr;
    for (int x = 0; x < countActiveChunks; x++)
    {
        if (chunk[x] != nullptr)
        {
            if (chunkX == chunk[x]->chunkX && chunkY == chunk[x]->chunkY)
            {
                localChunk = &chunk[x];
                break;
            }
        }
    }
    return localChunk;
}

Chunk** World::getChunkByBlockPositionNotGeneration(int posX, int posY) // Самое длинное слово в мире XD
{
    Chunk** localChunk = nullptr;

    int chunkX = 0;
    int chunkY = 0;

    if (posX < 0)
    {
        chunkX = (abs(posX) % Chunk::sizeChunk) > 0 ? posX / Chunk::sizeChunk - 1 : posX / Chunk::sizeChunk;
    }
    else
    {
        chunkX = posX / Chunk::sizeChunk;
    }


    if (posY < 0)
    {
        chunkY = (abs(posY) % Chunk::sizeChunk) > 0 ? posY / Chunk::sizeChunk - 1 : posY / Chunk::sizeChunk;
    }
    else
    {
        chunkY = posY / Chunk::sizeChunk;
    }

    localChunk = getChunkWithoutThreadNotGeneration(chunkX, chunkY);

    return localChunk;
}

Block** World::getBlockNotGeneration(int posX, int posY, bool isBackBlock)
{
    Chunk** chunk = getChunkByBlockPositionNotGeneration(posX, posY);
    if (chunk != nullptr)
    {
        int blockInChunkX = 0;
        int blockInChunkY = 0;


        if (posX < 0)
        {
            //blockInChunkX = abs(posX) % Chunk::sizeChunk > 0 ? Chunk::sizeChunk - (abs(posX) % Chunk::sizeChunk) : 0;
            blockInChunkX = abs((*chunk)->chunkX * Chunk::sizeChunk) - abs(posX);
        }
        else
        {
            blockInChunkX = posX - (*chunk)->chunkX * Chunk::sizeChunk;
        }


        if (posY < 0)
        {
            //blockInChunkY = Chunk::sizeChunk - (abs(posY) % Chunk::sizeChunk) - 1;
            blockInChunkY = abs((*chunk)->chunkY * Chunk::sizeChunk) - abs(posY);
        }
        else
        {
            blockInChunkY = posY - (*chunk)->chunkY * Chunk::sizeChunk;
        }

        Block** block = &(*chunk)->block[blockInChunkX][blockInChunkY];
        if (block != nullptr)
        {
            if (!isBackBlock)
            {
                return &(*chunk)->block[blockInChunkX][blockInChunkY];
            }
            else
            {
                return &(*chunk)->backBlock[blockInChunkX][blockInChunkY];
            }
        }
    }
    else
    {
        return nullptr;
    }
}

void World::setBlock(int blockX, int blockY, int id, bool isBackBlock)
{
    Chunk** chunk = getChunkWithoutThreadByBlockPosition(blockX, blockY);
    if (chunk != nullptr)
    {
        int blockInChunkX = 0;
        int blockInChunkY = 0;


        if (blockX < 0)
        {
            //blockInChunkX = abs(posX) % Chunk::sizeChunk > 0 ? Chunk::sizeChunk - (abs(posX) % Chunk::sizeChunk) : 0;
            blockInChunkX = abs((*chunk)->chunkX * Chunk::sizeChunk) - abs(blockX);
        }
        else
        {
            blockInChunkX = blockX - (*chunk)->chunkX * Chunk::sizeChunk;
        }


        if (blockY < 0)
        {
            //blockInChunkY = Chunk::sizeChunk - (abs(posY) % Chunk::sizeChunk) - 1;
            blockInChunkY = abs((*chunk)->chunkY * Chunk::sizeChunk) - abs(blockY);
        }
        else
        {
            blockInChunkY = blockY - (*chunk)->chunkY * Chunk::sizeChunk;
        }


        Block* block = (*chunk)->block[blockInChunkX][blockInChunkY];

        int pX = blockX;
        int pY = blockY;

        Block*** b = new Block**[8];
        b[0] = getBlockNotGeneration(pX, pY - 1, isBackBlock);
        b[1] = getBlockNotGeneration(pX + 1, pY - 1, isBackBlock);
        b[2] = getBlockNotGeneration(pX + 1, pY, isBackBlock);
        b[3] = getBlockNotGeneration(pX + 1, pY + 1, isBackBlock);
        b[4] = getBlockNotGeneration(pX, pY + 1, isBackBlock);
        b[5] = getBlockNotGeneration(pX - 1, pY + 1, isBackBlock);
        b[6] = getBlockNotGeneration(pX - 1, pY, isBackBlock);
        b[7] = getBlockNotGeneration(pX - 1, pY - 1, isBackBlock);

        for (int x = 0; x < 8; x++)
        {
            if (b[x] != nullptr)
            {
                (*b[x])->isUpdatedViewTexture = false;
            }
        }

        if (block != nullptr)
        {
            if (!isBackBlock)
            {
                delete (*chunk)->block[blockInChunkX][blockInChunkY];
                (*chunk)->block[blockInChunkX][blockInChunkY] = RegisteryBlocks::createBlock((*chunk)->chunkX * Chunk::sizeChunk + blockInChunkX, (*chunk)->chunkY * Chunk::sizeChunk + blockInChunkY, false, this, id);
            }
            else
            {
                delete (*chunk)->block[blockInChunkX][blockInChunkY];
                (*chunk)->backBlock[blockInChunkX][blockInChunkY] = RegisteryBlocks::createBlock((*chunk)->chunkX * Chunk::sizeChunk + blockInChunkX, (*chunk)->chunkY * Chunk::sizeChunk + blockInChunkY, false, this, id);
            }
        }
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
    //Удаление entity не требуется, тк это происходит в диструкторе ~vector
}

void World::rendererBlock(Block* block, Renderer* renderer, Alterable alters)
{
    block->updateViewBlock();
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

    double mouseX = 0;
    double mouseY = 0;
    glfwGetCursorPos(map->game->window->window, &mouseX, &mouseY);

    int mousePX = mouseX / Block::sizeBlock + rendererBlockX;
    int mousePY = mouseY / Block::sizeBlock + rendererBlockY;

    int mouseButtonActive = glfwGetMouseButton(map->game->window->window, GLFW_MOUSE_BUTTON_1);

    if (mouseButtonActive == 1)
    {
        Block** block = getBlockNotGeneration(mousePX, mousePY, false);
        if (block != nullptr)
        {
           setBlock(mousePX, mousePY, 2, false);
        }
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
                            if (block->pX > rendererBlockX&& block->pX < maxBlockXInCamera)
                            {
                                if (block->pY > rendererBlockY&& block->pY < maxBlockYInCamera)
                                {
                                    if (backBlock != nullptr)
                                    {
                                        rendererBlock(backBlock, renderer, alters);
                                    }

                                    rendererBlock(block, renderer, alters);
                                }
                            }
                        }
                    }
                }
            }


    Position = -leftTopAngleCamera;
}
