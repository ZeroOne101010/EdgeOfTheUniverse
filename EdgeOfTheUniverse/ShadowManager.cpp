#include "ShadowManager.h"

#define SIZE_COLOR 3

ShadowManager::ShadowManager()
{
	fieldToUpdateShadow = 10;
	initBlockBrigtnessBuffer(RenderWindow::width, RenderWindow::height);
}

ShadowManager::ShadowManager(int fieldToUpdateShadow)
{
	this->fieldToUpdateShadow = fieldToUpdateShadow;
	initBlockBrigtnessBuffer(RenderWindow::width, RenderWindow::height);
}

// Обнавляет значения буфера теней в шейдере
void ShadowManager::toUpdateShadowUniformBuffer()
{
}

void ShadowManager::initBlockBrigtnessBuffer(int widthWindow, int heightWindow)
{
	int widthBlocks = widthWindow / Block::sizeBlock;
	int heightBlocks = heightWindow / Block::sizeBlock;

	blockBrightnessBuffer = new char**[widthBlocks];
	for (int x = 0; x < widthBlocks; x++)
	{
		blockBrightnessBuffer[x] = new char*[heightBlocks];
	}

	for (int x = 0; x < widthBlocks; x++)
		for (int y = 0; y < heightBlocks; y++)
		{
			blockBrightnessBuffer[x][y] = new char[fieldToUpdateShadow * fieldToUpdateShadow * SIZE_COLOR];
		}
}


