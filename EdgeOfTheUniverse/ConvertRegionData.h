#pragma once
#include<fstream>
#include "ConvertChunkToData.h"

#define STOP_NAME 52428

class ConvertRegionData
{
public:
    /* CHUNK DATA:
* 1. ������ ���� ����� (2 �����)
* 2. ������ ���� ����� (2 �����)
* 3. �������� 2 ����� ����� (2 �����)
* 4. id ���� ������
* 5. ��������� ������
*/

/* ����� ��������� �����, ���������� � ���� ������������ ��������� ������, ������� ����� ����������� ��������� �������:
 * REGION DATA:
 * 1. ������� ������� X (2 �����)
 * 2. ������� ������� Y (2 �����)
 * 3. ���������� ����������� ������ ��� ����� (2 �����)
 * 4. ������ �� �����:
 *       4.1 ������� ����� �� X (2 �����)
 *       4.2 ������� ����� �� Y (2 �����)
 *       4.3 ������ �� ���� � region data (2 �����)
 * 5. �����
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

     /*������ ������� notHaveChunk: (�������� �������������� :D)
     * ���� ����� ���� � RegionData:
     * 1. ������ ������� ���������� �� region.Lenght + sizeNewChunk
     * 2. pointer ������������ �� �����  (sizeRegionPos * 2 + sizeAddress) + getValueFromData(sizeRegionPos * 2, sizeAddress) * (sizeRegionPos * 2 + sizeAddress), 
     *  �� ���� ��������� �� ����������� ������ ��� ������
     * 3. ������ ����� �������� ������ �� ��������� ������ ����� ��� �����(lastChunkAddress):
     *      3.1 ������� ����� �� ������ � RegionReference: regionReference = getValueFromData(pointer - sizeAddress, sizeAddress) 
     *      3.2 lastChunkAddress = getValueFromData(regionReference + (sizeRegionPos * 2), sizeAddress) 
     *      ----3.3 ������� ������ ���� ���������� �����, �� ���� sizePropertys
     *      ----3.4 ������� ������ �����, �� ���� sizeChunk = Chunk.sizeChunk * Chunk.sizeChunk * 2 + sizePropertys
     *      ----3.5 newChunkAddress = lastChunkAddress + sizeChunk
     * 4. �������� ����� �� ��������� ����, ��������  setValueForData((pointer - (sizeRegionPos * 2 + sizeAddress)) / (sizeRegionPos * 2 + sizeAddress), sizeRegionPos * 2, sizeAddress);
     * 5. ����� ��������� setValueForData(chunk.chunkX, pointer, sizeRegionPos). ����� pointer += sizeRegionPos
     * 6. ����� ��������� setValueForData(chunk.chunkY, pointer, sizeRegionPos). ����� pointer += sizeRegionPos
     * 7. ����� ��������� setValueForData(lastChunkAddress + sizeChunk, pointer, sizeAddress). ����� pointer += sizeAddress
     * 8. pointer ������������ �� ��������� ����� ��� ����, �� ���� newChunkAddress
     * 9. �������� ������ byte[] chunkData = ConvertChunkToData.convertChunk(chunk)
     * 10. ���������� �������� chunkData � ������ data � ������� ����� � ������ pointer, �� ������ data.Lenght
     * 11. ��������� ���� � ����� data
     */
    static void notHaveChunk(unsigned long pointer, Chunk* chunk, int regionX, int regionY, World* world, unsigned char* data, int size);


    /* ������ ������ haveChunk: (��� ��������, �� ���� �����)
     * ���� � regionData ��� ���� ����, ��:
     * 1. ������������� ������ �����, ������� ����� ������
     *      1.1 ��������� ������������ �� ����
     *      1.2 � ������� ������� getSizePropertys ������������ ������ �������� ����� ������� ������ � ������� ������
     *      1.3 ������ �������� ����� ������������ � Chunk.sizeChunk * Chunk.sizeChunk * 2. � ����� ������ ����� ����� �����: 
     *      Chunk.sizeChunk * Chunk.sizeChunk * 2 + sizePropertysBlock + sizePropertysBackBlock
     * 2. ������ regionData ���������� �����: (regionData.Lenght - oldSizeChunk) + newSizeChunk. 
     * 3. ��� �����, ����� ������� ����� ��������� �� ������ oldSizeChunk - newSizeChunk(���� ����� �������������, �� ������� ����� ����� �����)
     * 4. ����� ���� ������������ � regionData � ������ oldAddress �� ������ oldAddress + newSizeChunk. 
     * 5. ��� ������ �� ����� ����� ������ �����, ������� ��� ������ ��������� ��� �� �� �������� oldSizeChunk - newSizeChunk
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

