#pragma once
#include "Block.h"
class ShadowManager
{
public:
	int fieldToUpdateShadow;

	ShadowManager();
	ShadowManager(int fieldToUpdateShadow);

	char*** blockBrightnessBuffer;
	void toUpdateShadowUniformBuffer();
private:
	void initBlockBrigtnessBuffer(int widthWindow, int heightWindow);
};

