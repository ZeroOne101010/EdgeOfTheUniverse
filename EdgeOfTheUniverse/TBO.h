#pragma once
#include "OpenGLEngine\VBO.h"
#include <SOIL.h>
#include "OpenGLEngine\Shader.h"
#include <fstream>
#include "OpenGLEngine\DefaultShader.h"
#include "OpenGLEngine\FloatRect.h"

class TBO
{
public:
	struct textureBufferStruct
	{
		GLuint textureHandle;
	};

	std::vector<textureBufferStruct> handleTextureBuffer;
	std::vector<glm::vec2> sizeTexture;

	TBO();
	TBO(const GLchar* path);
	TBO(const GLchar* path, const GLchar* nameUniformSampler);

	void addTextureHandle(unsigned char* textureBuffer, GLuint textureWidth, GLuint textureHeight, const GLchar* nameUniformSampler);
	void addTextureHandle(const GLchar* path, const GLchar* nameUniformSampler);
	void bindToDrawTextureBuffers(Shader* shader);
	void updateTextureBuffer(GLuint idInArray, unsigned char* textureBuffer, GLuint textureWidth, GLuint textureHeight);
};

