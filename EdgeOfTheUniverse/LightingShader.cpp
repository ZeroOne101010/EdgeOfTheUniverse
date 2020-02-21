#include "LightingShader.h"
LightingShader::LightingShader() : DefaultShader("Resources/Shaders/DefaultShader.vert", "Resources/Shaders/LightingShader.frag")
{
	blockBrightnessTBOIndex = createUniformIndex("blockBrightnessTBOIndex");

}

void LightingShader::setBlockPositionToBuffer(int blockX, int blockY)
{

}
