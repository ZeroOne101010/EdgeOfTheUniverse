#include "ByteHelper.h"

int ByteHelper::setValue2To10(int* code, int size, int value2)
{
    int number = 0;
    for (int x = 0; x < size; x++)
    {
        number += code[x] * (int)pow(value2, size - x - 1);
    }
    return number;
}

int ByteHelper::set256To10(unsigned char* code, int size)
{
    int value = 0;
    for (int x = 0; x < size; x++)
    {
        value += code[x] * (int)pow(256, size - x - 1);
    }
    return value;
}

int ByteHelper::getSizeCode(int value1, int value2)
{
    float logCode = (float)(log(value1) / log(value2));
    float logRes = logCode - (int)(logCode);
    int sizeCode = logRes > 0 ? (int)logCode + 1 : (int)logCode;
    if (value1 <= 1) sizeCode = 1;
    return sizeCode;
}

int* ByteHelper::set10ToValue(int value, float res, int& size)
{
    float logCode = (float)(log(value) / log(res)) - (int)(log(value) / log(res));
    size = getSizeCode((int)value, (int)res);;
    if (value <= 1)
    {
        size = 1;
    }
    int* code = new int[size];

    if (value > 0)
    {
        if (logCode > 0)
        {
            float saveValue = value;

            for (int x = size - 1; x >= 0; x--)
            {
                saveValue = saveValue / (res * 1.0f);
                float number2 = saveValue - (int)(saveValue); // остаток
                saveValue = (int)saveValue;
                int answ = (int)(number2 * res);
                code[x] = answ;
            }
        }
        else
        {
            if (value != 1)
            {
                int sizeCode = size + 1;
                code = new int[sizeCode];
            }
            code[0] = 1;
        }
    }
    else
    {
        code[0] = 0;
    }

    return code;
}

unsigned char* ByteHelper::set10To256(int value, int& size)
{
    const int* codeInt = set10ToValue(value, 256, size);
    unsigned char* code = new unsigned char[size];
    for (int x = 0; x < size; x++)
    {
        code[x] = (unsigned char)(codeInt[x]);
    }
    return code;
}

float ByteHelper::distance(glm::vec2 vec1, glm::vec2 vec2)
{
    glm::vec2 dVec = vec2 - vec1;
    return (float)sqrt(dVec.x * dVec.x + dVec.y * dVec.y);
}

glm::vec2 ByteHelper::normalized(glm::vec2 vec)
{
    float lenght = (float)sqrt(vec.x * vec.x + vec.y * vec.y);
    return glm::vec2(vec.x / lenght, vec.y / lenght);
}
