#pragma once

#include "VBO.h"
#include <SOIL.h>
#include "Shader.h"
#include <fstream>
#include "DefaultShader.h"
#include "FloatRect.h"

class Texture
{
public:
	GLuint index;
	FloatRect rect;
	int width, height;
	unsigned char* image;
	Texture();
	Texture(const char* path);
	~Texture();
	void setSampler(Shader* shader);
private: 
	VBO vboUV;
};

