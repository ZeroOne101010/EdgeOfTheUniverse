#include "World.h"
#include "ChunkThread.h"
ChunkThread::ChunkThread()
{
    chunkToSave = std::vector<Chunk*>();
}

ChunkThread::~ChunkThread()
{
}

void ChunkThread::start()
{
    chunkThread = new std::thread(&ChunkThread::updateThread, this);
}


void ChunkThread::updateThread()
{
    while (threadIsClose)
    {
        //std::cout << chunkContainer.size() << std::endl;
        if (chunkContainer.size() > 0)
        {
            int id = 0;
            threadLocator.lock();
            id = chunkContainer.size() - 1;
            threadLocator.unlock();

            //std::cout << chunkContainer.size() << std::endl;

            threadLocator.lock();
            loadChunkToWorld(chunkContainer[id]);
            threadLocator.unlock();

            threadLocator.lock();
            chunkContainer.erase(chunkContainer.begin() + id);
            std::vector<ChunkContainer>(chunkContainer).swap(chunkContainer);
            threadLocator.unlock();
        }
    }
}

void ChunkThread::addChunkToSave(Chunk* chunk)
{
    threadLocator.lock();
    if (!std::binary_search(chunkToSave.begin(), chunkToSave.end(), chunk))
    {
        chunkToSave.push_back(chunk);
    }
    threadLocator.unlock();
}

void ChunkThread::addChunkContainer(int chunkX, int chunkY, World* world)
{
    threadLocator.lock();
    bool isFind = false;

    for (int x = 0; x < chunkContainer.size(); x++)
    {
        if (chunkContainer[x].chunkX == chunkX && chunkContainer[x].chunkY == chunkY)
        {
            isFind = true;
            break;
        }
    }
    if (!isFind)
    {
        ChunkContainer containter;
        containter.chunkX = chunkX;
        containter.chunkY = chunkY;
        containter.world = world;
        chunkContainer.push_back(containter);
    }

    threadLocator.unlock();
}

void ChunkThread::toSaveChunk(Chunk* chunk)
{
    ConvertRegionData::saveChunkDataToRegion(chunk, chunk->world);
}

void ChunkThread::loadChunkToWorld(ChunkContainer container)
{
    World* world = container.world;
    Chunk* localChunk = ConvertRegionData::getChunkFromDataRegion(container.chunkX, container.chunkY, world);

    if (localChunk == nullptr)
    {
        localChunk = world->generationChunk(container.chunkX, container.chunkY);
    }

    world->chunkPointer++;
    std::cout << world->chunkPointer << std::endl;
    if (world->chunkPointer > World::countActiveChunks - 1)
    {
        world->chunkPointer = 0;
    }

    if (world->chunk[world->chunkPointer] != nullptr)
    {
        //threadLocator.lock();
        toSaveChunk(world->chunk[world->chunkPointer]);
        //threadLocator.unlock();

        //threadLocator.lock();
        //world->updateCloseChunk(world->chunk[world->chunkPointer]);
        //delete world->chunk[world->chunkPointer];
        //threadLocator.unlock();
    }

    world->chunk[world->chunkPointer] = localChunk;
}

void ChunkThread::close()
{
    chunkThread->join(); // Ожидание завершения потока нужно, чтобы все чанки успели сохраниться
    threadIsClose = true;
}
