#include "RandomCoor.h"

RandomCoor::RandomCoor(int sizeNumberMap, int seed)
{
    this->sizeNumberMap = sizeNumberMap;
    this->seed = seed;

    numberMap = new char*[sizeNumberMap];
    for (int x = 0; x < sizeNumberMap; x++)
    {
        numberMap[x] = new char[sizeNumberMap];
    }

    std::srand(seed);
    for (int x = 0; x < sizeNumberMap; x++)
        for (int y = 0; y < sizeNumberMap; y++)
        {
            numberMap[x][y] = rand() % 127;
        }
}

bool RandomCoor::getProbably(int posX, int posY, int maxSize, int probably)
{
    float value = next(posX, posY, 0, maxSize);
    return value < probably;
}

float RandomCoor::next(int posX, int posY, float min, float max)
{
    int posXF = posX + 100000;
    int posYF = posY + 100000;
    if (posXF >= sizeNumberMap)
    {
        posXF = posXF % sizeNumberMap;
    }

    if (posYF >= sizeNumberMap)
    {
        posYF = posYF % sizeNumberMap;
    }

    if (posXF < 0)
    {
        posXF = (abs(posXF) % sizeNumberMap) > 0 ? (abs(posXF) % sizeNumberMap + 1) * sizeNumberMap : 0;
    }
    if (posYF < 0)
    {
        posYF = (abs(posYF) % sizeNumberMap) > 0 ? (abs(posYF) % sizeNumberMap + 1) * sizeNumberMap : 0;
    }
    float number = numberMap[posXF][posYF];
    float answer = min + (max - min) * (number / 127.00f);

    return answer;
}
