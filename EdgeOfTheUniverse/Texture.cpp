#include "Texture.h"



Texture::Texture()
{
	index = NULL;
	width = NULL;
	height = NULL;
	image = nullptr;
}

Texture::Texture(const char* path)
{
	//image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);

	//glGenTextures(1, &index);

	//glBindTexture(GL_TEXTURE_2D, index);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	//SOIL_free_image_data(image);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//std::cout << "Texture.cpp::Ты textureSampler поставил?" << std::endl;
	glGenTextures(1, &index);
	glBindTexture(GL_TEXTURE_2D, index);
	image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); //----------------------------------------------------------------------------------------------------------
}

Texture::~Texture()
{
	delete[] image;
}

void Texture::setSampler(Shader* shader)
{
	glUniform1i(glGetUniformLocation(shader->shaderProgram, "textureSampler"), 0);
	//glUniformSampler2D(shader->shaderProgram, );
	DefaultShader kek;
}
