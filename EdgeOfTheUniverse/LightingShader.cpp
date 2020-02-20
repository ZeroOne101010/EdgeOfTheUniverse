#include "LightingShader.h"
LightingShader::LightingShader() : DefaultShader("Resources/Shaders/DefaultShader.vert", "Resources/Shaders/LightingShader.frag")
{
	positionBlockInBuffer = createUniformIndex("positionBlockInBuffer");
	blockBrightnessBufferIndex = createUniformIndex("blockBrightnessBuffer");
	sizeBufferIndex = createUniformIndex("sizeBuffer");

}

void LightingShader::setBlockPositionToBuffer(int blockX, int blockY)
{
	float* position = new float[2];
	position[0] = blockX;
	position[1] = blockY;
	//glUniform
}
