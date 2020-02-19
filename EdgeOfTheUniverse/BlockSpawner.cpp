#include "BlockSpawner.h"

float BlockSpawner::offsetLimited = 30;
float BlockSpawner::kLimit = 0.2f;


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

    if (!isInverseMap)
    {
        if (posY < limitDown - offsetLimited && posY > limitUp + offsetLimited)
        {
            if (answer > highSection)
            {
                isCreate = true;
            }
        }
        else
        {
            float t = 0;
            if (posY >= limitDown - offsetLimited)
            {
                t = (offsetLimited - (limitDown - posY)) / offsetLimited;
            }
            else if (posY <= limitUp + offsetLimited)
            {
                t = (offsetLimited - (posY - limitUp)) / offsetLimited;
            }
            else
            {
                t = 1;
            }

            if (t < 0) t = 0;
            if (t > 1) t = 1;

            float section = highSection + (offsetY * kLimit * high * sizeNoise - highSection) * t;

            if (answer > section)
            {
                isCreate = true;
            }
        }
    }
    else
    {
        if (posY < limitDown - offsetLimited && posY > limitUp + offsetLimited)
        {
            if (answer < highSection)
            {
                isCreate = true;
            }
        }
        else
        {
            float t = 0;
            if (posY >= limitDown - offsetLimited)
            {
                t = (offsetLimited - (limitDown - posY)) / offsetLimited;
            }
            else if (posY <= limitUp + offsetLimited)
            {
                t = (offsetLimited - (posY - limitUp)) / offsetLimited;
            }
            else
            {
                t = 1;
            }

            if (t < 0) t = 0;
            if (t > 1) t = 1;

            float section = highSection + (offsetY * kLimit * high * sizeNoise - highSection) * t;

            if (answer < section)
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

    if (!isInverseMap)
    {
        if (posY < limitDown - offsetLimited && posY > limitUp + offsetLimited)
        {
            if (answer > (highSection + (offsetY * kLimit * high * sizeNoise - highSection) * tSection))
            {
                isCreate = true;
            }
        }
        else
        {
            float t = 0;
            if (posY >= limitDown - offsetLimited)
            {
                t = (offsetLimited - (limitDown - posY)) / offsetLimited;
            }
            else if (posY <= limitUp + offsetLimited)
            {
                t = (offsetLimited - (posY - limitUp)) / offsetLimited;
            }
            else
            {
                t = 1;
            }

            if (t < 0) t = 0;
            if (t > 1) t = 1;

            float section = (highSection + (offsetY * kLimit * high * sizeNoise - highSection) * tSection) + (offsetY * kLimit * high * sizeNoise - (highSection + (offsetY * kLimit * high * sizeNoise - highSection) * tSection)) * t;;

            if (answer > section)
            {
                isCreate = true;
            }
        }
    }
    else
    {
        if (posY < limitDown - offsetLimited && posY > limitUp + offsetLimited)
        {
            if (answer < (highSection + (offsetY * kLimit * high * sizeNoise - highSection) * tSection))
            {
                isCreate = true;
            }
        }
        else
        {
            float t = 0;
            if (posY >= limitDown - offsetLimited)
            {
                t = (offsetLimited - (limitDown - posY)) / offsetLimited;
            }
            else if (posY <= limitUp + offsetLimited)
            {
                t = (offsetLimited - (posY - limitUp)) / offsetLimited;
            }
            else
            {
                t = 1;
            }

            if (t < 0) t = 0;
            if (t > 1) t = 1;

            float section = (highSection + (offsetY * kLimit * high * sizeNoise - highSection) * tSection) + (offsetY * kLimit * high * sizeNoise - (highSection + (offsetY * kLimit * high * sizeNoise - highSection) * tSection)) * t;;

            if (answer < section)
            {
                isCreate = true;
            }
        }
    }

    return isCreate;
}
