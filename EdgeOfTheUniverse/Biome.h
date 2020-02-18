#pragma once
//#include <vector>
#include "glm/glm.hpp"
#include "Chunk.h"
#include "BlockSpawner.h"
#include "PerlinNoise.h"
#include "RegisteryBiome.h"
#include "RegisteryBlocks.h"


class World;
class RandomCoor;
class BiomeAir;

class Biome
{
public:
    static int biomeOffsetLimited;

    glm::vec4 biomeColor = glm::vec4(255, 255, 255, 255);

    //public int offsetHigh = 0;

    int id;

    int offsetX = Chunk::sizeChunk;
    int offsetY = Chunk::sizeChunk;
    float offsetPosX = 0;
    float offsetPosY = 0;
    float sizeNoiseX = 1;
    float sizeNoiseY = 1;
    glm::vec4 backgroundColor = glm::vec4(255, 255, 255, 255);
    float brightnessK = 1;

    float high;
    float highSection;

    float limitUp;
    float limitDown;


    int offsetXLandshaft = Chunk::sizeChunk;
    int offsetYLandshaft = Chunk::sizeChunk;
    float sizeNoiseXLandshaft = 1;
    float sizeNoiseYLandshaft = 1;

    float highLandshaft = 5;

    int offsetSmoothBorder = 10;

    float offsetPosXAddition = 3452;
    float offsetPosYAddition = 363;
    float sizeNoiseXAddition = 1;
    float sizeNoiseYAddition = 1;

    float highAddition = 1;
    float highSectionAddition;

    std::vector<BlockSpawner> spawnBlock;
    std::vector<BlockSpawner> spawnBackBlock;

    Biome();
    Biome(int offsetX, int offsetY, float offsetPosX, float offsetPosY, float sizeNoiseX, float sizeNoiseY, float high, float highSection, float limitUp, float limitDown);
    virtual Biome* getNewBiome() = 0;
    virtual void editChunk(Chunk* chunk, Block*** block, Block*** backBlock);
    Biome* createBiome(World* world);
    void setLandshaft(int offsetXLandshaft, int offsetYLandshaft, float sizeNoiseXLandshaft, float sizeNoiseYLandshaft, float highLandshaft);
    bool toSpawnBiome(int posX, int posY, RandomCoor* rand);
    void addSpawnBlock(Block* block, float offsetX, float offsetY, float offsetPosX, float offsetPosY, float high, float highSection, float limitUp, float limitDown, float sizeNoise);
    void addSpawnBackBlock(Block* block, float offsetX, float offsetY, float offsetPosX, float offsetPosY, float high, float highSection, float limitUp, float limitDown, float sizeNoise);
    void addSpawnBlock(Block* block, float offsetX, float offsetY, float offsetPosX, float offsetPosY, float high, float highSection, float sizeNoise);
    void addSpawnBackBlock(Block* block, float offsetX, float offsetY, float offsetPosX, float offsetPosY, float high, float highSection, float sizeNoise);
    Block* getBiomeBlock(int blockX, int blockY, World* world);
    Block* getBiomeBackBlock(int blockX, int blockY, World* world);
    Block* getBiomeBlock(int blockX, int blockY, float tSection, World* world);
    bool needCreateBiomeBlock(int blockX, int blockY, float tSection, World* world);
    Block* getBiomeBlockWithTransition(int blockX, int blockY, float tSection, bool isBackBlock, Biome* biome, World* world);
    Block* getBiomeBackBlock(int blockX, int blockY, float tSection, World* world);
    void setBorderChunk(Chunk* chunk, World* world);
    bool toCreateBlockInLandshaft(int blockX, int blockY, World* world);
    void setLandshaftChunk(Chunk* chunk, World* world);
    void setAdditionChunk(Chunk* chunk, World* world);
    Chunk* generateChunk(int chunkX, int chunkY, World* world);
};

