#include "ByteHelper.h"
#include "PerlinNoise.h"

float PerlinNoise::lerp(float t, float a, float b)
{
	return a + (b - a) * t;
}

float PerlinNoise::getPerlinNoise(float posX, float posZ, int offsetX, int offsetZ, RandomCoor* rand)
{
    //int sXa = (int)(abs(posX) / offsetX);
    //int sXb = sXa + 1;
    //int sXc = sXa;
    //int sXd = sXb;

    //sXa *= offsetX;
    //sXb *= offsetX;
    //sXc *= offsetX;
    //sXd *= offsetX;

    //int sZa = (int)(abs(posZ) / offsetZ);
    //int sZb = sZa;
    //int sZc = sZa + 1;
    //int sZd = sZa + 1;

    //sZa *= offsetZ;
    //sZb *= offsetZ;
    //sZc *= offsetZ;
    //sZd *= offsetZ;

    //glm::vec2 serifA = glm::vec2(sXa, sZa);
    //glm::vec2 serifB = glm::vec2(sXb, sZb);
    //glm::vec2 serifC = glm::vec2(sXc, sZc);
    //glm::vec2 serifD = glm::vec2(sXd, sZd);

    //glm::vec2 point = glm::vec2(abs(posX), abs(posZ));

    //glm::vec2 sDisA = point - serifA;
    //glm::vec2 sDisB = point - serifB;
    //glm::vec2 sDisC = point - serifC;
    //glm::vec2 sDisD = point - serifD;

    //int signX = posX > 0 ? 1 : -1;
    //int signZ = posZ > 0 ? 1 : -1;

    //glm::vec2 inclineA = glm::vec2(rand->next((int)serifA.x * signX, (int)serifA.y * signZ, 0, 100) / 100.00f, rand->next((int)(sin(serifA.x * signX) * rand->sizeNumberMap), (int)(sin(serifA.y * signZ) * rand->sizeNumberMap), 0, 100) / 100.00f);
    //glm::vec2 inclineB = glm::vec2(rand->next((int)serifB.x * signX, (int)serifB.y * signZ, 0, 100) / 100.00f, rand->next((int)(sin(serifB.x * signX) * rand->sizeNumberMap), (int)(sin(serifB.y * signZ) * rand->sizeNumberMap), 0, 100) / 100.00f);
    //glm::vec2 inclineC = glm::vec2(rand->next((int)serifC.x * signX, (int)serifC.y * signZ, 0, 100) / 100.00f, rand->next((int)(sin(serifC.x * signX) * rand->sizeNumberMap), (int)(sin(serifC.y * signZ) * rand->sizeNumberMap), 0, 100) / 100.00f);
    //glm::vec2 inclineD = glm::vec2(rand->next((int)serifD.x * signX, (int)serifD.y * signZ, 0, 100) / 100.00f, rand->next((int)(sin(serifD.x * signX) * rand->sizeNumberMap), (int)(sin(serifD.y * signZ) * rand->sizeNumberMap), 0, 100) / 100.00f);

    //float cosmA = inclineA.x * sDisA.x + inclineA.y * sDisA.y;
    //float cosmB = inclineB.x * sDisB.x + inclineB.y * sDisB.y;
    //float cosmC = inclineC.x * sDisC.x + inclineC.y * sDisC.y;
    //float cosmD = inclineD.x * sDisD.x + inclineD.y * sDisD.y;

    //float tX = sDisA.x / offsetX;
    //float tZ = sDisA.y / offsetZ;

    //float polrX1 = lerp(tX, cosmA, cosmB);
    //float polrX2 = lerp(tX, cosmC, cosmD);
    //float polr = lerp(tZ, polrX1, polrX2);

    int sXa = (int)(abs(posX) / offsetX);
    int sXb = sXa + 1;
    int sXc = sXa;
    int sXd = sXb;

    sXa *= offsetX;
    sXb *= offsetX;
    sXc *= offsetX;
    sXd *= offsetX;

    int sZa = (int)(abs(posZ) / offsetZ);
    int sZb = sZa;
    int sZc = sZa + 1;
    int sZd = sZa + 1;

    sZa *= offsetZ;
    sZb *= offsetZ;
    sZc *= offsetZ;
    sZd *= offsetZ;

    //float maxDis = ByteHelper::distance(glm::vec2(0, 0), glm::vec2(offsetX, offsetZ));

    glm::vec2 serifA = glm::vec2(sXa, sZa);
    glm::vec2 serifB = glm::vec2(sXb, sZb);
    glm::vec2 serifC = glm::vec2(sXc, sZc);
    glm::vec2 serifD = glm::vec2(sXd, sZd);

    glm::vec2 point = glm::vec2(abs(posX), abs(posZ));

    glm::vec2 sDisA = point - serifA;
    glm::vec2 sDisB = point - serifB;
    glm::vec2 sDisC = point - serifC;
    glm::vec2 sDisD = point - serifD;

    sDisA = glm::vec2(sDisA.x / offsetX, sDisA.y / offsetZ);
    sDisB = glm::vec2(sDisB.x / offsetX, sDisB.y / offsetZ);
    sDisC = glm::vec2(sDisC.x / offsetX, sDisC.y / offsetZ);
    sDisD = glm::vec2(sDisD.x / offsetX, sDisD.y / offsetZ);

    int signX = posX > 0 ? 1 : -1;
    int signZ = posZ > 0 ? 1 : -1;

    glm::vec2 inclineA = glm::vec2(rand->next((int)serifA.x * signX, (int)serifA.y * signZ, 0, 100) / 100.00f, rand->next((int)(sin(serifA.x * signX) * rand->sizeNumberMap), (int)(sin(serifA.y * signZ) * rand->sizeNumberMap), 0, 100) / 100.00f);
    glm::vec2 inclineB = glm::vec2(rand->next((int)serifB.x * signX, (int)serifB.y * signZ, 0, 100) / 100.00f, rand->next((int)(sin(serifB.x * signX) * rand->sizeNumberMap), (int)(sin(serifB.y * signZ) * rand->sizeNumberMap), 0, 100) / 100.00f);
    glm::vec2 inclineC = glm::vec2(rand->next((int)serifC.x * signX, (int)serifC.y * signZ, 0, 100) / 100.00f, rand->next((int)(sin(serifC.x * signX) * rand->sizeNumberMap), (int)(sin(serifC.y * signZ) * rand->sizeNumberMap), 0, 100) / 100.00f);
    glm::vec2 inclineD = glm::vec2(rand->next((int)serifD.x * signX, (int)serifD.y * signZ, 0, 100) / 100.00f, rand->next((int)(sin(serifD.x * signX) * rand->sizeNumberMap), (int)(sin(serifD.y * signZ) * rand->sizeNumberMap), 0, 100) / 100.00f);

    float cosmA = inclineA.x * sDisA.x + inclineA.y * sDisA.y;
    float cosmB = inclineB.x * sDisB.x + inclineB.y * sDisB.y;
    float cosmC = inclineC.x * sDisC.x + inclineC.y * sDisC.y;
    float cosmD = inclineD.x * sDisD.x + inclineD.y * sDisD.y;

    float tX = sDisA.x;
    float tZ = sDisA.y;

    float polrX1 = lerp(tX, cosmA, cosmB);
    float polrX2 = lerp(tX, cosmC, cosmD);
    float polr = lerp(tZ, polrX1, polrX2);

    return polr;
}

float PerlinNoise::getPerlinNoise2DWithCurve(float posX, float posY, int offsetX, int offsetZ, float T, float kPos, float kOffset, int countNoises, RandomCoor rand)
{
    float* yRes = new float[countNoises];
    for (int x = 0; x < countNoises; x++)
    {
        yRes[x] = getPerlinNoise(posX + x * kPos, posY + x * kPos, (int)(offsetX + x * kOffset), (int)(offsetZ + x * kOffset), &rand);
    }

    float y = yRes[0];

    for (int x = 1; x < countNoises; x++)
    {
        y = lerp(T, y, yRes[x]);
    }

    delete[countNoises] yRes;
    return y;
}

float PerlinNoise::smoothstep(float edge0, float edge1, float x)
{
    x = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return x * x * (3 - 2 * x);
}

float PerlinNoise::clamp(float x, float lowerlimit, float upperlimit)
{
    if (x < lowerlimit)
    {
        x = lowerlimit;
    }
    if (x > upperlimit)
    {
        x = upperlimit;
    }
    return x;
}
