#include "VAO.h"

VAO::VAO(VBO modelVBO, IBO modelIBO)
{
	this->modelVBO = modelVBO;
	this->modelIBO = modelIBO;

	glGenVertexArrays(1, &indexVAO);
	shader->linkToVAO(this);
	worldPosIndex = glGetUniformLocation(shader->shaderProgram, "worldPos");
	localPosIndex = glGetUniformLocation(shader->shaderProgram, "localPos");
	rotationMatrixIndex = glGetUniformLocation(shader->shaderProgram, "rotation");
	colorIndex = glGetUniformLocation(shader->shaderProgram, "Color");
	shader->useShaderProgram();
	glm::mat4 positionMatrix;
	glm::mat4 originPosMatrix;

	glBindVertexArray(indexVAO);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//ÇÀÏÎËÍÈÒÜ!!!
}

VAO::VAO(Shader* shader, VBO modelVBO, IBO modelIBO)
{
	this->modelVBO = modelVBO;
	this->modelIBO = modelIBO;
	this->shader = shader;

	glGenVertexArrays(1, &indexVAO);
	shader->linkToVAO(this);
	worldPosIndex = glGetUniformLocation(shader->shaderProgram, "worldPos");
	localPosIndex = glGetUniformLocation(shader->shaderProgram, "localPos");
	rotationMatrixIndex = glGetUniformLocation(shader->shaderProgram, "rotation");
	colorIndex = glGetUniformLocation(shader->shaderProgram, "Color");
	shader->useShaderProgram();
	glm::mat4 positionMatrix;
	glm::mat4 originPosMatrix;

	glBindVertexArray(indexVAO);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &indexVAO);
	glDeleteBuffers(1, &modelVBO.index);
	glDeleteBuffers(1, &modelIBO.index);
	glDeleteProgram(shader->shaderProgram);
	delete shader;
}

void VAO::setColor()
{
	glUniform4f(colorIndex, color.x, color.y, color.z, color.a);
}

void VAO::updateData(GLuint IDAttributeInArray, GLsizeiptr sizeData, GLfloat* data, GLenum typeDraw)
{
	shader->updateData(this, IDAttributeInArray, sizeData, data, typeDraw);
}


void VAO::draw()
{
	glBindVertexArray(indexVAO);
	//glEnableVertexAttribArray(0);
	//for (int x = 0; x < shader->attribute.size(); x++)
	//{
	//	glEnableVertexAttribArray(shader->attribute[x].index);
	//}
	shader->useShaderProgram();
	setCoords();
	setColor();
	glDrawElements(GL_TRIANGLES, modelIBO.size, GL_UNSIGNED_INT, 0);

	//for (int x = 0; x < shader->attribute.size(); x++)
	//{
	//	glDisableVertexAttribArray(shader->attribute[x].index);
	//}
	//glDisableVertexAttribArray(0);
}

void VAO::setCoords()
{
	glUniformMatrix4fv(rotationMatrixIndex, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniform3f(localPosIndex, originPos.x, originPos.y, 0);
	glUniform3f(worldPosIndex, position.x, position.y, 0);
}


