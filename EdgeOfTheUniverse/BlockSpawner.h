#pragma once
#include "RandomCoor.h"
#include "Block.h"
#include "PerlinNoise.h"
#include <vector>
#include <map>
class BlockSpawner
{
public:
    Block* block;

    float offsetX, offsetY;
    float offsetPosX, offsetPosY;
    float highSection;
    float high;
    float sizeNoise;
    bool isInverseMap = false;

    float limitUp;
    float limitDown;
    static float offsetLimited;
    static float kLimit;

    BlockSpawner(Block* block, float offsetX, float offsetY, float offsetPosX, float offsetPosY, float high, float highSection, float limitUp, float limitDown, float sizeNoise);

    bool toCreateBlock(int posX, int posY, RandomCoor* rand);
    bool toCreateBlock(int posX, int posY, float tSection, RandomCoor* rand);
};

