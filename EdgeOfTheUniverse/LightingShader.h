#pragma once
#include "OpenGLEngine/DefaultShader.h"
class LightingShader : public DefaultShader
{
public:
	LightingShader();
	GLuint textureSampler1;

	void setParams() override;

	void setBlockPositionToBuffer(int blockX, int blockY);
};

