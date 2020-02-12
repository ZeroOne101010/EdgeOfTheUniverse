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
	rotationMatrixIndex = glGetUniformLocation(shader->shaderProgram, "rotation");
	colorIndex = glGetUniformLocation(shader->shaderProgram, "Color");
	relSizeIndex = glGetUniformLocation(shader->shaderProgram, "relSize");
	correctSizeIndex = glGetUniformLocation(shader->shaderProgram, "correctSize");
	sizeIndex = glGetUniformLocation(shader->shaderProgram, "size");

	shader->useShaderProgram();

	glBindVertexArray(indexVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	//ÇÀÏÎËÍÈÒÜ!!!
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
	rotationMatrixIndex = glGetUniformLocation(shader->shaderProgram, "rotation");
	colorIndex = glGetUniformLocation(shader->shaderProgram, "Color");
	relSizeIndex = glGetUniformLocation(shader->shaderProgram, "relSize");
	correctSizeIndex = glGetUniformLocation(shader->shaderProgram, "correctSize");
	sizeIndex = glGetUniformLocation(shader->shaderProgram, "size");

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
	texture->setSampler(shader);
	glBindVertexArray(indexVAO);
	
	shader->useShaderProgram(); 
	setDrawParams();
	glDrawElements(GL_TRIANGLES, modelIBO.size, GL_UNSIGNED_INT, 0);
}

void VAO::setCoords()
{
	glUniformMatrix4fv(rotationMatrixIndex, 1, GL_FALSE, glm::value_ptr(Rotation));
	glUniform3f(localPosIndex, (drawOrigin.x / (RenderWindow::sizeConst / 2)), -(drawOrigin.y / (RenderWindow::sizeConst / 2)), 0);
	glUniform3f(worldPosIndex, (drawPosition.x / RenderWindow::sizeConst) * 2 - 1, -((drawPosition.y / RenderWindow::sizeConst) * 2 - 1), 0);
}

void VAO::setSize()
{
	glUniform3f(sizeIndex, Size.x * (4 / RenderWindow::sizeConst), Size.y * (4 / RenderWindow::sizeConst), 1);
	glUniform3f(relSizeIndex, drawRelSize.x, drawRelSize.y, 0);
	correctSize = glm::vec2(RenderWindow::sizeConst / RenderWindow::width, RenderWindow::sizeConst / RenderWindow::height);
	glUniform3f(correctSizeIndex, correctSize.x, correctSize.y, 1);
}


void VAO::setDrawParams()
{
	setSize();
	setCoords();
	setColor();
}

void VAO::draw(Renderer* renderer, Alterable alters)
{
	Rotation = alters.Rotation * rotation;
	drawRelSize = alters.RelSize * RelSize;
	drawOrigin = Origin * alters.RelSize * RelSize;
	drawPosition = alters.Position + Position * alters.RelSize;
	draw();
}



