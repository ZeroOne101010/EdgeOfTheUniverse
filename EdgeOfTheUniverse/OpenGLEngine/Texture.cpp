#include "Texture.h"


Texture::Texture(const char* path)
{
	glGenTextures(1, &index);
	glBindTexture(GL_TEXTURE_2D, index);
	image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	delete[] image;
}

void Texture::setTextureRect(GLuint index, FloatRect rect)
{
	glUniform4f(index, rect.positionX, rect.positionY, rect.sizeX, rect.sizeY);
}

void Texture::setTextureRect(GLuint index, glm::vec2 position, glm::vec2 size)
{
	glUniform4f(index, position.x, position.y, size.x, size.y);
}

void Texture::setTextureRect(GLuint index, float x, float y, float width, float height)
{
	glUniform4f(index, x, y, width, height);
}

void Texture::setSampler(Shader* shader, GLuint indexSampler, GLuint value)
{
	glUniform1i(indexSampler, value);
}
