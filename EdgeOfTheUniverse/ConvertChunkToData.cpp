#include "Chunk.h"
#include "World.h"
#include "ConvertChunkToData.h"

/* CHUNK DATA:
* 1. Первый биом чанка (2 байта)
* 2. Второй биом чанка (2 байта)
* 3. Параметр 2 биома чанка (2 байта)
* 4. id всех блоков
* 5. Параметры блоков
*/

int ConvertChunkToData::sizeBiome1 = 2;
int ConvertChunkToData::sizeBiome2 = 2;
int ConvertChunkToData::sizeBiome2Info = 2;
int ConvertChunkToData::sizeCountEntity = 1;
int ConvertChunkToData::sizeEntityPos = 3;
int ConvertChunkToData::sizeIdEntity = 1;
int ConvertChunkToData::sizeIdBlock = 1;

//Шаг должен быть больше 0!
int ConvertChunkToData::getValueFromData(unsigned long address, unsigned long offset, unsigned char* data, int stride)
{
    address *= stride;
    offset *= stride;
    unsigned char* code = new unsigned char[offset];
    //13487571
    //124434
    for (int x = 0; x < offset; x++)
    {
        code[x] = data[address + x];
    }
    int value = ByteHelper::set256To10(code, offset);
    delete[offset] code;
    return value;
}

//Шаг должен быть больше 0!
void ConvertChunkToData::setValueForData(unsigned long value, unsigned long address, unsigned long offset, unsigned char* data, int stride)
{
    address *= stride;
    offset *= stride;
    unsigned char* code = new unsigned char[offset];
    int size = 0;
    unsigned char* gotCode = ByteHelper::set10To256(value, size);
    for (int x = 0; x < size; x++)
    {
        code[offset - size + x] = gotCode[x];
    }
    for (int x = 0; x < offset - size; x++)
    {
        code[x] = 0;
    }

    for (int x = 0; x < offset; x++)
    {
        data[address + x] = code[x];
    }
    delete[offset] code;
    delete[size] gotCode;
}

int ConvertChunkToData::getSizePropertys(Chunk* chunk, bool isBackBlock)
{
    int sizePropertys = 0;
    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            if (isBackBlock)
            {

                sizePropertys += chunk->backBlock[x][y]->propertyManager.allSize;
            }
            else
            {
                sizePropertys += chunk->block[x][y]->propertyManager.allSize;
            }
        }
    return sizePropertys;
}

void ConvertChunkToData::converPropertysChunk(Chunk* chunk, int& pointer, bool isBackBlock, unsigned char* data)
{
    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            PropertyManager* propertyManager;

            if (isBackBlock)
            {
                propertyManager = &chunk->backBlock[x][y]->propertyManager;
            }
            else
            {
                propertyManager = &chunk->block[x][y]->propertyManager;
            }

            if (propertyManager->allSize > 0)
            {
                for (int z = 0; z < propertyManager->propertyList.size(); z++)
                {
                    setValueForData(propertyManager->propertyList[z]->value, pointer, propertyManager->propertyList[z]->sizeProperty, data, STRIDE);
                    pointer += propertyManager->propertyList[z]->sizeProperty;
                }
            }
        }
}

int ConvertChunkToData::getCountEntitys(Chunk* chunk, World* world, std::vector<Entity*>* entityInChunk)
{
    int countEntity = 0;

    std::vector<Entity*>* entity = &world->entity;

    for (int x = 0; x < entity->size(); x++)
    {
        if ((*entity)[x]->saveInChunk)
        {
            /////////////////////////////////////////////

            int pX = 0;
            int pY = 0;


            if ((*entity)[x]->Position.x < 0)
            {
                if (abs((*entity)[x]->Position.x / (float)Block::sizeBlock) - abs(((int)(*entity)[x]->Position.x / Block::sizeBlock)) > 0) // Если остаток больше нуля
                {
                    pX = (int)(*entity)[x]->Position.x / Block::sizeBlock - 1;
                }
                else
                {
                    pX = (int)(*entity)[x]->Position.x / Block::sizeBlock;
                }
            }
            else
            {
                pX = (int)(*entity)[x]->Position.x / Block::sizeBlock;
            }


            if ((*entity)[x]->Position.y < 0)
            {
                if (abs((*entity)[x]->Position.y / (float)Block::sizeBlock) - abs((int)((*entity)[x]->Position.y / Block::sizeBlock)) > 0)
                {
                    pY = (int)(*entity)[x]->Position.y / Block::sizeBlock - 1;
                }
                else
                {
                    pY = (int)(*entity)[x]->Position.y / Block::sizeBlock;
                }
            }
            else
            {
                pY = (int)(*entity)[x]->Position.y / Block::sizeBlock;
            }

            /////////////////////////////////////////////

            int chunkX = 0;
            int chunkY = 0;

            if (pX < 0)
            {
                if (abs(pX / (float)Chunk::sizeChunk) - abs((int)(pX / Chunk::sizeChunk)) > 0)
                {
                    chunkX = pX / Chunk::sizeChunk - 1;
                }
                else
                {
                    chunkX = pX / Chunk::sizeChunk;
                }
            }
            else
            {
                chunkX = pX / Chunk::sizeChunk;
            }


            if (pY < 0)
            {
                if (abs(pY / (float)Chunk::sizeChunk) - abs((int)(pY / Chunk::sizeChunk)) > 0)
                {
                    chunkY = pY / Chunk::sizeChunk - 1;
                }
                else
                {
                    chunkY = pY / Chunk::sizeChunk;
                }
            }
            else
            {
                chunkY = pY / Chunk::sizeChunk;
            }

            if (chunkX == chunk->chunkX && chunkY == chunk->chunkY)
            {
                entityInChunk->push_back((*entity)[x]);
            }

        }
    }
    countEntity = entityInChunk->size();

    return countEntity;

}

int ConvertChunkToData::getSizePropertysEntity(std::vector<Entity*>* entityInChunk)
{
    int sizePropertys = 0;
    for (int x = 0; x < entityInChunk->size(); x++)
    {
        Entity* entity = (*entityInChunk)[x];
        int allSizePropertys = entity->propertyManager.allSize;
        sizePropertys += allSizePropertys;
    }
    return sizePropertys;
}

void ConvertChunkToData::convertEntityChunk(Chunk* chunk, std::vector<Entity*>* entityInChunk, int& pointer, World* world, unsigned char* data)
{
    int countEntity = entityInChunk->size();
    setValueForData(countEntity, pointer, sizeCountEntity, data, STRIDE);
    pointer += sizeCountEntity;

    for (int x = 0; x < countEntity; x++)
    {
        int posX = (int)(*entityInChunk)[x]->Position.x;
        setValueForData(posX + (int)(std::pow(2, sizeEntityPos * 8) / 2), pointer, sizeEntityPos, data, STRIDE);
        pointer += sizeEntityPos;

        int posY = (int)(*entityInChunk)[x]->Position.y;
        setValueForData(posY + (int)(std::pow(2, sizeEntityPos * 8) / 2), pointer, sizeEntityPos, data, STRIDE);
        pointer += sizeEntityPos;

        int id = (*entityInChunk)[x]->id;
        setValueForData(id, pointer, sizeIdEntity, data, STRIDE);
        pointer += sizeIdEntity;
    }

    for (int x = 0; x < countEntity; x++)
    {
        Entity* entity = (*entityInChunk)[x];
        for (int y = 0; y < entity->propertyManager.propertyList.size(); y++)
        {
            int sizeProperty = entity->propertyManager.propertyList[y]->sizeProperty;
            int valueProperty = entity->propertyManager.propertyList[y]->value;
            setValueForData(valueProperty, pointer, sizeProperty, data, STRIDE);
            pointer += sizeProperty;
        }
    }
}

unsigned char* ConvertChunkToData::convertChunk(Chunk* chunk, World* world)
{
    int sizePropertysBlock = getSizePropertys(chunk, false);
    int sizePropertysBackBlock = getSizePropertys(chunk, true);
    std::vector<Entity*>* entityInChunk = new std::vector<Entity*>();
    int countEntity = getCountEntitys(chunk, world, entityInChunk);
    int sizePropertysEntity = getSizePropertysEntity(entityInChunk);

    int dataSize = (sizeBiome1 + sizeBiome2 + sizeBiome2Info + Chunk::sizeChunk * Chunk::sizeChunk * 2 + sizePropertysBlock + sizePropertysBackBlock
        + sizeCountEntity + countEntity * (sizeEntityPos * 2 + sizeIdEntity) + sizePropertysEntity) * STRIDE;
    unsigned char* data = new unsigned char[dataSize];

    int biome1 = chunk->biome1;
    int biome2 = chunk->biome2;
    int biome2info = chunk->biome2Info;

    int pointer = 0;

    setValueForData(biome1, pointer, sizeBiome1, data, STRIDE);
    pointer += sizeBiome1;

    setValueForData(biome2, pointer, sizeBiome2, data, STRIDE);
    pointer += sizeBiome2;

    setValueForData(biome2info, pointer, sizeBiome2Info, data, STRIDE);
    pointer += sizeBiome2Info;

    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            setValueForData(chunk->block[x][y]->id, pointer, sizeIdBlock, data, STRIDE);
            pointer += sizeIdBlock;
        }

    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            setValueForData(chunk->backBlock[x][y]->id, pointer, sizeIdBlock, data, STRIDE);
            pointer += sizeIdBlock;
        }

    converPropertysChunk(chunk, pointer, false, data);
    converPropertysChunk(chunk, pointer, true, data);
    convertEntityChunk(chunk, entityInChunk, pointer, world, data);

    return data;
}

unsigned char* ConvertChunkToData::convertChunk(Chunk* chunk, World* world, int& size)
{
    int sizePropertysBlock = getSizePropertys(chunk, false);
    int sizePropertysBackBlock = getSizePropertys(chunk, true);
    std::vector<Entity*>* entityInChunk = new std::vector<Entity*>();
    int countEntity = getCountEntitys(chunk, world, entityInChunk);
    int sizePropertysEntity = getSizePropertysEntity(entityInChunk);

    int dataSize = (sizeBiome1 + sizeBiome2 + sizeBiome2Info + Chunk::sizeChunk * Chunk::sizeChunk * 2 + sizePropertysBlock + sizePropertysBackBlock
        + sizeCountEntity + countEntity * (sizeEntityPos * 2 + sizeIdEntity) + sizePropertysEntity) * STRIDE;
    unsigned char* data = new unsigned char[dataSize];

    size = dataSize;

    int biome1 = chunk->biome1;
    int biome2 = chunk->biome2;
    int biome2info = chunk->biome2Info;

    int pointer = 0;

    setValueForData(biome1, pointer, sizeBiome1, data, STRIDE);
    pointer += sizeBiome1;

    setValueForData(biome2, pointer, sizeBiome2, data, STRIDE);
    pointer += sizeBiome2;

    setValueForData(biome2info, pointer, sizeBiome2Info, data, STRIDE);
    pointer += sizeBiome2Info;

    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            setValueForData(chunk->block[x][y]->id, pointer, sizeIdBlock, data, STRIDE);
            pointer += sizeIdBlock;
        }

    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            setValueForData(chunk->backBlock[x][y]->id, pointer, sizeIdBlock, data, STRIDE);
            pointer += sizeIdBlock;
        }

    converPropertysChunk(chunk, pointer, false, data);
    converPropertysChunk(chunk, pointer, true, data);
    convertEntityChunk(chunk, entityInChunk, pointer, world, data);

    return data;
}

Chunk* ConvertChunkToData::recoveryChunk(unsigned char* chunkData, int chunkX, int chunkY, World* world)
{
    int pointer = 0;

    int biome1 = 0;
    int biome2 = 0;
    int biome2Info = 0;
    std::vector<Entity*>* entity = new std::vector<Entity*>();

    biome1 = getValueFromData(pointer, sizeBiome1, chunkData, STRIDE);
    pointer += sizeBiome1;

    biome2 = getValueFromData(pointer, sizeBiome2, chunkData, STRIDE);
    pointer += sizeBiome2;

    biome2Info = getValueFromData(pointer, sizeBiome2Info, chunkData, STRIDE);
    pointer += sizeBiome2Info;

    int propertyPointer = sizeBiome1 + sizeBiome2 + sizeBiome2Info + Chunk::sizeChunk * Chunk::sizeChunk * 2;

    Block*** block = new Block**[Chunk::sizeChunk];

    for (int x = 0; x < Chunk::sizeChunk; x++)
    {
        block[x] = new Block*[Chunk::sizeChunk];
    }

    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            int id = getValueFromData(pointer, sizeIdBlock, chunkData, STRIDE);
            pointer += sizeIdBlock;

            block[x][y] = RegisteryBlocks::createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, false, world, id);

            if (block[x][y]->propertyManager.allSize > 0)
            {
                PropertyManager* propertyManager = &block[x][y]->propertyManager;
                for (int z = 0; z < propertyManager->propertyList.size(); z++)
                {
                    propertyManager->propertyList[z]->value = getValueFromData(propertyPointer, propertyManager->propertyList[z]->sizeProperty, chunkData, STRIDE);
                    propertyPointer += propertyManager->propertyList[z]->sizeProperty;
                }
            }
            block[x][y]->start();
        }

    Block*** backBlock = new Block**[Chunk::sizeChunk];

    for (int x = 0; x < Chunk::sizeChunk; x++)
    {
        backBlock[x] = new Block*[Chunk::sizeChunk];
    }

    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            int id = getValueFromData(pointer, sizeIdBlock, chunkData, STRIDE);
            pointer += sizeIdBlock;

            backBlock[x][y] = RegisteryBlocks::createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, true, world, id);

            if (backBlock[x][y]->propertyManager.allSize > 0)
            {
                PropertyManager* propertyManager = &backBlock[x][y]->propertyManager;
                for (int z = 0; z < propertyManager->propertyList.size(); z++)
                {
                    propertyManager->propertyList[z]->value = getValueFromData(propertyPointer, propertyManager->propertyList[z]->sizeProperty, chunkData, STRIDE);
                    propertyPointer += propertyManager->propertyList[z]->sizeProperty;
                }
            }
            backBlock[x][y]->start();
        }

    pointer = propertyPointer;


    int countEntity = getValueFromData(pointer, sizeCountEntity, chunkData, STRIDE);
    pointer += sizeCountEntity;
    propertyPointer = pointer + countEntity * (sizeEntityPos * 2 + sizeIdEntity);

    for (int x = 0; x < countEntity; x++)
    {
        /*(int)(pow(2, sizeEntityPos * 8) / 2) - это максимальный размер, 
        который может хранить переменная sizeEntityPos * 8(умножение на 8, потому что одно значение хранит 1 байт)
        Это нужно, чтобы было можно хранить отрицательные значения, в данном случае позицию чанка*/
        int posX = getValueFromData(pointer, sizeEntityPos, chunkData, STRIDE) - (int)(std::pow(2, sizeEntityPos * 8) / 2);
        pointer += sizeEntityPos;

        int posY = getValueFromData(pointer, sizeEntityPos, chunkData, STRIDE) - (int)(std::pow(2, sizeEntityPos * 8) / 2);
        pointer += sizeEntityPos;

        int id = getValueFromData(pointer, sizeIdEntity, chunkData, STRIDE);
        pointer += sizeIdEntity;

       // Entity* localEntity = world->addEntity(posX, posY, id);
        Entity* localEntity = RegisteryEntity::addEntity(world, id, vec2(posX, posY));
        if (localEntity->propertyManager.allSize > 0)
        {
            PropertyManager* propertyManager = &localEntity->propertyManager;
            for (int y = 0; y < propertyManager->propertyList.size(); y++)
            {
                int sizeProperty = propertyManager->propertyList[y]->sizeProperty;
                int value = getValueFromData(propertyPointer, sizeProperty, chunkData, STRIDE);
                propertyPointer += sizeProperty;

                localEntity->propertyManager.propertyList[y]->value = value;
            }
        }
        localEntity->start();
    }

    Chunk* chunk = new Chunk(world, chunkX, chunkY);
    chunk->biome1 = biome1;
    chunk->biome2 = biome2;
    chunk->biome2Info = biome2Info;
    chunk->block = block;
    chunk->backBlock = backBlock;

    return chunk;
}

