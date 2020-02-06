#include "VAO.h"

VAO::VAO(VBO modelVBO, IBO modelIBO)
{
	this->modelVBO = modelVBO;
	this->modelIBO = modelIBO;

	glGenVertexArrays(1, &indexVAO);
	shader->linkToVAO(this);
	worldPosIndex = glGetUniformLocation(shader->shaderProgram, "worldPos");
	localPosIndex = glGetUniformLocation(shader->shaderProgram, "localPos");
	shader->useShaderProgram();
	glm::mat4 positionMatrix;
	glm::mat4 originPosMatrix;
	glUniformMatrix4fv(worldPosIndex, 1, GL_FALSE, glm::value_ptr(positionMatrix));
	glUniformMatrix4fv(localPosIndex, 1, GL_FALSE, glm::value_ptr(originPosMatrix));

	//ÇÀÏÎËÍÈÒÜ!!!
}

VAO::VAO(Shader* shader, VBO modelVBO, IBO modelIBO)
{
	this->modelVBO = modelVBO;
	this->modelIBO = modelIBO;
	this->shader = shader;

	glGenVertexArrays(1, &indexVAO);
	shader->linkToVAO(this);

}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &indexVAO);
	glDeleteBuffers(1, &modelVBO.index);
	glDeleteBuffers(1, &modelIBO.index);
	glDeleteProgram(shader->shaderProgram);
	delete shader;
}

void VAO::setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A)
{
	GLuint index = glGetUniformLocation(shader->shaderProgram, "Color");

	shader->useShaderProgram();
	glUniform4f(index, R, G, B, A);
}

void VAO::updateData(GLuint IDAttributeInArray, GLsizeiptr sizeData, GLfloat* data, GLenum typeDraw)
{
	shader->updateData(this, IDAttributeInArray, sizeData, data, typeDraw);
}


void VAO::draw()
{
	glBindVertexArray(indexVAO);
	glEnableVertexArrayAttrib(indexVAO, 0);
	for (int x = 0; x < shader->attribute.size(); x++)
	{
		glEnableVertexArrayAttrib(indexVAO, shader->attribute[x].index);
	}
	shader->useShaderProgram();
	setCoords();
	glDrawElements(GL_TRIANGLES, modelIBO.size, GL_UNSIGNED_INT, 0);

	for (int x = 0; x < shader->attribute.size(); x++)
	{
		glDisableVertexArrayAttrib(indexVAO, shader->attribute[x].index);
	}
	glDisableVertexArrayAttrib(indexVAO, 0);
}

void VAO::setCoords()
{
	glm::mat4 positionMatrix;
	glm::mat4 originPosMatrix;
	originPosMatrix = glm::translate(glm::mat4(), glm::vec3(originPos.x / Initialization::winWidth, originPos.y / Initialization::winWidth, 0));
	positionMatrix = glm::translate(glm::mat4(), glm::vec3(position.x / Initialization::winWidth, position.y / Initialization::winWidth, 0));
	shader->useShaderProgram();
	glUniformMatrix4fv(localPosIndex, 1, GL_FALSE, glm::value_ptr(originPosMatrix));
	glUniformMatrix4fv(worldPosIndex, 1, GL_FALSE, glm::value_ptr(positionMatrix));
}


