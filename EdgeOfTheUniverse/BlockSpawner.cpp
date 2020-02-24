#include "BlockSpawner.h"

float BlockSpawner::offsetLimited = 30;


BlockSpawner::BlockSpawner(Block* block, float offsetX, float offsetY, float offsetPosX, float offsetPosY, float high, float highSection, float limitUp, float limitDown, float sizeNoise)
{
    this->block = block;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    this->offsetPosX = offsetPosX;
    this->offsetPosY = offsetPosY;
    this->high = high;
    this->highSection = highSection;
    this->limitUp = limitUp;
    this->limitDown = limitDown;
    this->sizeNoise = sizeNoise;
}

bool BlockSpawner::toCreateBlock(int posX, int posY, RandomCoor* rand)
{
    float answer = PerlinNoise::getPerlinNoise((posX + offsetPosX) / sizeNoise, (posY + offsetPosY) / sizeNoise, (int)offsetX, (int)offsetY, rand);
    

    answer *= high;
    bool isCreate = false;


    float limitedAnswerUp = PerlinNoise::getPerlinNoise((posX + 245) * 1.000f / sizeNoise, 2344.000f / sizeNoise, (int)offsetX, (int)offsetY, rand) * highLandshaft;
    float limitedAnswerDown = PerlinNoise::getPerlinNoise((posX + 2346) * 1.000f / sizeNoise, 745.000f / sizeNoise, (int)offsetX, (int)offsetY, rand) * highLandshaft;


    limitedAnswerUp = limitUp + limitedAnswerUp;
    limitedAnswerDown = limitDown - limitedAnswerDown;

    if (!isInverseMap)
    {

        if (posY > limitedAnswerUp && posY < limitedAnswerDown)
        {
            if (answer >= highSection)
            {
                isCreate = true;
            }
        }
    }
    else
    {
        if (posY > limitedAnswerUp&& posY < limitedAnswerDown)
        {
            if (answer < highSection)
            {
                isCreate = true;
            }
        }
    }

    return isCreate;
}

bool BlockSpawner::toCreateBlock(int posX, int posY, float tSection, RandomCoor* rand)
{
    float answer = PerlinNoise::getPerlinNoise((posX + offsetPosX) / sizeNoise, (posY + offsetPosY) / sizeNoise, (int)offsetX, (int)offsetY, rand);
    answer *= high;
    bool isCreate = false;

    float limitedAnswerUp = PerlinNoise::getPerlinNoise((posX + 245) * 1.000f / sizeNoise, 2344.000f / sizeNoise, (int)offsetX, (int)offsetY, rand) * highLandshaft;
    float limitedAnswerDown = PerlinNoise::getPerlinNoise((posX + 2346) * 1.000f / sizeNoise, 745.000f / sizeNoise, (int)offsetX, (int)offsetY, rand) * highLandshaft;


    limitedAnswerUp = limitUp + limitedAnswerUp;
    limitedAnswerDown = limitDown - limitedAnswerDown;

    if (!isInverseMap)
    {
        if (posY > limitedAnswerUp&& posY < limitedAnswerDown)
        {
            if (answer > (highSection * tSection))
            {
                isCreate = true;
            }
        }
    }
    else
    {
        if (posY > limitedAnswerUp&& posY < limitedAnswerDown)
        {
            if (answer < (highSection * tSection))
            {
                isCreate = true;
            }
        }
    }

    return isCreate;
}
