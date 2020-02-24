#include "Chunk.h"
#include "RegisteryEntity.h"
#include <Windows.h>
#include <stdio.h>
#include "ConvertRegionData.h"
/* CHUNK DATA:
* 1. Первый биом чанка (2 байта)
* 2. Второй биом чанка (2 байта)
* 3. Параметр 2 биома чанка (2 байта)
* 4. id всех блоков
* 5. Параметры блоков
*/

/* Будут отдельные файлы, содержащие в себе одновременно несколько чанков, которые будут заполняться следующим образом:
 * REGION DATA:
 * 1. Позиция региона X (2 байта)
 * 2. Позиция региона Y (2 байта)
 * 3. Количиство заполненных ссылок под чанки (2 байта)
 * 4. Ссылки на чанки:
 *       4.1 Позиция чанка по X (2 байта)
 *       4.2 Позиция чанка по Y (2 байта)
 *       4.3 Ссылка на чанк в region data (2 байта)
 * 5. Чанки
 Нууу, в целом как то так :)
 */

int ConvertRegionData::sizeRegion = 15;

int ConvertRegionData::sizeRegionPos = 3;
int ConvertRegionData::sizeAddress = 3;

const std::string ConvertRegionData::directoryToMaps = "Source\\Saves\\";
const std::string ConvertRegionData::directioryToRegions = "Regions\\";
const std::string ConvertRegionData::extensionRegion = ".region";

/* Смещение символов от начала кодировки юникод.
   Это сделанно для того, чтобы не использовать служебные символы, при сохранения файла.
   А вот значение 688 как говорится, взято из воздуха. С таким смещением символы попрыкольней :D
*/
int ConvertRegionData::offsetEncoding = 688;

//Размер данных должен быть не меньше 2!!!
void ConvertRegionData::setDataToUnicode(unsigned char* data)
{
    try
    {
    data[0] = 254;
    data[1] = 255;
    }
    catch(int a)
    {
        std::cout << "ConvertRegionData::setDataToUnicode(unsigned char* data) : размер данных меньше 2" << std::endl;
        throw;
    };
}

/*Метод не совершенен из за недостатка времени...*/
std::string ConvertRegionData::getPath(char* localPath, int size)
{
    const int maxLenght = MAX_PATH * 2;
    wchar_t path[maxLenght];

    GetModuleFileName(NULL, path, maxLenght);

    int lenght = 0;
    for (int x = 0; x < maxLenght; x++)
    {
        if (path[x] == STOP_NAME)
        {
            lenght = x;
            break;
        }
    }

    char* charPath = new char[lenght];
    int addreses = 0;

    for (int x = 0; x < lenght; x++)
    {
        charPath[x] = (char)path[x]; // Преобразование через reinterpret_cast невозможно, так как размер wchar_t = 2 байта
        if (charPath[x] == 92)
        {
            addreses = x - 2;
        }
    }

    int lenghtAnswerChar = lenght - addreses;
    int sizeStr = lenghtAnswerChar + size;

    char* answer = new char[sizeStr];

    for (int x = 0; x < lenghtAnswerChar; x++)
    {
        answer[x] = charPath[x];
    }

    for (int x = 0; x < size; x++)
    {
        answer[lenghtAnswerChar + x] = localPath[x];
    }

    std::string globalPath = std::string(answer, sizeStr);

    delete[lenght] charPath;
    delete[sizeStr] answer;

    return globalPath;
}

/*Метод не совершенен из за недостатка времени...*/
std::string ConvertRegionData::getPath(std::string localPath)
{
    const int maxLenght = MAX_PATH * 2;
    wchar_t path[maxLenght];

    GetModuleFileName(NULL, path, maxLenght);

    int lenght = 0;
    for (int x = 0; x < maxLenght; x++)
    {
        if (path[x] == STOP_NAME)
        {
            lenght = x;
            break;
        }
    }

    char* charPath = new char[lenght];
    int addreses = 0;

    for (int x = 0; x < lenght; x++)
    {
        charPath[x] = (char)path[x]; // Преобразование через reinterpret_cast невозможно, так как размер wchar_t = 2 байта
        if (charPath[x] == 92)
        {
            addreses = x - 2;
        }
    }

    int lenghtAnswerChar = lenght - addreses;
    int sizeStr = lenghtAnswerChar + localPath.length();

    char* answer = new char[sizeStr];

    for (int x = 0; x < lenghtAnswerChar; x++)
    {
        answer[x] = charPath[x];
    }

    for (size_t x = 0; x < localPath.length(); x++)
    {
        answer[lenghtAnswerChar + x] = localPath[x];
    }

    std::string globalPath = std::string(answer, sizeStr);

    delete[lenght] charPath;
    delete[sizeStr] answer;

    return globalPath;
}

unsigned char* ConvertRegionData::createRegionFile(int regionX, int regionY, int& size)
{
    int dataSize = sizeRegionPos * 2 + sizeAddress + (sizeRegionPos * 2 + sizeAddress) * sizeRegion * sizeRegion;
    byte* data = new byte[sizeRegionPos * 2 + sizeAddress + (sizeRegionPos * 2 + sizeAddress) * sizeRegion * sizeRegion];

    unsigned long pointer = 0;

    ConvertChunkToData::setValueForData(regionX + (int)(std::pow(2, sizeRegionPos * 8) / 2), pointer, sizeRegionPos, data, STRIDE);
    pointer += sizeRegionPos;

    ConvertChunkToData::setValueForData(regionY + (int)(std::pow(2, sizeRegionPos * 8) / 2), pointer, sizeRegionPos, data, STRIDE);
    pointer += sizeRegionPos;

    ConvertChunkToData::setValueForData(0, pointer, sizeAddress, data, STRIDE);
    pointer += sizeAddress;

    ConvertChunkToData::setValueForData(0, pointer, (sizeRegionPos * 2 + sizeAddress) * sizeRegion * sizeRegion, data, STRIDE);

    std::stringstream ss;
    ss << regionX;
    std::string str;
    ss >> str;
    while (str.size() < 5)
    {
        str.push_back('0');
    }

    ss = std::stringstream();
    ss << regionY;
    std::string str1;
    ss >> str1;
    while (str1.size() < 5)
    {
        str1.push_back('0');
    }

    std::string name = std::string(str) + std::string(str1);
    std::string path = ConvertRegionData::getPath(directoryToMaps + directioryToRegions + name + extensionRegion);


    std::ofstream writer(path, std::ofstream::binary);
    writer.write(reinterpret_cast<char*>(data), dataSize);
    writer.close();
    size = dataSize;
    return data;
}

void ConvertRegionData::saveChunkDataToRegion(Chunk* chunk, World* world)
{
    int regionX = 0;
    int regionY = 0;

    if (chunk->chunkX >= 0)
    {
        regionX = (chunk->chunkX / ConvertRegionData::sizeRegion);
    }
    else
    {
        if (abs(chunk->chunkX * 1.00f / ConvertRegionData::sizeRegion) - abs(chunk->chunkX / ConvertRegionData::sizeRegion) > 0)
        {
            regionX = chunk->chunkX / ConvertRegionData::sizeRegion - 1;
        }
        else
        {
            regionX = chunk->chunkX / ConvertRegionData::sizeRegion;
        }
    }

    if (chunk->chunkY >= 0)
    {
        regionY = (chunk->chunkY / ConvertRegionData::sizeRegion);
    }
    else
    {

        if (abs(chunk->chunkY * 1.00f / ConvertRegionData::sizeRegion) - abs(chunk->chunkY / ConvertRegionData::sizeRegion) > 0)
        {
            regionY = chunk->chunkY / ConvertRegionData::sizeRegion - 1;
        }
        else
        {
            regionY = chunk->chunkY / ConvertRegionData::sizeRegion;
        }
    }

    std::stringstream ss;
    ss << regionX;
    std::string str;
    ss >> str;
    while (str.size() < 5)
    {
        str.push_back('0');
    }

    ss = std::stringstream();
    ss << regionY;
    std::string str1;
    ss >> str1;
    while (str1.size() < 5)
    {
        str1.push_back('0');
    }

    std::string name = std::string(str) + std::string(str1);
    std::string path = ConvertRegionData::getPath(directoryToMaps + directioryToRegions + name + extensionRegion);

    std::ifstream reader;

    reader.open(path, std::ifstream::binary);

    unsigned char* data = nullptr;
    int sizeData = 0;

    bool readerIsOpen = false;

    std::vector<unsigned char> fileData;

    if (reader.is_open())
    {
        char ch = 0;
        while (reader.get(ch))
        {
            if (fileData.size() == 105)
            {
                int k = 1;
            }
            fileData.push_back(ch);
        }
        data = fileData.data();
        sizeData = fileData.size();
        readerIsOpen = true;
    }
    else
    {
        data = createRegionFile(regionX, regionY, sizeData);
    }

    reader.close();

    int countFillChunk = ConvertChunkToData::getValueFromData(sizeRegionPos * 2, sizeAddress, data, STRIDE);

    int pointer = sizeRegionPos * 2 + sizeAddress;

    bool isMatches = false;

    for (int x = 0; x < countFillChunk; x++)
    {
        int chunkX = ConvertChunkToData::getValueFromData(pointer, sizeRegionPos, data, STRIDE) - (int)(std::pow(2, sizeRegionPos * 8) / 2);
        pointer += sizeRegionPos;

        int chunkY = ConvertChunkToData::getValueFromData(pointer, sizeRegionPos, data, STRIDE) - (int)(std::pow(2, sizeRegionPos * 8) / 2);
        pointer += sizeRegionPos;

        if (chunkX == chunk->chunkX && chunkY == chunk->chunkY)
        {
            isMatches = true;
            break;
        }
        else
        {
            pointer += sizeAddress;
        }
    }

    if (isMatches)
    {
        haveChunk(pointer, chunk, regionX, regionY, world, data, sizeData);
        if (!readerIsOpen)
        {
            delete[sizeData] data;
        }
    }
    else
    {
        notHaveChunk(pointer, chunk, regionX, regionY, world, data, sizeData);
        if (!readerIsOpen)
        {
            delete[sizeData] data;
        }
    }
}

void ConvertRegionData::notHaveChunk(unsigned long pointer, Chunk* chunk, int regionX, int regionY, World* world, unsigned char* data, int size)
{
    int countFillChunks = ConvertChunkToData::getValueFromData(sizeRegionPos * 2, sizeAddress, data, STRIDE);
    int newChunkXInData = (sizeRegionPos * 2 + sizeAddress) + countFillChunks * (sizeRegionPos * 2 + sizeAddress);
    int oldChunkAddress = ConvertChunkToData::getValueFromData(newChunkXInData - sizeAddress, sizeAddress, data, STRIDE) == 0 ? 
        (sizeRegionPos * 2 + sizeAddress) + sizeRegion * sizeRegion * (sizeRegionPos * 2 + sizeAddress) : 
        ConvertChunkToData::getValueFromData(newChunkXInData - sizeAddress, sizeAddress, data, STRIDE);
    int newChunkAddress = 0;

    int sizeOldChunk = 0;

    int sizeOldPropertys = 0;
    int sizeOldBlockPropertys = 0;
    int sizeOldBackPropertys = 0;
    int sizeOldEntitys = 0;
    int sizeOldPropertysEntity = 0;

    int localOldChunkAddress = oldChunkAddress;
    localOldChunkAddress += ConvertChunkToData::sizeBiome1 + ConvertChunkToData::sizeBiome2 + ConvertChunkToData::sizeBiome2Info;
    if (countFillChunks > 0)
    {

        for (int x = 0; x < Chunk::sizeChunk * Chunk::sizeChunk; x++)
        {
            int id = ConvertChunkToData::getValueFromData(localOldChunkAddress, ConvertChunkToData::sizeIdBlock, data, STRIDE);
            int allSizeProperty = RegisteryBlocks::block[id]->propertyManager.allSize;
            sizeOldBlockPropertys += allSizeProperty;
            localOldChunkAddress += ConvertChunkToData::sizeIdBlock;
        }

        for (int x = 0; x < Chunk::sizeChunk * Chunk::sizeChunk; x++)
        {
            int id = ConvertChunkToData::getValueFromData(localOldChunkAddress, ConvertChunkToData::sizeIdBlock, data, STRIDE);
            int allSizeProperty = RegisteryBlocks::block[id]->propertyManager.allSize;
            sizeOldBackPropertys += allSizeProperty;
            localOldChunkAddress += ConvertChunkToData::sizeIdBlock;
        }
        sizeOldPropertys = sizeOldBlockPropertys + sizeOldBackPropertys;

        localOldChunkAddress += sizeOldPropertys;

        int countEntity = ConvertChunkToData::getValueFromData(localOldChunkAddress, ConvertChunkToData::sizeCountEntity, data, STRIDE);
        localOldChunkAddress += ConvertChunkToData::sizeCountEntity;

        sizeOldEntitys = countEntity * (ConvertChunkToData::sizeEntityPos * 2 + ConvertChunkToData::sizeIdEntity);

        for (int x = 0; x < countEntity; x++)
        {
            int id = ConvertChunkToData::getValueFromData(localOldChunkAddress + ConvertChunkToData::sizeEntityPos * 2, ConvertChunkToData::sizeIdEntity, data, STRIDE);
            int sizeAllPropertys = RegisteryEntity::entity[id]->propertyManager.allSize;
            sizeOldPropertysEntity += sizeAllPropertys;
            localOldChunkAddress += ConvertChunkToData::sizeEntityPos * 2 + ConvertChunkToData::sizeIdEntity;
        }


        sizeOldChunk = ConvertChunkToData::sizeBiome1 + ConvertChunkToData::sizeBiome2 + ConvertChunkToData::sizeBiome2Info + Chunk::sizeChunk * Chunk::sizeChunk * 2 + sizeOldPropertys
            + ConvertChunkToData::sizeCountEntity + sizeOldEntitys + sizeOldPropertysEntity;
        newChunkAddress = oldChunkAddress + sizeOldChunk;
    }
    else
    {
        newChunkXInData = sizeRegionPos * 2 + sizeAddress;
        newChunkAddress = (sizeRegionPos * 2 + sizeAddress) + sizeRegion * sizeRegion * (sizeRegionPos * 2 + sizeAddress);
    }

    int sizeNewChunk = 0;
    byte* chunkData = ConvertChunkToData::convertChunk(chunk, world, sizeNewChunk);

    int sizeNewRegionData = size + sizeNewChunk;
    byte* newRegionData = new byte[sizeNewRegionData];

    for (int x = 0; x < size; x++)
    {
        newRegionData[x] = data[x];
    }
    data = newRegionData;
    size = sizeNewRegionData;

    for (int x = newChunkAddress; x < size; x++)
    {
        data[x] = chunkData[x - newChunkAddress];
    }
    delete[sizeNewChunk] chunkData;

    pointer = newChunkXInData;

    ConvertChunkToData::setValueForData(countFillChunks + 1, sizeRegionPos * 2, sizeAddress, data, STRIDE);


    long value = chunk->chunkX + (int)(std::pow(2, sizeRegionPos * 8) / 2);
    ConvertChunkToData::setValueForData(chunk->chunkX + (int)(std::pow(2, sizeRegionPos * 8) / 2), pointer, sizeRegionPos, data, STRIDE);
    pointer += sizeRegionPos;

    ConvertChunkToData::setValueForData(chunk->chunkY + (int)(std::pow(2, sizeRegionPos * 8) / 2), pointer, sizeRegionPos, data, STRIDE);
    pointer += sizeRegionPos;

    ConvertChunkToData::setValueForData(newChunkAddress, pointer, sizeAddress, data, STRIDE);

    std::stringstream ss;
    ss << regionX;
    std::string str;
    ss >> str;
    while (str.size() < 5)
    {
        str.push_back('0');
    }

    ss = std::stringstream();
    ss << regionY;
    std::string str1;
    ss >> str1;
    while (str1.size() < 5)
    {
        str1.push_back('0');
    }

    std::string name = std::string(str) + std::string(str1);
    std::string path = ConvertRegionData::getPath(directoryToMaps + directioryToRegions + name + extensionRegion);


    std::ofstream writer(path, std::ofstream::binary);
    writer.write(reinterpret_cast<char*>(data), size);
    writer.close();
    delete[sizeNewRegionData] data;
}

void ConvertRegionData::haveChunk(unsigned long pointer, Chunk* chunk, int regionX, int regionY, World* world, unsigned char* data, int size)
{
    int chunkAddress = ConvertChunkToData::getValueFromData(pointer, sizeAddress, data, STRIDE);
    int chunkXInData = pointer - sizeRegionPos * 2;
    int endChunkAddress = 0;

    int oldSizeChunk = 0;
    int oldSizeBlockPropertys = 0;
    int oldSizeBackPropertys = 0;
    int oldSizePropertys = 0;
    int oldSizeEntitys = 0;
    int oldSizePropertysEntity = 0;

    int newSizeChunk = 0;

    int localChunkAddress = chunkAddress;
    localChunkAddress += ConvertChunkToData::sizeBiome1 + ConvertChunkToData::sizeBiome2 + ConvertChunkToData::sizeBiome2Info;

    for (int x = 0; x < Chunk::sizeChunk * Chunk::sizeChunk; x++)
    {
        int id = ConvertChunkToData::getValueFromData(localChunkAddress, ConvertChunkToData::sizeIdBlock, data, STRIDE);
        int allSizeProperty = RegisteryBlocks::block[id]->propertyManager.allSize;
        oldSizeBlockPropertys += allSizeProperty;
        localChunkAddress += ConvertChunkToData::sizeIdBlock;
    }

    for (int x = 0; x < Chunk::sizeChunk * Chunk::sizeChunk; x++)
    {
        int id = ConvertChunkToData::getValueFromData(localChunkAddress, ConvertChunkToData::sizeIdBlock, data, STRIDE);
        int allSizeProperty = RegisteryBlocks::block[id]->propertyManager.allSize;
        oldSizeBackPropertys += allSizeProperty;
        localChunkAddress += ConvertChunkToData::sizeIdBlock;
    }
    oldSizePropertys = oldSizeBlockPropertys + oldSizeBackPropertys;

    localChunkAddress += oldSizePropertys;

    int countEntity = ConvertChunkToData::getValueFromData(localChunkAddress, ConvertChunkToData::sizeCountEntity, data, STRIDE);
    localChunkAddress += ConvertChunkToData::sizeCountEntity;

    oldSizeEntitys = countEntity * (ConvertChunkToData::sizeEntityPos * 2 + ConvertChunkToData::sizeIdEntity);

    for (int x = 0; x < countEntity; x++)
    {
        int id = ConvertChunkToData::getValueFromData(localChunkAddress + ConvertChunkToData::sizeEntityPos * 2, ConvertChunkToData::sizeIdEntity, data, STRIDE);
        int sizeAllPropertys = RegisteryEntity::entity[id]->propertyManager.allSize;
        oldSizePropertysEntity += sizeAllPropertys;
        localChunkAddress += ConvertChunkToData::sizeEntityPos * 2 + ConvertChunkToData::sizeIdEntity;
    }


    oldSizeChunk = ConvertChunkToData::sizeBiome1 + ConvertChunkToData::sizeBiome2 + ConvertChunkToData:: sizeBiome2Info + Chunk::sizeChunk * Chunk::sizeChunk * 2 + oldSizePropertys
        + ConvertChunkToData::sizeCountEntity + oldSizeEntitys + oldSizePropertysEntity;

    byte* chunkData = ConvertChunkToData::convertChunk(chunk, world, newSizeChunk);

    endChunkAddress = chunkAddress + oldSizeChunk;

    int offsetChunk = newSizeChunk - oldSizeChunk;

    int sizeNewRegionData = 0;

    if (offsetChunk > 0) // Смещать вправо
    {
        sizeNewRegionData = (size - oldSizeChunk) + newSizeChunk;
        byte* newRegionData = new byte[sizeNewRegionData];
        for (int x = 0; x < size; x++)
        {
            newRegionData[x] = data[x];
        }
        size = sizeNewRegionData;
        data = newRegionData;

        for (int x = size - 1; x >= endChunkAddress + offsetChunk; x--)
        {
            data[x] = data[x - offsetChunk];
        }

        int countFillChunks = ConvertChunkToData::getValueFromData(sizeRegionPos * 2, sizeAddress, data, STRIDE);
        int numberChunk = (chunkXInData - (sizeRegionPos * 2 + sizeAddress)) / (sizeRegionPos * 2 + sizeAddress);
        numberChunk++;
        int localPointer = (sizeRegionPos * 2 + sizeAddress) + numberChunk * (sizeRegionPos * 2 + sizeAddress);
        for (int x = numberChunk; x < countFillChunks; x++)
        {
            int address = ConvertChunkToData::getValueFromData(localPointer + sizeRegionPos * 2, sizeAddress, data, STRIDE);
            address += offsetChunk;
            ConvertChunkToData::setValueForData(address, localPointer + sizeRegionPos * 2, sizeAddress, data, STRIDE);
            localPointer += sizeRegionPos * 2 + sizeAddress;
        }
    }
    else if (offsetChunk < 0) // Смещать влево
    {
        for (int x = endChunkAddress + offsetChunk; x < size + offsetChunk; x++)
        {
            data[x] = data[x - offsetChunk];
        }
        sizeNewRegionData = (size - oldSizeChunk) + newSizeChunk;
        byte* newRegionData = new byte[sizeNewRegionData];
        for (int x = 0; x < sizeNewRegionData; x++)
        {
            newRegionData[x] = data[x];
        }
        size = sizeNewRegionData;
        data = newRegionData;

        int countFillChunks = ConvertChunkToData::getValueFromData(sizeRegionPos * 2, sizeAddress, data, STRIDE);
        int numberChunk = (chunkXInData - (sizeRegionPos * 2 + sizeAddress)) / (sizeRegionPos * 2 + sizeAddress);
        numberChunk++;
        int localPointer = (sizeRegionPos * 2 + sizeAddress) + numberChunk * (sizeRegionPos * 2 + sizeAddress);
        for (int x = numberChunk; x < countFillChunks; x++)
        {
            int address = ConvertChunkToData::getValueFromData(localPointer + sizeRegionPos * 2, sizeAddress, data, STRIDE);
            address += offsetChunk;
            ConvertChunkToData::setValueForData(address, localPointer + sizeRegionPos * 2, sizeAddress, data, STRIDE);
            localPointer += sizeRegionPos * 2 + sizeAddress;
        }
    }

    for (int x = chunkAddress; x < chunkAddress + newSizeChunk; x++)
    {
        data[x] = chunkData[x - chunkAddress];
    }



    std::stringstream ss;
    ss << regionX;
    std::string str;
    ss >> str;
    while (str.size() < 5)
    {
        str.push_back('0');
    }

    ss = std::stringstream();
    ss << regionY;
    std::string str1;
    ss >> str1;
    while (str1.size() < 5)
    {
        str1.push_back('0');
    }

    std::string name = std::string(str) + std::string(str1);
    std::string path = ConvertRegionData::getPath(directoryToMaps + directioryToRegions + name + extensionRegion);


    std::ofstream writer(path, std::ofstream::binary);
    writer.write(reinterpret_cast<char*>(data), size);
    writer.close();

    delete[newSizeChunk] chunkData;

    if (offsetChunk > 0 || offsetChunk < 0)
    {
        delete[sizeNewRegionData] data;
    }
}

Chunk* ConvertRegionData::getChunkFromDataRegion(int chunkX, int chunkY, World* world)
{
    int regionX = 0;
    int regionY = 0;

    if (chunkX >= 0)
    {
        regionX = (chunkX / ConvertRegionData::sizeRegion);
    }
    else
    {
        if (abs(chunkX * 1.00f / ConvertRegionData::sizeRegion) - abs(chunkX / ConvertRegionData::sizeRegion) > 0)
        {
            regionX = chunkX / ConvertRegionData::sizeRegion - 1;
        }
        else
        {
            regionX = chunkX / ConvertRegionData::sizeRegion;
        }
    }

    if (chunkY >= 0)
    {
        regionY = (chunkY / ConvertRegionData::sizeRegion);
    }
    else
    {

        if (abs(chunkY * 1.00f / ConvertRegionData::sizeRegion) - abs(chunkY / ConvertRegionData::sizeRegion) > 0)
        {
            regionY = chunkY / ConvertRegionData::sizeRegion - 1;
        }
        else
        {
            regionY = chunkY / ConvertRegionData::sizeRegion;
        }
    }

    // Пункт 1
    std::stringstream ss;
    ss << regionX;
    std::string str;
    ss >> str;
    while (str.size() < 5)
    {
        str.push_back('0');
    }

    ss = std::stringstream();
    ss << regionY;
    std::string str1;
    ss >> str1;
    while (str1.size() < 5)
    {
        str1.push_back('0');
    }

    std::string name = std::string(str) + std::string(str1);
    std::string path = ConvertRegionData::getPath(directoryToMaps + directioryToRegions + name + extensionRegion);

    std::ifstream reader;

    reader.open(path, std::ifstream::binary);

    unsigned char* data = nullptr;
    int sizeData = 0;

    bool readerIsOpen = false;

    std::vector<unsigned char> fileData;

    bool isOpen = false;

    if (reader.is_open())
    {
        char ch = 0;
        while (reader.get(ch))
        {
            fileData.push_back(ch);
        }
        data = fileData.data();
        sizeData = fileData.size();
        readerIsOpen = true;
        isOpen = true;
    }
    else
    {
        isOpen = false;
    }

    reader.close();

    Chunk* chunk = nullptr;

    if (isOpen == true)
    {
        //Пункт 2

        int pointer = sizeRegionPos * 2 + sizeAddress;
        int countFillChunks = ConvertChunkToData::getValueFromData(sizeRegionPos * 2, sizeAddress, data, STRIDE);
        bool isMatches = false;

        int l = (pointer - (sizeRegionPos * 2 + sizeAddress)) / (sizeRegionPos * 2 + sizeAddress);


        while ((pointer - (sizeRegionPos * 2 + sizeAddress)) / (sizeRegionPos * 2 + sizeAddress) < countFillChunks)
        {
            int regionChunkX = ConvertChunkToData::getValueFromData(pointer, sizeRegionPos, data, STRIDE) - ((int)(std::pow(2, sizeRegionPos * 8) / 2));
            pointer += sizeRegionPos;

            int regionChunkY = ConvertChunkToData::getValueFromData(pointer, sizeRegionPos, data, STRIDE) - ((int)(std::pow(2, sizeRegionPos * 8) / 2));
            pointer += sizeRegionPos;

            if (chunkX == regionChunkX && chunkY == regionChunkY)
            {
                isMatches = true;
                break;
            }
            else
            {
                pointer += sizeAddress;
            }
        }

        if (isMatches)
        {

            //Пункт 3
            pointer = ConvertChunkToData::getValueFromData(pointer, sizeAddress, data, STRIDE);

            int sizeBlockPropertys = 0;
            int sizeBackPropertys = 0;
            int sizePropertys = 0;
            int sizeEntitys = 0;
            int sizePropertysEntity = 0;
            int sizeChunk = 0;

            int localPointer = pointer + ConvertChunkToData::sizeBiome1 + ConvertChunkToData::sizeBiome2 + ConvertChunkToData::sizeBiome2Info;

            for (int x = 0; x < Chunk::sizeChunk * Chunk::sizeChunk; x++)
            {
                int id = ConvertChunkToData::getValueFromData(localPointer, ConvertChunkToData::sizeIdBlock, data, STRIDE);
                int allSizeProperty = RegisteryBlocks::block[id]->propertyManager.allSize;
                sizeBlockPropertys += allSizeProperty;
                localPointer += ConvertChunkToData::sizeIdBlock;
            }

            for (int x = 0; x < Chunk::sizeChunk * Chunk::sizeChunk; x++)
            {
                int id = ConvertChunkToData::getValueFromData(localPointer, ConvertChunkToData::sizeIdBlock, data, STRIDE);
                int allSizeProperty = RegisteryBlocks::block[id]->propertyManager.allSize;
                sizeBackPropertys += allSizeProperty;
                localPointer += ConvertChunkToData::sizeIdBlock;
            }
            sizePropertys = sizeBlockPropertys + sizeBackPropertys;

            localPointer += sizePropertys;

            int countEntity = ConvertChunkToData::getValueFromData(localPointer, ConvertChunkToData::sizeCountEntity, data, STRIDE);
            localPointer += ConvertChunkToData::sizeCountEntity;

            sizeEntitys = countEntity * (ConvertChunkToData::sizeEntityPos * 2 + ConvertChunkToData::sizeIdEntity);

            for (int x = 0; x < countEntity; x++)
            {
                int id = ConvertChunkToData::getValueFromData(localPointer + ConvertChunkToData::sizeEntityPos * 2, ConvertChunkToData::sizeIdEntity, data, STRIDE);
                int sizeAllPropertys = RegisteryEntity::entity[id]->propertyManager.allSize;
                sizePropertysEntity += sizeAllPropertys;
                localPointer += ConvertChunkToData::sizeEntityPos * 2 + ConvertChunkToData::sizeIdEntity;
            }


            sizeChunk = ConvertChunkToData::sizeBiome1 + ConvertChunkToData::sizeBiome2 + ConvertChunkToData::sizeBiome2Info + Chunk::sizeChunk * Chunk::sizeChunk * 2 + sizePropertys
                + ConvertChunkToData::sizeCountEntity + sizeEntitys + sizePropertysEntity;

            //Пункт 4
            byte* chunkData = new byte[sizeChunk];

            for (int x = pointer; x < pointer + sizeChunk; x++)
            {
                chunkData[x - pointer] = data[x];
            }

            //Пункт 5
            chunk = ConvertChunkToData::recoveryChunk(chunkData, chunkX, chunkY, world);

            delete[sizeChunk] chunkData;

        }
    }
    //Пункт 6
    return chunk;
}

