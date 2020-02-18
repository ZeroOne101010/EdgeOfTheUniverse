#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include "ConvertRegionData.h"

class Chunk;

class ChunkThread
{
public:

    struct ChunkContainer
    {
        int chunkX;
        int chunkY;
        World* world;
    };

    std::mutex threadLocator;
    std::vector<Chunk*> chunkToSave;
    std::vector<ChunkContainer> chunkContainer;
    std::thread* chunkThread;

    ChunkThread();
    ~ChunkThread();
    void start();
    void updateThread();
    void addChunkToSave(Chunk* chunk);
    void addChunkContainer(int chunkX, int chunkY, World* world);
    void toSaveChunk(Chunk* chunk);
    void loadChunkToWorld(ChunkContainer container);
    void close();
private:
    bool threadIsClose = true;
};

