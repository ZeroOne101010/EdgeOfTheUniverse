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
	std::vector<GLuint> handleTextureBuffer;
	std::vector<glm::vec2> sizeTexture;

	TBO();
	TBO(const GLchar* path);

	void addTextureHandle(unsigned char* textureBuffer, GLuint textureWidth, GLuint textureHeight);
	void addTextureHandle(const GLchar* path);
	void bindToDrawTextureBuffers();
	void updateTextureBuffer(GLuint idInArray, unsigned char* textureBuffer, GLuint textureWidth, GLuint textureHeight);
};

