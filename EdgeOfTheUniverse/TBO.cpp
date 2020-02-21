#include "TBO.h"

TBO::TBO()
{
	addTextureHandle("E:\EdgeOfTheUniverse\EdgeOfTheUniverse\Resources\Textures\DefaultTexture.png");
}

TBO::TBO(const GLchar* path)
{
	addTextureHandle(path);
}

void TBO::addTextureHandle(unsigned char* textureBuffer, GLuint textureWidth, GLuint textureHeight)
{	
	GLuint textureHandle = 0;
	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);

	glBindTexture(GL_TEXTURE_2D, 0);

	this->handleTextureBuffer.push_back(textureHandle);
	this->sizeTexture.push_back(glm::vec2(textureWidth, textureHeight));
}

void TBO::addTextureHandle(const GLchar* path)
{
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);

	GLuint textureHandle = 0;
	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	this->handleTextureBuffer.push_back(textureHandle);
	this->sizeTexture.push_back(glm::vec2(width, height));
}

void TBO::bindToDrawTextureBuffers()
{
	for (int x = 0; x < handleTextureBuffer.size(); x++)
	{
		glActiveTexture(GL_TEXTURE0 + x);
		glBindTexture(GL_TEXTURE_2D, handleTextureBuffer[x]);
	}
}

void TBO::updateTextureBuffer(GLuint idInArray, unsigned char* textureBuffer, GLuint textureWidth, GLuint textureHeight)
{
	glBindTexture(GL_TEXTURE_2D, idInArray);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}


