#include "TBO.h"

TBO::TBO()
{
	addTextureHandle("E:\\EdgeOfTheUniverse\\EdgeOfTheUniverse\\Resources\\Textures\\DefaultTexture.png", "textureSampler");
}

TBO::TBO(const GLchar* path)
{
	addTextureHandle(path, "textureSampler");
}

TBO::TBO(const GLchar* path, const GLchar* nameUniformSampler)
{
	addTextureHandle(path, nameUniformSampler);
}

void TBO::addTextureHandle(unsigned char* textureBuffer, GLuint textureWidth, GLuint textureHeight, const GLchar* nameUniformSampler)
{	
	GLuint textureHandle = 0;
	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);

	glBindTexture(GL_TEXTURE_2D, 0);


	TBO::textureBufferStruct buffer;
	buffer.textureHandle = textureHandle;

	this->handleTextureBuffer.push_back(buffer);
	this->sizeTexture.push_back(glm::vec2(textureWidth, textureHeight));
}

void TBO::addTextureHandle(const GLchar* path, const GLchar* nameUniformSampler)
{
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);

	GLuint textureHandle = 0;
	glGenTextures(1, &textureHandle);
	glActiveTexture(GL_TEXTURE0 + handleTextureBuffer.size());
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	TBO::textureBufferStruct buffer;
	buffer.textureHandle = textureHandle;

	this->handleTextureBuffer.push_back(buffer);
	this->sizeTexture.push_back(glm::vec2(width, height));
}

void TBO::bindToDrawTextureBuffers(Shader* shader)
{
	for (int x = 0; x < handleTextureBuffer.size(); x++)
	{
		glActiveTexture(GL_TEXTURE0 + x);
		glBindTexture(GL_TEXTURE_2D, handleTextureBuffer[x].textureHandle);
	}
}

void TBO::updateTextureBuffer(GLuint idInArray, unsigned char* textureBuffer, GLuint textureWidth, GLuint textureHeight)
{
	glBindTexture(GL_TEXTURE_2D, idInArray);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}


