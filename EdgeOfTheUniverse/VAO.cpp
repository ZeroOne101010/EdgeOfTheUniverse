#include "VAO.h"

VAO::VAO(VBO modelVBO, IBO modelIBO, VBO textureUV)
{
	this->modelVBO = modelVBO;
	this->modelIBO = modelIBO;
	this->textureUV = textureUV;
	glGenVertexArrays(1, &indexVAO);
	shader->linkToVAO(this);
	worldPosIndex = glGetUniformLocation(shader->shaderProgram, "worldPos");
	localPosIndex = glGetUniformLocation(shader->shaderProgram, "localPos");
	angleIndex = glGetUniformLocation(shader->shaderProgram, "angle");
	colorIndex = glGetUniformLocation(shader->shaderProgram, "Color");
	relSizeIndex = glGetUniformLocation(shader->shaderProgram, "relSize");
	correctSizeIndex = glGetUniformLocation(shader->shaderProgram, "correctSize");
	sizeIndex = glGetUniformLocation(shader->shaderProgram, "size");

	coordsUVIndex = glGetUniformLocation(shader->shaderProgram, "textureCoords");
	textureSamplerIndex = glGetUniformLocation(shader->shaderProgram, "textureSampler");

	texture->setSampler(shader, textureSamplerIndex, 0); /////////////////////////////////////////»спользу€ эту функцию, можно добавить что то типо нормаль мапы и тд.  ороче передать несколько фоток в шейдер


	shader->useShaderProgram();

	glBindVertexArray(indexVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	textureRect = FloatRect(0, 0, texture->width, texture->height);

	//«јѕќЋЌ»“№!!!
}

VAO::VAO(Shader* shader, VBO modelVBO, IBO modelIBO, VBO textureUV)
{
	this->modelVBO = modelVBO;
	this->modelIBO = modelIBO;
	this->textureUV = textureUV;
	this->shader = shader;

	glGenVertexArrays(1, &indexVAO);
	shader->linkToVAO(this);
	worldPosIndex = glGetUniformLocation(shader->shaderProgram, "worldPos");
	localPosIndex = glGetUniformLocation(shader->shaderProgram, "localPos");
	angleIndex = glGetUniformLocation(shader->shaderProgram, "angle");
	colorIndex = glGetUniformLocation(shader->shaderProgram, "Color");
	relSizeIndex = glGetUniformLocation(shader->shaderProgram, "relSize");
	correctSizeIndex = glGetUniformLocation(shader->shaderProgram, "correctSize");
	sizeIndex = glGetUniformLocation(shader->shaderProgram, "size");

	coordsUVIndex = glGetUniformLocation(shader->shaderProgram, "textureCoords");
	textureSamplerIndex = glGetUniformLocation(shader->shaderProgram, "textureSampler");
	
	shader->useShaderProgram();

	glUniform3f(correctSizeIndex, correctSize.x, correctSize.y, 1);

	glBindVertexArray(indexVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &indexVAO);
	glDeleteBuffers(1, &modelVBO.index);
	glDeleteBuffers(1, &modelIBO.index);
	glDeleteProgram(shader->shaderProgram);
	delete shader;
	delete texture;
}

void VAO::setTexture(Texture texture)
{
	texture.setSampler(shader, textureSamplerIndex, 0);
	this->texture = &texture;
	textureRect = FloatRect(0, 0, this->texture->width, this->texture->height);	textureRect = FloatRect(0, 0, this->texture->width, this->texture->height);
}

void VAO::setColor()
{
	glUniform4f(colorIndex, Color.x, Color.y, Color.z, Color.a);
}

void VAO::updateData(GLuint IDAttributeInArray, GLsizeiptr sizeData, GLfloat* data, GLenum typeDraw)
{
	shader->updateData(this, IDAttributeInArray, sizeData, data, typeDraw);
}


void VAO::draw()
{
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, texture->index);

	glBindVertexArray(indexVAO);

	shader->useShaderProgram(); 
	setDrawParams();
	glDrawElements(GL_TRIANGLES, modelIBO.size, GL_UNSIGNED_INT, 0);
}

void VAO::setCoords()
{
	glUniform1f(angleIndex, drawAngle);
	glUniform2f(localPosIndex, (drawOrigin.x / (RenderWindow::sizeConst / 2)), -(drawOrigin.y / (RenderWindow::sizeConst / 2)));
	glUniform2f(worldPosIndex, (drawPosition.x / RenderWindow::sizeConst) * 2 - 1, -((drawPosition.y / RenderWindow::sizeConst) * 2 - 1));
	//glUniform4f(coordsUVIndex, (textureRect.positionX / ((GLfloat)texture->width / 2)), (textureRect.positionY / ((GLfloat)texture->height / 2)), textureRect.sizeX / (GLfloat)texture->width, textureRect.sizeY * (GLfloat)texture->height);
	glUniform4f(coordsUVIndex, textureRect.positionX / (GLfloat)texture->width, textureRect.positionY / (GLfloat)texture->height, textureRect.sizeX / (GLfloat)texture->width, textureRect.sizeY / (GLfloat)texture->height);
}

void VAO::setSize()
{
	glUniform2f(sizeIndex, Size.x * (4 / RenderWindow::sizeConst), Size.y * (4 / RenderWindow::sizeConst));
	glUniform2f(relSizeIndex, drawRelSize.x, drawRelSize.y);
	correctSize = glm::vec2(RenderWindow::sizeConst / RenderWindow::width, RenderWindow::sizeConst / RenderWindow::height);
	glUniform2f(correctSizeIndex, correctSize.x, correctSize.y);
}


void VAO::setDrawParams()
{
	setSize();
	setCoords();
	setColor();
}

void VAO::draw(Renderer* renderer, Alterable alters)
{
	//Rotation = alters.Rotation * rotation;
	drawAngle = alters.Angle + Angle;
	drawRelSize = alters.RelSize * RelSize;
	drawOrigin = Origin * alters.RelSize * RelSize;
	drawPosition = alters.Position + Position * alters.RelSize;
	draw();
}



