#include "World.h"
#include "Biome.h"
int Biome::biomeOffsetLimited = 0;

Biome::Biome(int offsetX, int offsetY, float offsetPosX, float offsetPosY, float sizeNoiseX, float sizeNoiseY, float high, float highSection, float limitUp, float limitDown)
{
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->offsetPosX = offsetPosX;
	this->offsetPosY = offsetPosY;
	this->sizeNoiseX = sizeNoiseX;
	this->sizeNoiseY = sizeNoiseY;
	this->high = high;
	this->highSection = highSection;
	this->limitUp = limitUp;
	this->limitDown = limitDown;
}

Biome::Biome(int offsetX, int offsetY, float offsetPosX, float offsetPosY, float sizeNoiseX, float sizeNoiseY, float high, float highSection, float limitUp, float limitDown, 
    int offsetXLandshaft, int offsetYLandshaft, float sizeNoiseXLandshaft, float sizeNoiseYLandshaft, float highLandshaft)
{
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    this->offsetPosX = offsetPosX;
    this->offsetPosY = offsetPosY;
    this->sizeNoiseX = sizeNoiseX;
    this->sizeNoiseY = sizeNoiseY;
    this->high = high;
    this->highSection = highSection;
    this->limitUp = limitUp;
    this->limitDown = limitDown;

    this->offsetXLandshaft = offsetXLandshaft;
    this->offsetYLandshaft = offsetYLandshaft;
    this->sizeNoiseXLandshaft = sizeNoiseXLandshaft;
    this->sizeNoiseYLandshaft = sizeNoiseYLandshaft;
    this->highLandshaft = highLandshaft;
}

Biome::Biome()
{
    this->offsetX = 0;
    this->offsetY = 0;
    this->offsetPosX = 0;
    this->offsetPosY = 0;
    this->sizeNoiseX = 0;
    this->sizeNoiseY = 0;
    this->high = 0;
    this->highSection = 0;
    this->limitUp = 0;
    this->limitDown = 0;
}

Biome* Biome::createBiome(World* world)
{
	Biome* biome = nullptr;
	biome = getNewBiome();
	biome->id = id;
	return biome;
}


void Biome::setLandshaft(int offsetXLandshaft, int offsetYLandshaft, float sizeNoiseXLandshaft, float sizeNoiseYLandshaft, float highLandshaft)
{
	this->offsetXLandshaft = offsetXLandshaft;
	this->offsetYLandshaft = offsetYLandshaft;
	this->sizeNoiseXLandshaft = sizeNoiseXLandshaft;
	this->sizeNoiseYLandshaft = sizeNoiseYLandshaft;
	this->highLandshaft = highLandshaft;
}

void Biome::setLandshaft(int offsetXLandshaft, int offsetYLandshaft, float sizeNoiseXLandshaft, float sizeNoiseYLandshaft, float highLandshaft, float kMaxHighMounties)
{
    this->offsetXLandshaft = offsetXLandshaft;
    this->offsetYLandshaft = offsetYLandshaft;
    this->sizeNoiseXLandshaft = sizeNoiseXLandshaft;
    this->sizeNoiseYLandshaft = sizeNoiseYLandshaft;
    this->highLandshaft = highLandshaft;
    this->kMaxHighMounties = kMaxHighMounties;
}

bool Biome::toSpawnBiome(int posX, int posY, RandomCoor* rand)
{
    float answer = PerlinNoise::getPerlinNoise((posX + offsetPosX) / (sizeNoiseX / 5), (posY + offsetPosY) / (sizeNoiseY / 5), (int)offsetX, (int)offsetY, rand);
    answer *= high;
    bool toSpawn = false;

    if (posY < limitDown - biomeOffsetLimited && posY > limitUp + biomeOffsetLimited)
    {
        if (answer > highSection)
        {
            toSpawn = true;
        }
    }
    else
    {
        float t = 0;
        if (posY >= limitDown - biomeOffsetLimited)
        {
            t = (biomeOffsetLimited - (limitDown - posY)) / biomeOffsetLimited;
        }
        else if (posY <= limitUp + biomeOffsetLimited)
        {
            t = (biomeOffsetLimited - (posY - limitUp)) / biomeOffsetLimited;
        }
        else
        {
            t = 1;
        }

        if (t < 0) t = 0;
        if (t > 1) t = 1;

        float section = highSection + (offsetY * BlockSpawner::kLimit * high * sizeNoiseY - highSection) * t;

        if (answer > section)
        {
            toSpawn = true;
        }
    }

    return toSpawn;
}

void Biome::editChunk(Chunk* chunk, Block*** block, Block*** backBlock, int sizeBlockX, int sizeBlockY)
{
    // Эта функция будет переопределяться в других класах.
}

void Biome::addSpawnBlock(Block* block, float offsetX, float offsetY, float offsetPosX, float offsetPosY, float high, float highSection, float limitUp, float limitDown, float sizeNoise)
{
    BlockSpawner blockSpawner = BlockSpawner(block, offsetX, offsetY, offsetPosX, offsetPosY, high, highSection, limitUp, limitDown, sizeNoise);
    spawnBlock.push_back(blockSpawner);
}

void Biome::addSpawnBackBlock(Block* block, float offsetX, float offsetY, float offsetPosX, float offsetPosY, float high, float highSection, float limitUp, float limitDown, float sizeNoise)
{
    BlockSpawner blockSpawner = BlockSpawner(block, offsetX, offsetY, offsetPosX, offsetPosY, high, highSection, limitUp, limitDown, sizeNoise);
    spawnBackBlock.push_back(blockSpawner);
}

void Biome::addSpawnBlock(Block* block, float offsetX, float offsetY, float offsetPosX, float offsetPosY, float high, float highSection, float sizeNoise)
{
    BlockSpawner blockSpawner = BlockSpawner(block, offsetX, offsetY, offsetPosX, offsetPosY, high, highSection, -100000000, 100000000, sizeNoise);
    spawnBlock.push_back(blockSpawner);
}

void Biome::addSpawnBackBlock(Block* block, float offsetX, float offsetY, float offsetPosX, float offsetPosY, float high, float highSection, float sizeNoise)
{
    BlockSpawner blockSpawner = BlockSpawner(block, offsetX, offsetY, offsetPosX, offsetPosY, high, highSection, -100000000, 100000000, sizeNoise);
    spawnBackBlock.push_back(blockSpawner);
}

Block* Biome::getBiomeBlock(int blockX, int blockY, World* world)
{
    Block* generateBlock = nullptr;
    for (int z = 0; z < spawnBlock.size(); z++)
    {
        bool toCreate = spawnBlock[z].toCreateBlock(blockX, blockY, world->rand);
        if (toCreate)
        {
            generateBlock = spawnBlock[z].block;
        }
    }
    if (generateBlock == nullptr)
    {
        generateBlock = RegisteryBlocks::block[0]; // Воздух
    }
    return generateBlock;
}

Block* Biome::getBiomeBackBlock(int blockX, int blockY, World* world)
{
    Block* generateBlock = nullptr;
    for (int z = 0; z < spawnBackBlock.size(); z++)
    {
        bool toCreate = spawnBlock[z].toCreateBlock(blockX, blockY, world->rand);
        if (toCreate)
        {
            generateBlock = spawnBackBlock[z].block;
        }
    }
    if (generateBlock == nullptr)
    {
        generateBlock = RegisteryBlocks::block[0]; // Воздух
    }
    return generateBlock;
}

Block* Biome::getBiomeBlock(int blockX, int blockY, float tSection, World* world)
{
    Block* generateBlock = nullptr;
    for (int z = 0; z < spawnBlock.size(); z++)
    {
        bool toCreate = spawnBlock[z].toCreateBlock(blockX, blockY, tSection, world->rand);
        if (toCreate)
        {
            generateBlock = spawnBlock[z].block;
        }
    }
    if (generateBlock == nullptr)
    {
        generateBlock = RegisteryBlocks::block[0]; // Воздух
    }

    return generateBlock;
}

bool Biome::needCreateBiomeBlock(int blockX, int blockY, float tSection, World* world)
{
    Block* generateBlock = nullptr;
    bool toCreateBiomeBlock = true;

    for (int z = 0; z < spawnBlock.size(); z++)
    {
        bool toCreate = spawnBlock[z].toCreateBlock(blockX, blockY, tSection, world->rand);
        if (toCreate)
        {
            generateBlock = spawnBlock[z].block;
        }
    }
    if (generateBlock == nullptr)
    {
        toCreateBiomeBlock = false;
    }
    return toCreateBiomeBlock;
}

Block* Biome::getBiomeBlockWithTransition(int blockX, int blockY, float tSection, bool isBackBlock, Biome* biome, World* world)
{
    Block* generateBlock = nullptr;

    bool isHaveSpawner = false;
    BlockSpawner* findSpawner = nullptr;
    BlockSpawner* selfSpawner = nullptr;
    if (!isBackBlock)
    {

        int idBlockSpawner = 0;
        for (int z = 0; z < spawnBlock.size(); z++)
        {
            bool toCreate = spawnBlock[z].toCreateBlock(blockX, blockY, world->rand);
            if (toCreate)
            {
                idBlockSpawner = z;
            }
        }

        BlockSpawner* spawner = &spawnBlock[idBlockSpawner];
        selfSpawner = spawner;
        for (int x = 0; x < biome->spawnBlock.size(); x++)
        {
            if (biome->spawnBlock[x].block == spawner->block)
            {
                isHaveSpawner = true;
                findSpawner = &biome->spawnBlock[x];
                break;
            }
        }
    }
    else
    {
        if (spawnBackBlock.size() > 0)
        {
            int idBlockSpawner = 0;
            for (int z = 0; z < spawnBackBlock.size(); z++)
            {
                bool toCreate = spawnBackBlock[z].toCreateBlock(blockX, blockY, world->rand);
                if (toCreate)
                {
                    idBlockSpawner = z;
                }
            }

            BlockSpawner* spawner = &spawnBackBlock[idBlockSpawner];
            selfSpawner = spawner;
            for (int x = 0; x < biome->spawnBackBlock.size(); x++)
            {
                if (biome->spawnBackBlock[x].block == spawner->block)
                {
                    isHaveSpawner = true;
                    findSpawner = &biome->spawnBackBlock[x];
                    break;
                }
            }
        }
    }

    if (isHaveSpawner) // Если такой же спавнер есть, то интрополируем значение шума перлина и проверяем, стоит ли создать блок уже у новога спавнеря
    {
        BlockSpawner transitionSpawner = BlockSpawner(findSpawner->block, PerlinNoise::lerp(tSection, selfSpawner->offsetX, findSpawner->offsetX), PerlinNoise::lerp(tSection, selfSpawner->offsetY, findSpawner->offsetY),
            PerlinNoise::lerp(tSection, selfSpawner->offsetPosX, findSpawner->offsetPosX), PerlinNoise::lerp(tSection, selfSpawner->offsetPosY, findSpawner->offsetPosY), PerlinNoise::lerp(tSection, selfSpawner->high, findSpawner->high),
            PerlinNoise::lerp(tSection, selfSpawner->highSection, findSpawner->highSection), PerlinNoise::lerp(tSection, selfSpawner->limitUp, findSpawner->limitUp), PerlinNoise::lerp(tSection, selfSpawner->limitDown, findSpawner->limitDown),
            PerlinNoise::lerp(tSection, selfSpawner->sizeNoise, findSpawner->sizeNoise)); // До того, как я интрополировал значения, выглядело попроще :D
        bool toCreateBlock = transitionSpawner.toCreateBlock(blockX, blockY, world->rand);
        if (toCreateBlock)
        {
            generateBlock = transitionSpawner.block;
        }
        else
        {
            generateBlock = RegisteryBlocks::block[0]; // Если блок не получится создать, то под ним будет воздух
        }
    }
    else // Если у соседнего биома нету такого же спавнера, то просто получаем значения с tSection, вместо интрополяции значений с другим биомом
    {
        if (!isBackBlock)
        {
            generateBlock = getBiomeBlock(blockX, blockY, tSection, world);
        }
        else
        {
            generateBlock = getBiomeBackBlock(blockX, blockY, tSection, world);
        }
    }


    return generateBlock;
}

Block* Biome::getBiomeBackBlock(int blockX, int blockY, float tSection, World* world)
{
    Block* generateBlock = nullptr;
    for (int z = 0; z < spawnBackBlock.size(); z++)
    {
        bool toCreate = spawnBackBlock[z].toCreateBlock(blockX, blockY, tSection, world->rand);
        if (toCreate)
        {
            generateBlock = spawnBackBlock[z].block;
        }
    }
    if (generateBlock == nullptr)
    {
        generateBlock = RegisteryBlocks::block[0]; // воздух;
    }
    return generateBlock;
}

void Biome::setBorderChunk(Chunk* chunk, World* world)
{
    int chunkX = chunk->chunkX;
    int chunkY = chunk->chunkY;
    Biome* biomeUp = world->getChunkBiome(chunkX, chunkY - 1);
    Biome* biomeUpLeft = world->getChunkBiome(chunkX - 1, chunkY - 1);
    Biome* biomeUpRight = world->getChunkBiome(chunkX + 1, chunkY - 1);

    Biome* biomeRight = world->getChunkBiome(chunkX + 1, chunkY);

    Biome* biomeDown = world->getChunkBiome(chunkX, chunkY + 1);
    Biome* biomeDownLeft = world->getChunkBiome(chunkX - 1, chunkY + 1);
    Biome* biomeDownRight = world->getChunkBiome(chunkX + 1, chunkY + 1);

    Biome* biomeLeft = world->getChunkBiome(chunkX - 1, chunkY);

    float t = 0;
    Block* localBlock = nullptr;
    if (biomeUp->id > id)
    {
        int offsetSmoothBorder = biomeUp->offsetSmoothBorder;
        if (offsetSmoothBorder > Chunk::sizeChunk - 1) offsetSmoothBorder = Chunk::sizeChunk - 1;
        for (int x = 0; x < Chunk::sizeChunk; x++)
            for (int y = 0; y < offsetSmoothBorder; y++)
            {
                t = y / (offsetSmoothBorder * 1.00f);
                bool toCreateBiomeBlock = needCreateBiomeBlock(x, y, t, world);
                localBlock = biomeUp->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, false, this, world);
                if (localBlock->id != 0 && biomeUp->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world))
                {
                    delete chunk->block[x][y];
                    chunk->block[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, false, world);
                }

                Block* realBlock = localBlock;

                localBlock = biomeUp->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, true, this, world);

                if (localBlock->id != 0 && biomeUp->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world))
                {
                    delete chunk->backBlock[x][y];
                    chunk->backBlock[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, true, world);
                }
            }
    }


    if (biomeUpLeft->id > id)
    {
        offsetSmoothBorder = biomeUpLeft->offsetSmoothBorder;
        offsetSmoothBorder = offsetSmoothBorder / 2;
        if (offsetSmoothBorder > Chunk::sizeChunk - 1) offsetSmoothBorder = Chunk::sizeChunk - 1;
        t = 0;
        for (int x = 0; x < offsetSmoothBorder; x++)
            for (int y = 0; y < offsetSmoothBorder; y++)
            {
                float dY = y;
                float dX = x;

                float maxT = offsetSmoothBorder * 2;
                t = (dX + dY) / maxT;

                bool toCreateBiomeBlock = needCreateBiomeBlock(x, y, t, world);

                localBlock = biomeUpLeft->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, false, this, world);
                if (biomeUpLeft->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->block[x][y];
                    chunk->block[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, false, world);
                }

                Block* realBlock = localBlock;

                localBlock = biomeUpLeft->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, true, this, world);

                if (biomeUpLeft->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->backBlock[x][y];
                    chunk->backBlock[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, true, world);
                }
            }
    }

    if (biomeUpRight->id > id)
    {
        offsetSmoothBorder = biomeUpRight->offsetSmoothBorder;
        offsetSmoothBorder = offsetSmoothBorder / 2;
        if (offsetSmoothBorder > Chunk::sizeChunk - 1) offsetSmoothBorder = Chunk::sizeChunk - 1;
        t = 0;
        for (int x = Chunk::sizeChunk - offsetSmoothBorder; x < Chunk::sizeChunk; x++)
            for (int y = 0; y < offsetSmoothBorder; y++)
            {
                float dY = y;
                float dX = offsetSmoothBorder - (x - (Chunk::sizeChunk - offsetSmoothBorder));

                float maxT = offsetSmoothBorder * 2;
                t = (dX + dY) / maxT;

                bool toCreateBiomeBlock = needCreateBiomeBlock(x, y, t, world);

                localBlock = biomeUpRight->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, false, this, world);
                if (biomeUpRight->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->block[x][y];
                    chunk->block[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, false, world);
                }

                Block* realBlock = localBlock;

                localBlock = biomeUpRight->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, true, this, world);
                if (biomeUpRight->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->backBlock[x][y];
                    chunk->backBlock[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, true, world);
                }
            }
    }


    if (biomeRight->id > id)
    {
        offsetSmoothBorder = biomeRight->offsetSmoothBorder;
        if (offsetSmoothBorder > Chunk::sizeChunk - 1) offsetSmoothBorder = Chunk::sizeChunk - 1;
        t = 0;

        for (int x = Chunk::sizeChunk - offsetSmoothBorder; x < Chunk::sizeChunk; x++)
            for (int y = 0; y < Chunk::sizeChunk; y++)
            {
                t = (offsetSmoothBorder - (x - (Chunk::sizeChunk - offsetSmoothBorder))) / (offsetSmoothBorder * 1.00f);

                bool toCreateBiomeBlock = needCreateBiomeBlock(x, y, t, world);
                localBlock = biomeRight->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, false, this, world);

                if (biomeRight->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->block[x][y];
                    chunk->block[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, false, world);
                }

                Block* realBlock = localBlock;

                localBlock = biomeRight->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, true, this, world);
                if (biomeRight->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->backBlock[x][y];
                    chunk->backBlock[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, true, world);
                }
            }
    }

    if (biomeDown->id > id)
    {
        offsetSmoothBorder = biomeDown->offsetSmoothBorder;
        if (offsetSmoothBorder > Chunk::sizeChunk - 1) offsetSmoothBorder = Chunk::sizeChunk - 1;
        t = 0;
        for (int x = 0; x < Chunk::sizeChunk; x++)
            for (int y = Chunk::sizeChunk - offsetSmoothBorder; y < Chunk::sizeChunk; y++)
            {
                t = ((offsetSmoothBorder - (y - (Chunk::sizeChunk - offsetSmoothBorder))) / (offsetSmoothBorder * 1.00f));

                bool toCreateBiomeBlock = needCreateBiomeBlock(x, y, t, world);

                localBlock = biomeDown->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, false, this, world);
                if (biomeDown->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->block[x][y];
                    chunk->block[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, false, world);
                }

                Block* realBlock = localBlock;
                localBlock = biomeDown->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, true, this, world);

                if (biomeDown->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->backBlock[x][y];
                    chunk->backBlock[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, true, world);
                }
            }
    }

    if (biomeDownLeft->id > id)
    {
        offsetSmoothBorder = biomeDownLeft->offsetSmoothBorder;
        offsetSmoothBorder = offsetSmoothBorder / 2;
        if (offsetSmoothBorder > Chunk::sizeChunk - 1) offsetSmoothBorder = Chunk::sizeChunk - 1;
        t = 0;
        for (int x = 0; x < offsetSmoothBorder; x++)
            for (int y = Chunk::sizeChunk - offsetSmoothBorder; y < Chunk::sizeChunk; y++)
            {
                float dY = offsetSmoothBorder - (y - (Chunk::sizeChunk - offsetSmoothBorder));
                float dX = x;

                float maxT = offsetSmoothBorder * 2;
                t = (dX + dY) / maxT;

                bool toCreateBiomeBlock = needCreateBiomeBlock(x, y, t, world);

                localBlock = biomeDownLeft->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, false, this, world);
                if (biomeDownLeft->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->block[x][y];
                    chunk->block[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, false, world);
                }

                Block* realBlock = localBlock;

                localBlock = biomeDownLeft->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, true, this, world);
                if (biomeDownLeft->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->backBlock[x][y];
                    chunk->backBlock[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, true, world);
                }
            }
    }


    if (biomeDownRight->id > id)
    {
        offsetSmoothBorder = biomeDownRight->offsetSmoothBorder;
        offsetSmoothBorder = offsetSmoothBorder / 2;
        if (offsetSmoothBorder > Chunk::sizeChunk - 1) offsetSmoothBorder = Chunk::sizeChunk - 1;
        t = 0;
        for (int x = Chunk::sizeChunk - offsetSmoothBorder; x < Chunk::sizeChunk; x++)
            for (int y = Chunk::sizeChunk - offsetSmoothBorder; y < Chunk::sizeChunk; y++)
            {
                float dY = offsetSmoothBorder - (y - (Chunk::sizeChunk - offsetSmoothBorder));
                float dX = offsetSmoothBorder - (x - (Chunk::sizeChunk - offsetSmoothBorder));

                float maxT = offsetSmoothBorder * 2;
                t = (dX + dY) / maxT;

                bool toCreateBiomeBlock = needCreateBiomeBlock(x, y, t, world);

                localBlock = biomeDownRight->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, false, this, world);
                if (biomeDownRight->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->block[x][y];
                    chunk->block[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, false, world);
                }

                Block* realBlock = localBlock;

                localBlock = biomeDownRight->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, true, this, world);
                if (biomeDownRight->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->backBlock[x][y];
                    chunk->backBlock[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, true, world);
                }
            }
    }


    if (biomeLeft->id > id)
    {
        offsetSmoothBorder = biomeLeft->offsetSmoothBorder;
        if (offsetSmoothBorder > Chunk::sizeChunk - 1) offsetSmoothBorder = Chunk::sizeChunk - 1;
        t = 0;
        for (int x = 0; x < offsetSmoothBorder; x++)
            for (int y = 0; y < Chunk::sizeChunk; y++)
            {
                t = x / (offsetSmoothBorder * 1.00f);

                bool toCreateBiomeBlock = needCreateBiomeBlock(x, y, t, world);

                localBlock = biomeLeft->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, false, this, world);
                if (biomeLeft->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->block[x][y];
                    chunk->block[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, false, world);
                }

                Block*realBlock = localBlock;

                localBlock = biomeLeft->getBiomeBlockWithTransition(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, t, true, this, world);
                if (biomeLeft->toCreateBlockInLandshaft(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, world) && localBlock->id != 0)
                {
                    delete chunk->backBlock[x][y];
                    chunk->backBlock[x][y] = localBlock->createBlock(chunkX * Chunk::sizeChunk + x, chunkY * Chunk::sizeChunk + y, true, world);
                }
            }
    }
}

bool Biome::toCreateBlockInLandshaft(int blockX, int blockY, World* world)
{
    bool toCreate = false;

    float maxHighMountains = highLandshaft * sizeNoiseYLandshaft;
    float answer = PerlinNoise::getPerlinNoise(blockX + offsetPosX * Chunk::sizeChunk, offsetPosY * Chunk::sizeChunk, offsetXLandshaft, offsetYLandshaft, world->rand) * highLandshaft;
    answer = maxHighMountains - answer;
    float answerDown = PerlinNoise::getPerlinNoise(blockX + offsetPosX * Chunk::sizeChunk + 32451, offsetPosY * Chunk::sizeChunk + 2346, offsetXLandshaft, offsetYLandshaft, world->rand) * highLandshaft;
    answer = maxHighMountains - answer;

    int highPoint = (int)(limitUp * Chunk::sizeChunk + maxHighMountains);
    int lowPoint = (int)(limitDown * Chunk::sizeChunk - maxHighMountains);

    if (blockY > answer + highPoint && blockY < lowPoint - answer)
    {
        toCreate = true;
    }
    return toCreate;
}

void Biome::setLandshaftChunk(Chunk* chunk, World* world)
{
    int chunkX = chunk->chunkX;
    int chunkY = chunk->chunkY;

    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            int blockX = chunkX * Chunk::sizeChunk + x;
            int blockY = chunkY * Chunk::sizeChunk + y;

            if (!toCreateBlockInLandshaft(blockX, blockY, world))
            {
                delete chunk->block[x][y];
                delete chunk->backBlock[x][y];
                chunk->block[x][y] = RegisteryBlocks::createBlock(blockX, blockY, false, world, 0); // Опять же, создаём блок воздуха
                chunk->backBlock[x][y] = RegisteryBlocks::createBlock(blockX, blockY, false, world, 0); // И ещё разочек :D
            }
        }
}

void Biome::setAdditionChunk(Chunk* chunk, World* world)
{
    int chunkX = chunk->chunkX;
    int chunkY = chunk->chunkY;

    Biome* biomeUp = world->getChunkBiome(chunkX, chunkY - 1);
    Biome* biomeRight = world->getChunkBiome(chunkX + 1, chunkY);
    Biome* biomeDown = world->getChunkBiome(chunkX, chunkY + 1);
    Biome* biomeLeft = world->getChunkBiome(chunkX - 1, chunkY);

    Block*** localBlock = new Block**[Chunk::sizeChunk];
    Block*** localBackBlock = new Block**[Chunk::sizeChunk];

    for (int x = 0; x < Chunk::sizeChunk; x++)
    {
        localBlock[x] = new Block * [Chunk::sizeChunk];
        localBackBlock[x] = new Block * [Chunk::sizeChunk];
    }



    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            localBlock[x][y] = chunk->block[x][y]->createBlock(Chunk::sizeChunk * chunkX + x, Chunk::sizeChunk * chunkY + y, false, chunk->world);
            localBackBlock[x][y] = chunk->backBlock[x][y]->createBlock(Chunk::sizeChunk * chunkX + x, Chunk::sizeChunk * chunkY + y, true, chunk->world);
        }


    editChunk(chunk, localBlock, localBackBlock, Chunk::sizeChunk, Chunk::sizeChunk);

    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            if (localBlock[x][y]->id != 0)
            {
                delete chunk->block[x][y];
                chunk->block[x][y] = localBlock[x][y];
            }
            if (localBackBlock[x][y]->id != 0)
            {
                delete chunk->backBlock[x][y];
                chunk->backBlock[x][y] = localBackBlock[x][y];
            }
        }

    for (int x = 0; x < Chunk::sizeChunk; x++)
    {
        delete[Chunk::sizeChunk] localBlock[x];
        delete[Chunk::sizeChunk] localBackBlock[x];
    }

    delete[Chunk::sizeChunk] localBlock;
    delete[Chunk::sizeChunk] localBackBlock;

    float t = 0;

    if (biomeUp->id > id)
    {

        localBlock = new Block * *[Chunk::sizeChunk];
        localBackBlock = new Block * *[Chunk::sizeChunk];

        for (int x = 0; x < Chunk::sizeChunk; x++)
        {
            localBlock[x] = new Block * [biomeUp->offsetSmoothBorder];
            localBackBlock[x] = new Block * [biomeUp->offsetSmoothBorder];
        }

        for (int x = 0; x < Chunk::sizeChunk; x++)
            for (int y = 0; y < biomeUp->offsetSmoothBorder; y++)
            {
                localBlock[x][y] = chunk->block[x][y]->createBlock(Chunk::sizeChunk * chunkX + x, Chunk::sizeChunk * chunkY + y, false, chunk->world);
                localBackBlock[x][y] = chunk->backBlock[x][y]->createBlock(Chunk::sizeChunk * chunkX + x, Chunk::sizeChunk * chunkY + y, true, chunk->world);
            }

        biomeUp->editChunk(chunk, localBlock, localBackBlock, Chunk::sizeChunk, biomeUp->offsetSmoothBorder);

        for (int x = 0; x < Chunk::sizeChunk; x++)
            for (int y = 0; y < biomeUp->offsetSmoothBorder; y++)
            {
                t = 1 - (y / biomeUp->offsetSmoothBorder);
                if (world->rand->next((int)(Chunk::sizeChunk * chunkX + x + biomeUp->offsetPosX), (int)(Chunk::sizeChunk * chunkY + y + biomeUp->offsetPosY), 0, 100) < t * 100)
                {
                    if (localBlock[x][y]->id != 0)
                    {
                        delete chunk->block[x][y];
                        chunk->block[x][y] = localBlock[x][y];
                    }
                    if (localBackBlock[x][y]->id != 0)
                    {
                        delete chunk->backBlock[x][y];
                        chunk->backBlock[x][y] = localBackBlock[x][y];
                    }
                }
            }

        for (int x = 0; x < biomeUp->offsetSmoothBorder; x++)
        {
            delete[biomeUp->offsetSmoothBorder] localBlock[x];
            delete[biomeUp->offsetSmoothBorder] localBackBlock[x];
        }

        delete[Chunk::sizeChunk] localBlock;
        delete[Chunk::sizeChunk] localBackBlock;
    }



    if (biomeRight->id > id)
    {
        localBlock = new Block * *[biomeRight->offsetSmoothBorder];
        localBackBlock = new Block * *[biomeRight->offsetSmoothBorder];

        for (int x = 0; x < biomeRight->offsetSmoothBorder; x++)
        {
            localBlock[x] = new Block * [Chunk::sizeChunk];
            localBackBlock[x] = new Block * [Chunk::sizeChunk];
        }


        for (int x = 0; x < biomeRight->offsetSmoothBorder; x++)
            for (int y = 0; y < Chunk::sizeChunk; y++)
            {
                int localX = Chunk::sizeChunk - biomeRight->offsetSmoothBorder + x;
                int localY = y;
                localBlock[x][y] = chunk->block[localX][localY]->createBlock(chunk->block[localX][localY]->pX, chunk->block[localX][localY]->pY, false, chunk->world);
                localBackBlock[x][y] = chunk->backBlock[localX][localY]->createBlock(chunk->backBlock[localX][localY]->pX, chunk->backBlock[localX][localY]->pY, true, chunk->world);
            }
        biomeRight->editChunk(chunk, localBlock, localBackBlock, biomeRight->offsetSmoothBorder, Chunk::sizeChunk);

        for (int x = 0; x < biomeRight->offsetSmoothBorder; x++)
            for (int y = 0; y < Chunk::sizeChunk; y++)
            {
                int localX = Chunk::sizeChunk - biomeRight->offsetSmoothBorder + x;
                int localY = y;
                t = 1 - (x / (Chunk::sizeChunk - biomeRight->offsetSmoothBorder));
                if (world->rand->next((int)(Chunk::sizeChunk * chunkX + x + biomeRight->offsetPosX), (int)(Chunk::sizeChunk * chunkY + y + biomeRight->offsetPosY), 0, 100) < t * 100)
                {
                    if (localBlock[x][y]->id != 0)
                    {
                        delete chunk->block[localX][localY];
                        chunk->block[localX][localY] = localBlock[x][y];
                    }
                    if (localBackBlock[x][y]->id != 0)
                    {
                        delete chunk->backBlock[localX][localY];
                        chunk->backBlock[localX][localY] = localBackBlock[x][y];
                    }
                }
            }
        for (int x = 0; x < biomeUp->offsetSmoothBorder; x++)
        {
            delete[Chunk::sizeChunk] localBlock[x];
            delete[Chunk::sizeChunk] localBackBlock[x];
        }

        delete[biomeRight->offsetSmoothBorder] localBlock;
        delete[biomeRight->offsetSmoothBorder] localBackBlock;
    }


    if (biomeDown->id > id)
    {
        localBlock = new Block * *[Chunk::sizeChunk];
        localBackBlock = new Block * *[Chunk::sizeChunk];

        for (int x = 0; x < Chunk::sizeChunk; x++)
        {
            localBlock[x] = new Block * [biomeDown->offsetSmoothBorder];
            localBackBlock[x] = new Block * [biomeDown->offsetSmoothBorder];
        }

        for (int x = 0; x < Chunk::sizeChunk; x++)
            for (int y = 0; y < biomeDown->offsetSmoothBorder; y++)
            {
                int localX = x;
                int localY = Chunk::sizeChunk - biomeDown->offsetSmoothBorder + y;
                localBlock[x][y] = chunk->block[localX][localY]->createBlock(chunk->block[localX][localY]->pX, chunk->block[localX][localY]->pY, false, chunk->world);
                localBackBlock[x][y] = chunk->backBlock[localX][localY]->createBlock(chunk->backBlock[localX][localY]->pX, chunk->backBlock[localX][localY]->pY, true, chunk->world);
            }
        biomeDown->editChunk(chunk, localBlock, localBackBlock, Chunk::sizeChunk, biomeDown->offsetSmoothBorder);
        for (int x = 0; x < Chunk::sizeChunk; x++)
            for (int y = 0; y < biomeDown->offsetSmoothBorder; y++)
            {
                int localX = x;
                int localY = Chunk::sizeChunk - biomeDown->offsetSmoothBorder + y;
                t = x / biomeDown->offsetSmoothBorder;
                if (world->rand->next((int)(Chunk::sizeChunk * chunkX + x + biomeDown->offsetPosX), (int)(Chunk::sizeChunk * chunkY + y + biomeDown->offsetPosY), 0, 100) < t * 100)
                {
                    if (localBlock[x][y]->id != 0)
                    {
                        delete chunk->block[localX][localY];
                        chunk->block[localX][localY] = localBlock[x][y];
                    }
                    if (localBackBlock[x][y]->id != 0)
                    {
                        delete chunk->backBlock[localX][localY];
                        chunk->backBlock[localX][localY] = localBackBlock[x][y];
                    }
                }
            }
        for (int x = 0; x < biomeUp->offsetSmoothBorder; x++)
        {
            delete[biomeDown->offsetSmoothBorder] localBlock[x];
            delete[biomeDown->offsetSmoothBorder] localBackBlock[x];
        }

        delete[Chunk::sizeChunk] localBlock;
        delete[Chunk::sizeChunk] localBackBlock;
    }

    if (biomeLeft->id > id)
    {
        localBlock = new Block * *[biomeLeft->offsetSmoothBorder];
        localBackBlock = new Block * *[biomeLeft->offsetSmoothBorder];

        for (int x = 0; x < biomeLeft->offsetSmoothBorder; x++)
        {
            localBlock[x] = new Block * [Chunk::sizeChunk];
            localBackBlock[x] = new Block * [Chunk::sizeChunk];
        }

        for (int x = 0; x < biomeLeft->offsetSmoothBorder; x++)
            for (int y = 0; y < Chunk::sizeChunk; y++)
            {
                int localX = x;
                int localY = y;
                localBlock[x][y] = chunk->block[localX][localY]->createBlock(chunk->block[localX][localY]->pX, chunk->block[localX][localY]->pY, false, chunk->world);
                localBackBlock[x][y] = chunk->backBlock[localX][localY]->createBlock(chunk->backBlock[localX][localY]->pX, chunk->backBlock[localX][localY]->pY, true, chunk->world);
            }
        biomeLeft->editChunk(chunk, localBlock, localBackBlock, biomeLeft->offsetSmoothBorder, biomeLeft->offsetSmoothBorder);

        for (int x = 0; x < biomeLeft->offsetSmoothBorder; x++)
            for (int y = 0; y < Chunk::sizeChunk; y++)
            {
                int localX = x;
                int localY = y;
                t = x / (Chunk::sizeChunk - biomeLeft->offsetSmoothBorder);
                if (world->rand->next((int)(Chunk::sizeChunk * chunkX + x + biomeLeft->offsetPosX), (int)(Chunk::sizeChunk * chunkY + y + biomeLeft->offsetPosY), 0, 100) < t * 100)
                {
                    if (localBlock[x][y]->id != 0)
                    {
                        delete chunk->block[localX][localY];
                        chunk->block[localX][localY] = localBlock[x][y];
                    }
                    if (localBackBlock[x][y]->id != 0)
                    {
                        delete chunk->backBlock[localX][localY];
                        chunk->backBlock[localX][localY] = localBackBlock[x][y];
                    }
                }
            }
        for (int x = 0; x < biomeUp->offsetSmoothBorder; x++)
        {
            delete[Chunk::sizeChunk] localBlock[x];
            delete[Chunk::sizeChunk] localBackBlock[x];
        }
        delete[biomeLeft->offsetSmoothBorder] localBlock;
        delete[biomeLeft->offsetSmoothBorder] localBackBlock;
    }
}

Chunk* Biome::generateChunk(int chunkX, int chunkY, World* world)
{
    Chunk* chunk = new Chunk(world, chunkX, chunkY);
    chunk->biome1 = id;

    int blockChunkX = chunk->chunkX * Chunk::sizeChunk;
    int blockChunkY = chunk->chunkY * Chunk::sizeChunk;

    Block*** block = new Block**[Chunk::sizeChunk];

    for (int x = 0; x < Chunk::sizeChunk; x++)
    {
        block[x] = new Block*[Chunk::sizeChunk];
    }

    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            block[x][y] = getBiomeBlock(blockChunkX + x, blockChunkY + y, world)->createBlock(blockChunkX + x, blockChunkY + y, false, world);
        }
    chunk->block = block;

    Block*** backBlock = new Block * *[Chunk::sizeChunk];

    for (int x = 0; x < Chunk::sizeChunk; x++)
    {
        backBlock[x] = new Block * [Chunk::sizeChunk];
    }

    for (int x = 0; x < Chunk::sizeChunk; x++)
        for (int y = 0; y < Chunk::sizeChunk; y++)
        {
            backBlock[x][y] = getBiomeBackBlock(blockChunkX + x, blockChunkY + y, world)->createBlock(blockChunkX + x, blockChunkY + y, true, world);
        }

    chunk->backBlock = backBlock;

    setLandshaftChunk(chunk, world);
    setBorderChunk(chunk, world);
    setAdditionChunk(chunk, world);
    return chunk;
}
