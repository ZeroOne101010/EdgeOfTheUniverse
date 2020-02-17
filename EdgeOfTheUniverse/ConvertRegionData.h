#pragma once
#include<fstream>
#include "ConvertChunkToData.h"

#define STOP_NAME 52428

class ConvertRegionData
{
public:
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
 */

    static int sizeRegion;

    static int sizeRegionPos;
    static int sizeAddress;

    static const std::string directoryToMaps;
    static const std::string directioryToRegions;
    static const std::string extensionRegion;

    static int offsetEncoding;

    static void setDataToUnicode(unsigned char* data);
    static std::string getPath(char* localPath, int size);
    static std::string getPath(std::string localPath);

    static unsigned char* createRegionFile(int regionX, int regionY, int& size);
    static void saveChunkDataToRegion(Chunk* chunk, World* world);

     /*РАБОТА МАЕТОДА notHaveChunk: (выглядит сложновательно :D)
     * Если чанка нету в RegionData:
     * 1. Размер региона изменяется на region.Lenght + sizeNewChunk
     * 2. pointer перемещается на адрес  (sizeRegionPos * 2 + sizeAddress) + getValueFromData(sizeRegionPos * 2, sizeAddress) * (sizeRegionPos * 2 + sizeAddress), 
     *  то есть последняя не заполненная ячейка под ссылку
     * 3. Теперь нужно получить ссылку на последнее пустое место для чанка(lastChunkAddress):
     *      3.1 Находим адрес на ссылку в RegionReference: regionReference = getValueFromData(pointer - sizeAddress, sizeAddress) 
     *      3.2 lastChunkAddress = getValueFromData(regionReference + (sizeRegionPos * 2), sizeAddress) 
     *      ----3.3 Находит размер всех параметров чанка, то есть sizePropertys
     *      ----3.4 Находит размер чанка, то есть sizeChunk = Chunk.sizeChunk * Chunk.sizeChunk * 2 + sizePropertys
     *      ----3.5 newChunkAddress = lastChunkAddress + sizeChunk
     * 4. Изменить адрес на последний чанк, выполнив  setValueForData((pointer - (sizeRegionPos * 2 + sizeAddress)) / (sizeRegionPos * 2 + sizeAddress), sizeRegionPos * 2, sizeAddress);
     * 5. Затем выполняет setValueForData(chunk.chunkX, pointer, sizeRegionPos). Потом pointer += sizeRegionPos
     * 6. Затем выполняет setValueForData(chunk.chunkY, pointer, sizeRegionPos). Потом pointer += sizeRegionPos
     * 7. Затем выполняет setValueForData(lastChunkAddress + sizeChunk, pointer, sizeAddress). Потом pointer += sizeAddress
     * 8. pointer перемещается на свободное место под чанк, то есть newChunkAddress
     * 9. Получаем массив byte[] chunkData = ConvertChunkToData.convertChunk(chunk)
     * 10. Записываем значение chunkData в массив data с помощью цикла с адреса pointer, до адреса data.Lenght
     * 11. Сохраняем файл с новым data
     */
    static void notHaveChunk(unsigned long pointer, Chunk* chunk, int regionX, int regionY, World* world, unsigned char* data, int size);


    /* РАБОТА МЕТОДА haveChunk: (Уже поменьше, но тоже много)
     * Если в regionData уже есть чанк, то:
     * 1. Определсяется размер чанка, который будет заменён
     *      1.1 Указатель перемещатеся на чанк
     *      1.2 С помощью функции getSizePropertys записывается размер настроек чанка фоновых блоков и обычных блоков
     *      1.3 Размер настроек чанка прибавляется к Chunk.sizeChunk * Chunk.sizeChunk * 2. В итоге размер чанка будет такой: 
     *      Chunk.sizeChunk * Chunk.sizeChunk * 2 + sizePropertysBlock + sizePropertysBackBlock
     * 2. Размер regionData становится таким: (regionData.Lenght - oldSizeChunk) + newSizeChunk. 
     * 3. Все чанки, после старого чанка смещаются на размер oldSizeChunk - newSizeChunk(если число отрицательное, то смещать чанки нужно влево)
     * 4. Новый чанк записывается в regionData с адреса oldAddress до адреса oldAddress + newSizeChunk. 
     * 5. Все адреса на чанки после адреса чанка, который был заменён смещаются так же на значение oldSizeChunk - newSizeChunk
     * 
     */
    static void haveChunk(unsigned long pointer, Chunk* chunk, int regionX, int regionY, World* world, unsigned char* data, int size);
    static Chunk* getChunkFromDataRegion(int chunkX, int chunkY, World* world);

private:
	struct RegionPosState
	{
		int regionX;
		int regionY;
	};
};

