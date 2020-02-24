#include "ByteHelper.h"
#include "PerlinNoise.h"

#define PI 3.1415926f

float PerlinNoise::lerp(float t, float a, float b)
{
	return a + (b - a) * t;
}

float PerlinNoise::getPerlinNoise(float posX, float posZ, int offsetX, int offsetZ, RandomCoor* rand)
{
    float sXa = (int)(abs(posX) / offsetX);
    float sXb = sXa + 1;
    float sXc = sXa;
    float sXd = sXb;

    sXa *= offsetX;
    sXb *= offsetX;
    sXc *= offsetX;
    sXd *= offsetX;

    float sZa = (int)(abs(posZ) / offsetZ);
    float sZb = sZa;
    float sZc = sZa + 1;
    float sZd = sZa + 1;

    sZa *= offsetZ;
    sZb *= offsetZ;
    sZc *= offsetZ;
    sZd *= offsetZ;

    glm::vec2 serifA = glm::vec2(sXa, sZa);
    glm::vec2 serifB = glm::vec2(sXb, sZb);
    glm::vec2 serifC = glm::vec2(sXc, sZc);
    glm::vec2 serifD = glm::vec2(sXd, sZd);

    glm::vec2 point = glm::vec2(abs(posX), abs(posZ));

    glm::vec2 sDisA = point - serifA;
    glm::vec2 sDisB = point - serifB;
    glm::vec2 sDisC = point - serifC;
    glm::vec2 sDisD = point - serifD;

    int signX = posX > 0 ? 1 : -1;
    int signZ = posZ > 0 ? 1 : -1;

    //float maxValueX = (Mathf.Acos(1.000f / (offsetX * 1.00f / 2)) * 1.000f /( Mathf.PI * 2));
    //float maxValueY = (Mathf.Asin(1.000f / (offsetY * 1.00f / 2)) * 1.000f / (Mathf.PI * 2));

    float maxValueX = 1;
    float maxValueY = 1;

    glm::vec2 inclineA = glm::vec2(rand->next((int)serifA.x * signX, (int)serifA.y * signZ, 0, 100) / 100.00f, rand->next((int)(sin(serifA.x * signX) * rand->sizeNumberMap), (int)(sin(serifA.y * signZ) * rand->sizeNumberMap), 0, 100) / 100.00f);
    glm::vec2 inclineB = glm::vec2(rand->next((int)serifB.x * signX, (int)serifB.y * signZ, 0, 100) / 100.00f, rand->next((int)(sin(serifB.x * signX) * rand->sizeNumberMap), (int)(sin(serifB.y * signZ) * rand->sizeNumberMap), 0, 100) / 100.00f);
    glm::vec2 inclineC = glm::vec2(rand->next((int)serifC.x * signX, (int)serifC.y * signZ, 0, 100) / 100.00f, rand->next((int)(sin(serifC.x * signX) * rand->sizeNumberMap), (int)(sin(serifC.y * signZ) * rand->sizeNumberMap), 0, 100) / 100.00f);
    glm::vec2 inclineD = glm::vec2(rand->next((int)serifD.x * signX, (int)serifD.y * signZ, 0, 100) / 100.00f, rand->next((int)(sin(serifD.x * signX) * rand->sizeNumberMap), (int)(sin(serifD.y * signZ) * rand->sizeNumberMap), 0, 100) / 100.00f);

    float cosmA = (inclineA.x * maxValueX) * sDisA.x + (inclineA.y * maxValueY) * sDisA.y;
    float cosmB = (inclineB.x * maxValueX) * sDisB.x + (inclineB.y * maxValueY) * sDisB.y;
    float cosmC = (inclineC.x * maxValueX) * sDisC.x + (inclineC.y * maxValueY) * sDisC.y;
    float cosmD = (inclineD.x * maxValueX) * sDisD.x + (inclineD.y * maxValueY) * sDisD.y;

    float tX = sDisA.x * 1.00f / offsetX;
    float tZ = sDisA.y * 1.00f / offsetZ;

    float polrX1 = cosmA + (cosmB - cosmA) * tX;
    float polrX2 = cosmC + (cosmD - cosmC) * tX;
    float polr = polrX1 + (polrX2 - polrX1) * tZ;

    return smoothstep(-3, 3, polr);
    // smoothstep(-2.5f, 2.5f, polr);
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
    float t = clamp((x - edge0) / (edge1 - edge0), 0.000f, 1.000f);
    return t * t * (3.0f - 2.0f * t);
}

float PerlinNoise::clamp(float x, float lowerlimit, float upperlimit)
{
    if (x < lowerlimit)
    {
        x = lowerlimit;
    }
    else if (x > upperlimit)
    {
        x = upperlimit;
    }
    return x;
}
