#include "Map.h"
#include"Game.h"
#include "World.h"

#define CONST_MOD 1
#define OFFSET_DRAW 0

const int World::countActiveChunks = 50;

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


    //setBlock(Chunk::sizeChunk * 2 + 5, 5, 2);
}

World::~World()
{
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

Chunk* World::getChunk(int chunkX, int chunkY)
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

    //if (chunkX == 0 && chunkY == 0)
    //{
    //    int k = 0;
    //}

    //Chunk* localChunk = nullptr;
    //bool chunkFinded = false;

    ////localChunk = chunkTable[new Vector2f(chunkX, chunkY)] as Chunk;

    //for (int x = 0; x < countActiveChunks; x++)
    //{
    //    if (chunk[x] != nullptr)
    //    {
    //        if (chunkX == chunk[x]->chunkX && chunkY == chunk[x]->chunkY)
    //        {
    //            localChunk = chunk[x];
    //            chunkFinded = true;
    //            break;
    //        }
    //    }
    //}

    //if (chunkFinded == false)
    //{
    //    localChunk = ConvertRegionData::getChunkFromDataRegion(chunkX, chunkY, this);

    //    if (localChunk == nullptr)
    //    {
    //        localChunk = generationChunk(chunkX, chunkY);
    //    }

    //    if (chunk[chunkPointer] != nullptr)
    //    {
    //        ConvertRegionData::saveChunkDataToRegion(chunk[chunkPointer], this);
    //        //delete chunk[chunkPointer];
    //        chunk[chunkPointer] = localChunk;
    //    }
    //    else
    //    {
    //        chunk[chunkPointer] = localChunk;
    //    }

    //    chunkPointer++;
    //    if (chunkPointer >= countActiveChunks)
    //    {
    //        chunkPointer = 0;
    //    }

    //}
    if (localChunk != nullptr)
    {
        return *localChunk;
    }
    else
    {
        return nullptr;
    }

}

Chunk* World::getChunkWithoutThread(int chunkX, int chunkY)
{
    Chunk* localChunk = nullptr;
    bool isFiend = false;

    for (int x = 0; x < countActiveChunks; x++)
    {
        if (chunk[x] != nullptr)
        {
            if (chunk[x]->chunkX == chunkX && chunk[x]->chunkY)
            {
                isFiend = true;
                localChunk = chunk[x];
                break;
            }
        }
    }

    if (!isFiend)
    {
        localChunk = ConvertRegionData::getChunkFromDataRegion(chunkX, chunkY, this);
        if (localChunk == nullptr)
        {
            localChunk = generationChunk(chunkX, chunkY);
        }

        if (chunk[chunkPointer] != nullptr)
        {
            delete chunk[chunkPointer];
            chunk[chunkPointer] = localChunk;
        }
        else
        {
            chunk[chunkPointer] = localChunk;
        }

        chunkPointer++;
        if (chunkPointer > countActiveChunks - 1)
        {
            chunkPointer = 0;
        }
    }

    return localChunk;

}

Chunk* World::getChunkByBlockPosition(int posX, int posY)
{
    Chunk* localChunk = nullptr;

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

Block* World::getBlockByBlockPosition(int posX, int posY, bool isBackBlock)
{

    Chunk* localChunk = getChunkByBlockPosition(posX, posY);

    if (localChunk != nullptr)
    {
        int blockX = 0;
        int blockY = 0;

        if (localChunk->chunkX < 0)
        {
            blockX = abs(localChunk->chunkX * Chunk::sizeChunk) - abs(posX);
        }
        else
        {
            blockX = posX - localChunk->chunkX * Chunk::sizeChunk;
        }




        if (localChunk->chunkY < 0)
        {
            blockY = abs(localChunk->chunkY * Chunk::sizeChunk) - abs(posY);
        }
        else
        {
            blockY = posY - localChunk->chunkY * Chunk::sizeChunk;
        }

        if (isBackBlock)
        {
            return localChunk->backBlock[blockX][blockY];
        }
        else
        {
            return localChunk->block[blockX][blockY];
        }
    }
    else
    {
        return nullptr;
    }

}

void World::setBlock(int blockX, int blockY, int id)
{
    Chunk* chunk = getChunkWithoutThread(blockX / Chunk::sizeChunk, blockY / Chunk::sizeChunk);
    int blockInChunkX = blockX % Chunk::sizeChunk;
    int blockInChunkY = blockY % Chunk::sizeChunk;
    chunk->block[blockInChunkX][blockInChunkY] = RegisteryBlocks::createBlock(chunk->chunkX * Chunk::sizeChunk + blockInChunkX, chunk->chunkY * Chunk::sizeChunk + blockInChunkY, false, this, id);
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
    if (block != nullptr)
    {
        renderer->draw(block, alters);
    }
}

void World::renderChunk(Renderer* renderer, Alterable alters)
{
    for (int i = 0; i < chunkRendererSize; i++)
    {
        if (chunkRenderer[i] != nullptr)
        {
            int chunkBlockXToRender = 0;
            int chunkBlockYToRender = 0;

            int chunkMaxBlockXToRenderer = Chunk::sizeChunk;
            int chunkMaxBlockYToRenderer = Chunk::sizeChunk;

            int chunkBlockX = chunkRenderer[i]->chunkX * Chunk::sizeChunk;
            int chunkBlockY = chunkRenderer[i]->chunkY * Chunk::sizeChunk;

            int maxPositionCameraBlockX = rendererBlockX + rendererCountBlocksInCameraX;
            int maxPositionCameraBlockY = rendererBlockY + rendererCountBlocksInCameraY;

            if (chunkBlockX < rendererBlockX)
            {
                chunkBlockXToRender = (int)abs(rendererBlockX) % Chunk::sizeChunk;
            }
            if (chunkBlockY < rendererBlockY)
            {
                chunkBlockYToRender = (int)abs(rendererBlockY) % Chunk::sizeChunk;
            }



            if (chunkBlockX + Chunk::sizeChunk > maxPositionCameraBlockX)
            {
                chunkMaxBlockXToRenderer = (int)abs(maxPositionCameraBlockX) % Chunk::sizeChunk;
            }
            if (chunkBlockY + Chunk::sizeChunk > maxPositionCameraBlockY)
            {
                chunkMaxBlockYToRenderer = (int)abs(maxPositionCameraBlockY) % Chunk::sizeChunk;
            }



            //for (int x = chunkBlockXToRender; x < chunkMaxBlockXToRenderer; x++)
            //    for (int y = chunkBlockYToRender; y < chunkMaxBlockYToRenderer; y++)
            //    {
            //        renderer->draw(chunkRenderer[i]->block[x][y], alters);
            //    }
            for (int x = chunkBlockXToRender; x < chunkMaxBlockXToRenderer; x++)
                for (int y = chunkBlockYToRender; y < chunkMaxBlockYToRenderer; y++)
                {
                    renderer->draw(chunkRenderer[i]->block[x][y], alters);
                }
        }
    }
}

void World::draw(Renderer* renderer, Alterable alters)
{
    alters *= *this;

    float speed = 10;

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

    vec2 sizeCamera = vec2(RenderWindow::width + OFFSET_DRAW, RenderWindow::height + OFFSET_DRAW);
    leftTopAngleCamera = camera - vec2(sizeCamera.x / 2, sizeCamera.y / 2);

    if (oldWidth - sizeCamera.x != 0 || oldHeight - sizeCamera.y != 0)
    {
       /* oldWidth = sizeCamera.x;
        oldHeight = sizeCamera.y;

        rendererCountBlocksInCameraX = sizeCamera.x / Block::sizeBlock;
        rendererCountBlocksInCameraY = sizeCamera.y / Block::sizeBlock;

        blocksToRenderer = new Block ** [rendererCountBlocksInCameraX];
        for (int x = 0; x < rendererCountBlocksInCameraX; x++)
        {
            blocksToRenderer[x] = new Block * [rendererCountBlocksInCameraY];
        }

        std::cout << "kek" << std::endl;*/
        sizeCamera = vec2(RenderWindow::width + OFFSET_DRAW, RenderWindow::height + OFFSET_DRAW);
        leftTopAngleCamera = camera - vec2(sizeCamera.x / 2, sizeCamera.y / 2);

        rendererBlockX = leftTopAngleCamera.x / Block::sizeBlock;
        rendererBlockY = leftTopAngleCamera.y / Block::sizeBlock;

        rendererCountBlocksInCameraX = sizeCamera.x / Block::sizeBlock;
        rendererCountBlocksInCameraY = sizeCamera.y / Block::sizeBlock;

        rendererChunkX = rendererBlockX / Chunk::sizeChunk;
        rendererChunkY = rendererBlockY / Chunk::sizeChunk;
        //Вместо того, чтобы использовать % для более точного определения размера экрана, эффективней просто прибавлять еденицу( а ещё так меньше писать) )
        //В качестве еденицы я создал макрос CONST_MOD, шоб не запутаться :D
        rendererCountChunksInCameraX = rendererCountBlocksInCameraX / Chunk::sizeChunk + CONST_MOD;
        rendererCountChunksInCameraY = rendererCountBlocksInCameraY / Chunk::sizeChunk + CONST_MOD;

        chunkRendererSize = rendererCountChunksInCameraX * rendererCountChunksInCameraY;
        chunkRenderer = new Chunk *[rendererCountChunksInCameraX];

    }

    leftTopAngleCamera = camera - vec2(sizeCamera.x / 2, sizeCamera.y / 2);

    rendererChunkX = leftTopAngleCamera.x / (Chunk::sizeChunk * Block::sizeBlock);
    rendererChunkY = leftTopAngleCamera.y / (Chunk::sizeChunk * Block::sizeBlock);

    int id = 0;

    //for(int x = 0; x < rendererCountChunksInCameraX; x++)
    //    for (int y = 0; y < rendererCountChunksInCameraY; y++)
    //    {
    //        chunkRenderer[id] = getChunkWithoutThread(x + rendererChunkX, y + rendererChunkY);
    //        id++;
    //    }
   
    //Chunk* c[50];

    //for (int x = 0; x < chunkRendererSize; x++)
    //{
    //    c[x] = chunkRenderer[x];
    //}

    //renderChunk(renderer, alters);

    //Position = -leftTopAngleCamera;
}
