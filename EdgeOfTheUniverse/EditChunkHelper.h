#pragma once
#include "RegisteryBlocks.h"
#include "World.h"
class EditChunkHelper
{
public:
	static Block** getNeighboringBlock(int x, int y, Block*** block, int sizeX, int sizeY);
	static void setGrass(Chunk* chunk, Block*** block, Block*** backBlock, BlockName* nameGrass, int sizeBlockX, int sizeBlockY, int sizeNameGrass);
	static void setGrass(Chunk* chunk, Block*** block, Block*** backBlock, BlockName nameGrass, int sizeBlockX, int sizeBlockY);
	static void setGrass(Chunk* chunk, Block*** block, Block*** backBlock, int* idGrass, int sizeIdGrass, int sizeBlockX, int sizeBlockY);
	static void setGrass(Chunk* chunk, Block*** block, Block*** backBlock, int idGrass, int sizeBlockX, int sizeBlockY);
	static void setGrass(Chunk* chunk, Block*** block, Block*** backBlock, int idGrass, int grassBlockPlace, int sizeBlockX, int sizeBlockY);
};

