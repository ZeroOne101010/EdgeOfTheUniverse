#include "World.h"
#include "Block.h"

#define NN(ID) b[ID] != 0
#define IN(ID) b[ID] == 0

#define NI(ID) b[ID] != ID
#define II(ID) b[ID] == this->id

#define TXR(MIN, MAX) tX = world->rand->next(pX, pY, MIN, MAX + 1)
#define TYR(MIN, MAX) tY = world->rand->next(pX, pY, MIN, MAX + 1)

#define TXRS(OFFSET, MIN, MAX, STRIDE_RECT) tX = OFFSET + ((int)world->rand->next(pX, pY, MIN, MAX + 1) * (STRIDE_RECT))
#define TYRS(OFFSET, MIN, MAX, STRIDE_RECT) tY = OFFSET + ((int)world->rand->next(pX, pY, MIN, MAX + 1) * (STRIDE_RECT))

#define TX(VALUE) tX = VALUE;
#define TY(VALUE) tY = VALUE;

const int Block::sizeBlock = 21;

Block::Block()
{
	world = nullptr;
}

Block::Block(glm::vec4 color, Texture* texture, FloatRect textureRect)
{
	world = nullptr;
	this->color = color;
	this->texture = texture;
	this->textureRect = textureRect;
}

Block::~Block()
{
	if (rect != nullptr)
	{
		delete rect;
	}
}


Block* Block::createBlock(int pX, int pY, bool isBackBlock, World* world)
{
	Block* block = getNewBlock();
	block->id = id;
	block->pX = pX;
	block->pY = pY;
	block->isBackBlock = isBackBlock;
	block->world = world;
	//block->Position = vec2(pX * sizeBlock , pY * sizeBlock);
	return block;
}

void Block::updateTextureBlock()
{
	if (!isUpdatedTexture)
	{
		rect = new RectangleShape(sizeBlock, sizeBlock);
        rect->shader = Content::lightingShader;
		rect->optimizeMode = optimizeMode;
		rect->Position = vec2(pX * sizeBlock, pY * sizeBlock);
		rect->textureRect = textureRect;
		isUpdatedTexture = true;
		rect->texture = texture;
		rect->Color = color;
	}
}

void Block::update()
{
	//Здесь пока пусто :3
}

void Block::start()
{
	//Здесь пока пусто :3
}

void Block::updateTextureRect()
{
    if (!isUpdatedViewTexture)
    {
        if (canUpdateTexture)
        {
            int pXl = pX;
            int pYl = pY;
            int sX = 1;
            int sY = 1;
            //isBackBlock = false;

            int pXb0 = pXl * sX; int pXb1 = (pXl + 1) * sX; int pXb2 = (pXl + 1) * sX; int pXb3 = (pXl + 1) * sX; int pXb4 = pXl * sX;
            int pYb0 = (pYl - 1) * sY; int pYb1 = (pYl - 1) * sY; int pYb2 = pYl * sY; int pYb3 = (pYl + 1) * sY; int pYb4 = (pYl + 1) * sY;
            int pXb5 = (pXl - 1) * sX; int pXb6 = (pXl - 1) * sX; int pXb7 = (pXl - 1) * sX;
            int pYb5 = (pYl + 1) * sY; int pYb6 = pYl * sY; int pYb7 = (pYl - 1) * sY;

            int* b = new int[8];
            b[0] = world->getBlockNotGeneration(pXb0, pYb0, isBackBlock) == nullptr ? -1 : (*world->getBlockNotGeneration(pXb0, pYb0, isBackBlock))->id;
            b[1] = world->getBlockNotGeneration(pXb1, pYb1, isBackBlock) == nullptr ? -1 : (*world->getBlockNotGeneration(pXb1, pYb1, isBackBlock))->id;
            b[2] = world->getBlockNotGeneration(pXb2, pYb2, isBackBlock) == nullptr ? -1 : (*world->getBlockNotGeneration(pXb2, pYb2, isBackBlock))->id;
            b[3] = world->getBlockNotGeneration(pXb3, pYb3, isBackBlock) == nullptr ? -1 : (*world->getBlockNotGeneration(pXb3, pYb3, isBackBlock))->id;
            b[4] = world->getBlockNotGeneration(pXb4, pYb4, isBackBlock) == nullptr ? -1 : (*world->getBlockNotGeneration(pXb4, pYb4, isBackBlock))->id;
            b[5] = world->getBlockNotGeneration(pXb5, pYb5, isBackBlock) == nullptr ? -1 : (*world->getBlockNotGeneration(pXb5, pYb5, isBackBlock))->id;
            b[6] = world->getBlockNotGeneration(pXb6, pYb6, isBackBlock) == nullptr ? -1 : (*world->getBlockNotGeneration(pXb6, pYb6, isBackBlock))->id;
            b[7] = world->getBlockNotGeneration(pXb7, pYb7, isBackBlock) == nullptr ? -1 : (*world->getBlockNotGeneration(pXb7, pYb7, isBackBlock))->id;

            bool isNullptr = false;
            for (int x = 0; x < 8; x++)
            {
                if (b[x] == -1)
                {
                    isNullptr = true;
                    break;
                }
            }

            if (isNullptr == false)
            {
                isUpdatedViewTexture = true;
            }
            int tX = 0;
            int tY = 0;

            if (NN(0) && IN(1) && NN(2) && NN(4) && NN(6)) //Правый верхний угол свободно
            {
                TX(2);
                TYRS(6, 0, 2, 2);
            }
            else if (NN(0) && NN(2) && NN(4) && NN(6) && IN(7)) //Левый верхний угол свободно
            {
                TX(3);
                TYRS(6, 0, 2, 2);
            }
            else if (NN(0) && NN(2) && NN(4) && IN(5) && NN(6)) //Левый нижний угол свободно
            {
                TX(3);
                TYRS(5, 0, 2, 2);
            }
            else if (NN(0) && NN(2) && IN(3) && NN(4) && NN(6)) // Праый нижний угол свободно
            {
                TX(2);
                TYRS(5, 0, 2, 2);
            }
            else if (NN(0) && NN(2) && NN(4) && NN(6)) // Центр
            {
                TXR(1, 3);
                TY(1);
            }
            else if(IN(0) && NN(2) && NN(4) && NN(6)) //Сверху свободно
            {
                TXR(1, 3);
                TY(0);  
            }
            else if (NN(0) && IN(2) && NN(4) && NN(6)) // Справа свободно
            {
                TX(4);
                TYR(0, 2);
            }
            else if(NN(0) && NN(2) && IN(4) && NN(6)) // Снизу совободно
            {
                TXR(1, 3);
                TY(2)
            }
            else if (NN(0) && NN(2) && NN(4) && IN(6)) // Слева свободно
            {
                TX(0);
                TYR(0, 2);
            }
            else if (IN(0) && NN(2) && NN(4) && IN(6)) // Левый верхний угол
            {
                TXRS(0, 0, 2, 2);
                TY(3);
            }
            else if (IN(0) && IN(2) && NN(4) && NN(6)) // Правый верхний угол
            {
                TXRS(1, 0, 2, 2);
                TY(3);
            }
            else if (NN(0) && IN(2) && IN(4) && NN(6)) // Правый нижней угол
            {
                TXRS(1, 0, 2, 2);
                TY(4);
            }
            else if (NN(0) && NN(2) && IN(4) && IN(6)) // Левый нижний угол
            {
                TXRS(0, 0, 2, 2);
                TY(4);
            }
            else if (NN(0) && IN(2) && NN(4) && IN(6)) // Вертикальная линия
            {
                TX(5);
                TYR(0, 2);
            }
            else if (IN(0) && NN(2) && IN(4) && NN(6)) // Горизонтальная линия 
            {
                TXR(6, 8);
                TY(4);
            }
            else if (NN(6)) // Слева занято
            {
                TX(12);
                TYR(0, 2);
            }
            else if (NN(2)) // Справа занято
            {
                TX(9);
                TYR(0, 2);
            }
            else if (NN(0)) // Сверху занято
            {
                TXR(6, 9);
                TY(3);
            }
            else if (NN(4)) // Снизу занято
            {
                TXR(6, 9);
                TY(0);
            } 
            else // Везде свободно
            {
                TXR(9, 11);
                TY(3);
            }

            delete[8] b;

            //tX = 0;
            //tY = 3;

            tX = tX * (16 + 2);
            tY = tY * (16 + 2);

            textureRect = FloatRect(tX, tY, 16, 16);
            //if (backTexture != null)
            //{
            //    backTextureRect = new FloatRect(tX, tY, sizeBlock, sizeBlock);
            //}
            if (rect != nullptr)
                rect->textureRect = textureRect;
            //if (backgroundRect != null)
            //    backgroundRect.TextureRect = new IntRect(tX, tY, sizeBlock, sizeBlock);
        }
    }
}

void Block::updateViewBlock()
{
    updateTextureBlock();
    updateTextureRect();
}

void Block::draw(Renderer* renderer, Alterable alters)
{
	alters *= *this;
	renderer->draw(rect, alters);
}

Block* Block::addProperty(int value, int sizeProperty, std::string nameProperty)
{
	propertyManager.addProperty(value, sizeProperty, nameProperty);
	return this;
}

int Block::getValueProperty(std::string nameProperty)
{
	return propertyManager.getValueProperty(nameProperty);
}

void Block::setValueProperty(std::string nameProperty, int value)
{
	propertyManager.setValueProperty(nameProperty, value);;
}
