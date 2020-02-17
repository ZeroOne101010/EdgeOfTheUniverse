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
	int width, height;
	unsigned char* image;
	Texture(const char* path = "Resources/Textures/DefaultTexture.png");
	~Texture();

	void setTextureRect(GLuint index, FloatRect rect);
	void setTextureRect(GLuint index, glm::vec2 position, glm::vec2 size);
	void setTextureRect(GLuint index, float x, float y, float width, float height);

	void setSampler(Shader* shader, GLuint indexSampler, GLuint value);
private: 
	VBO vboUV;
	bool haveSampler;
};

