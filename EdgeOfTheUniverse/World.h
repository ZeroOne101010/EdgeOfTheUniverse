#pragma once
#include "AlterableHeader.h"
#include "OpenGLEngine/RectangleShape.h"
#include "Chunk.h"
#include "Entity.h"
#include "RegisteryBlocks.h"
#include "RegisteryEntity.h"
#include "ConvertRegionData.h"
#include "ICloseObject.h";
#include "RandomCoor.h"
#include "Biome.h"
#include"BiomeAir.h"
#include "Cursor.h"

class Map;

using namespace glm;
class World : public Alterable, public IDraw
{
public:
	World(int seed, Map* map);
	~World();

	static const int countActiveChunks;

	Map* map;
	Chunk** chunk;
	int chunkPointer = 0;
	int seed;
	vec2 camera = vec2(0, 0);
	RandomCoor* rand;

	std::vector<Biome*> biome;

	std::vector<Entity*> entity;
	Entity* addEntity(int posX, int posY, int id);

	Biome* defaulBiome = new BiomeAir();
	void addBiome(Biome* biome);
	Biome* getChunkBiome(int chunkX, int chunkY);
	Biome* getBlockBiome(int posX, int posY);


	Chunk* generationChunk(int chunkX, int chunkY);
	Chunk** getChunk(int chunkX, int chunkY);
	Chunk** getChunkWithoutThread(int chunkX, int chunkY);
	Chunk** getChunkWithoutThreadByBlockPosition(int blockX, int blockY);
	Chunk** getChunkByBlockPosition(int posX, int posY);
	Chunk** getChunkByBlockPositionNotGenerationWithoutThread(int blockX, int blockY);
	Chunk** getChunkWithoutThreadNotGeneration(int chunkX, int chunkY);
	Block** getBlockByBlockPosition(int posX, int posY, bool isBackBlock);

	Chunk** getChunkNotGeneration(int chunkX, int chunkY);
	Chunk** getChunkByBlockPositionNotGeneration(int posX, int posY);
	Block** getBlockNotGeneration(int posX, int posY, bool isBackBlock);
	void updateCloseChunk(Chunk* chunk);
	void setBlock(int blockX, int blockY, int id, bool isBackBlock);
	void setBlocks(int blockX, int blockY, int width, int height, int id, bool isBackBlock);

	void rendererBlock(Block* block, Renderer* renderer, Alterable alters);

	virtual void draw(Renderer* renderer, Alterable alters) override;
	int countChunks;
	int chunkRendererSize = 0;
	int rendererChunkX = 0;
	int rendererChunkY = 0;
	int rendererBlockX = 0;
	int rendererBlockY = 0;
	int rendererCountBlocksInCameraX = 0;
	int rendererCountBlocksInCameraY = 0;
	int rendererCountChunksInCameraX = 0;
	int rendererCountChunksInCameraY = 0;
	int oldWidth = 0;
	int oldHeight = 0;
	vec2 leftTopAngleCamera = vec2(0, 0);
	Chunk*** chunkRenderer = nullptr;
};

