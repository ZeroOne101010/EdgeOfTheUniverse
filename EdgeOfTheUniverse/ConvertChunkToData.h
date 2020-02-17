#pragma once
#include "ByteHelper.h"
#include "RegisteryBlocks.h"
#include <vector>
#include "Entity.h"

#define STRIDE 1
#define STRIDE_UNICODE 2

class Chunk;
class World;

class ConvertChunkToData
{
public:
   /* CHUNK DATA:
* 1. Первый биом чанка (2 байта)
* 2. Второй биом чанка (2 байта)
* 3. Параметр 2 биома чанка (2 байта)
* 4. id всех блоков
* 5. Параметры блоков
*/
    static int sizeBiome1;
    static int sizeBiome2;
    static int sizeBiome2Info;
    static int sizeCountEntity;
    static int sizeEntityPos;
    static int sizeIdEntity;
    static int sizeIdBlock;

    static int getValueFromData(unsigned long address, unsigned long offset, unsigned char* data, int stride);
    static void setValueForData(unsigned long value, unsigned long address, unsigned long offset, unsigned char* data, int stride);
    static int getSizePropertys(Chunk* chunk, bool isBackBlock);
    static void converPropertysChunk(Chunk* chunk, int& pointer, bool isBackBlock, unsigned char* data);
    static int getCountEntitys(Chunk* chunk, World* world, std::vector<Entity*>* entityInChunk);
    static int getSizePropertysEntity(std::vector<Entity*>* entityInChunk);
    static void convertEntityChunk(Chunk* chunk, std::vector<Entity*>* entityInChunk, int& pointer, World* world, unsigned char* data);
    static unsigned char* convertChunk(Chunk* chunk, World* world);
    static unsigned char* convertChunk(Chunk* chunk, World* world, int& size);
    static Chunk* recoveryChunk(unsigned char* chunkData, int chunkX, int chunkY, World* world);


};

