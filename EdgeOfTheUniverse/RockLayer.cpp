#include "RockLayer.h"
//Biome(20, 20, 234, 1233, 1, 1, 1, 0, 1, 50) - ��������� ��� ����������� ������ ����� (������ ����� ��� �� ��������, ��� � ������������ �������� ����)
RockLayer::RockLayer(float limitUp, float limitDown) : Biome(20, 20, 234, 1233, 1, 1, 1, 0, 1, 50)
{
	setLandshaft(Chunk::sizeChunk, Chunk::sizeChunk, 1, 1, 5, 0, 0);
	addSpawnBlock(RegisteryBlocks::block[4], 20, 20, 3456, 123, 5, 4, 1);
}

Biome* RockLayer::getNewBiome()
{
	return nullptr;
}
