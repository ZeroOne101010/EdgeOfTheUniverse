#pragma once
#include "OpenGLEngine/DefaultShader.h"
class LightingShader : public DefaultShader
{
public:
	LightingShader();

	GLuint positionBlockInBuffer;
	GLuint blockBrightnessBufferIndex;
	GLuint sizeBufferIndex;

	void setBlockPositionToBuffer(int blockX, int blockY);
};

