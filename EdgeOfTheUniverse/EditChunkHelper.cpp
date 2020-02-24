#include "EditChunkHelper.h"

//ѕроисходит выделение пам€ти, так что об€зательно удал€ть массив указателей после использовани€, но не массив блоков! –азмер массива равен 9
Block** EditChunkHelper::getNeighboringBlock(int x, int y, Block*** block, int sizeX, int sizeY)
{
    Block** neighboringBlock = new Block*[9];

    if (y - 1 >= 0)
        neighboringBlock[0] = block[x][y - 1];
    else  neighboringBlock[0] = nullptr;

    if (x + 1 < sizeX && y - 1 >= 0)
        neighboringBlock[1] = block[x + 1][y - 1];
    else  neighboringBlock[1] = nullptr;

    if (x + 1 < sizeX)
        neighboringBlock[2] = block[x + 1][y];
    else  neighboringBlock[2] = nullptr;

    if (x + 1 < sizeX && y + 1 < sizeY)
        neighboringBlock[3] = block[x + 1][y + 1];
    else  neighboringBlock[3] = nullptr;

    if (y + 1 < sizeY)
        neighboringBlock[4] = block[x][y + 1];
    else  neighboringBlock[4] = nullptr;

    if (x - 1 >= 0 && y + 1 < sizeY)
        neighboringBlock[5] = block[x - 1][y + 1];
    else  neighboringBlock[5] = nullptr;
    if (x - 1 >= 0)
        neighboringBlock[6] = block[x - 1][y];
    else  neighboringBlock[6] = nullptr;
    if (x - 1 >= 0 && y - 1 >= 0)
        neighboringBlock[7] = block[x - 1][y - 1];
    else  neighboringBlock[7] = nullptr;

    neighboringBlock[8] = block[x][y];

    return neighboringBlock;
}

void EditChunkHelper::setGrass(Chunk* chunk, Block*** block, Block*** backBlock, BlockName* nameGrass, int sizeBlockX, int sizeBlockY, int sizeNameGrass)
{
    for (int x = 0; x < sizeBlockX; x++)
        for (int y = 0; y < sizeBlockY; y++)
        {
            BlockName name = nameGrass[(int)chunk->world->rand->next(block[x][y]->pX, block[x][y]->pY, 0, sizeNameGrass)];

            if (name != NA)
            {

                Block** neighboringBlock = getNeighboringBlock(x, y, block, sizeBlockX, sizeBlockY);


                Block* top = neighboringBlock[0];
                Block* right = neighboringBlock[2];
                Block* down = neighboringBlock[4];
                Block* left = neighboringBlock[6];
                Block* center = neighboringBlock[8];

                if (top != nullptr && right != nullptr && down != nullptr && left != nullptr && center != nullptr)
                {
                    if (center->id != 0)
                    {
                        int blockX = block[x][y]->pX;
                        int blockY = block[x][y]->pY;
                        if (top->id == 0)
                            center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, name);

                        if (right->id == 0)
                            center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, name);

                        if (down->id == 0)
                            center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, name);

                        if (left->id == 0)
                            center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, name);

                        if (block[x][y] != nullptr) delete block[x][y];
                        block[x][y] = center;
                    }
                }

                delete[9] neighboringBlock;

            }
        }
}

void EditChunkHelper::setGrass(Chunk* chunk, Block*** block, Block*** backBlock, BlockName nameGrass, int sizeBlockX, int sizeBlockY)
{
    for (int x = 0; x < sizeBlockX; x++)
        for (int y = 0; y < sizeBlockY; y++)
        {
            BlockName name = nameGrass;

            if (name != NA)
            {

                Block** neighboringBlock = getNeighboringBlock(x, y, block, sizeBlockX, sizeBlockY);


                Block* top = neighboringBlock[0];
                Block* right = neighboringBlock[2];
                Block* down = neighboringBlock[4];
                Block* left = neighboringBlock[6];
                Block* center = neighboringBlock[8];

                if (top != nullptr && right != nullptr && down != nullptr && left != nullptr && center != nullptr)
                {
                    if (center->id != 0)
                    {
                        int blockX = block[x][y]->pX;
                        int blockY = block[x][y]->pY;
                        if (top->id == 0)
                            center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, name);

                        if (right->id == 0)
                            center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, name);

                        if (down->id == 0)
                            center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, name);

                        if (left->id == 0)
                            center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, name);

                        if (block[x][y] != nullptr) delete block[x][y];
                        block[x][y] = center;
                    }
                }

                delete[9] neighboringBlock;

            }
        }
}

void EditChunkHelper::setGrass(Chunk* chunk, Block*** block, Block*** backBlock, int* idGrass, int sizeIdGrass, int sizeBlockX, int sizeBlockY)
{
    for (int x = 0; x < sizeBlockX; x++)
        for (int y = 0; y < sizeBlockY; y++)
        {
            Block** neighboringBlock = getNeighboringBlock(x, y, block, sizeBlockX, sizeBlockY);

            int id = idGrass[(int)chunk->world->rand->next(block[x][y]->pX, block[x][y]->pY, 0, sizeIdGrass)];

            Block* top = neighboringBlock[0];
            Block* right = neighboringBlock[2];
            Block* down = neighboringBlock[4];
            Block* left = neighboringBlock[6];
            Block* center = neighboringBlock[8];

            if (top != nullptr && right != nullptr && down != nullptr && left != nullptr && center != nullptr)
            {
                if (center->id != 0)
                {
                    int blockX = block[x][y]->pX;
                    int blockY = block[x][y]->pY;
                    if (top->id == 0)
                        center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, id);

                    if (right->id == 0)
                        center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, id);

                    if (down->id == 0)
                        center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, id);

                    if (left->id == 0)
                        center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, id);

                    if (block[x][y] != nullptr) delete block[x][y];
                    block[x][y] = center;
                }
                delete[9] neighboringBlock;
            }
        }
}

void EditChunkHelper::setGrass(Chunk* chunk, Block*** block, Block*** backBlock, int idGrass, int sizeBlockX, int sizeBlockY)
{
    for (int x = 0; x < sizeBlockX; x++)
        for (int y = 0; y < sizeBlockY; y++)
        {
            Block** neighboringBlock = getNeighboringBlock(x, y, block, sizeBlockX, sizeBlockY);


            Block* top = neighboringBlock[0];
            Block* right = neighboringBlock[2];
            Block* down = neighboringBlock[4];
            Block* left = neighboringBlock[6];
            Block* center = neighboringBlock[8];

            if (top != nullptr && right != nullptr && down != nullptr && left != nullptr && center != nullptr)
            {
                if (center->id != 0)
                {
                    int blockX = block[x][y]->pX;
                    int blockY = block[x][y]->pY;
                    if (top->id == 0)
                    {
                        center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, idGrass);
                        if (block[x][y] != nullptr) delete block[x][y];
                        block[x][y] = center;
                    }
                    else if (right->id == 0)
                    {
                        center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, idGrass);
                        if (block[x][y] != nullptr) delete block[x][y];
                        block[x][y] = center;
                    }
                    else if (down->id == 0)
                    {
                        center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, idGrass);
                        if (block[x][y] != nullptr) delete block[x][y];
                        block[x][y] = center;
                    }
                    else if (left->id == 0)
                    {
                        center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, idGrass);
                        if (block[x][y] != nullptr) delete block[x][y];
                        block[x][y] = center;
                    }
                }
            }

            delete[9] neighboringBlock;
        }
}


void EditChunkHelper::setGrass(Chunk * chunk, Block * **block, Block * **backBlock, int idGrass, int grassBlockPlace, int sizeBlockX, int sizeBlockY)
    {
        for (int x = 0; x < sizeBlockX; x++)
            for (int y = 0; y < sizeBlockY; y++)
            {
                Block** neighboringBlock = getNeighboringBlock(x, y, block, sizeBlockX, sizeBlockY);


                Block* top = neighboringBlock[0];
                Block* right = neighboringBlock[2];
                Block* down = neighboringBlock[4];
                Block* left = neighboringBlock[6];
                Block* center = neighboringBlock[8];

                if (top != nullptr && right != nullptr && down != nullptr && left != nullptr && center != nullptr)
                {
                    if (center->id == grassBlockPlace)
                    {
                        int blockX = block[x][y]->pX;
                        int blockY = block[x][y]->pY;
                        if (top->id == 0)
                        {
                            center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, idGrass);
                            if (block[x][y] != nullptr) delete block[x][y];
                            block[x][y] = center;
                        }
                        else if (right->id == 0)
                        {
                            center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, idGrass);
                            if (block[x][y] != nullptr) delete block[x][y];
                            block[x][y] = center;
                        }
                        else if (down->id == 0)
                        {
                            center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, idGrass);
                            if (block[x][y] != nullptr) delete block[x][y];
                            block[x][y] = center;
                        }
                        else if (left->id == 0)
                        {
                            center = RegisteryBlocks::createBlock(blockX, blockY, false, chunk->world, idGrass);
                            if (block[x][y] != nullptr) delete block[x][y];
                            block[x][y] = center;
                        }
                    }
                }

                delete[9] neighboringBlock;
            }
}
