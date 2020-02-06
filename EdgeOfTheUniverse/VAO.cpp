#include "VAO.h"

VAO::VAO(VBO modelVBO, IBO modelIBO)
{
	this->modelVBO = modelVBO;
	this->modelIBO = modelIBO;

	glGenVertexArrays(1, &indexVAO);
	shader->linkToVAO(this);

	//ÇÀÏÎËÍÈÒÜ!!!
}

VAO::VAO(Shader* shader, VBO modelVBO, IBO modelIBO)
{
	this->modelVBO = modelVBO;
	this->modelIBO = modelIBO;
	this->shader = shader;

	glGenVertexArrays(1, &indexVAO);
	shader->linkToVAO(this);

	shader->useShaderProgram();
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

	glDrawElements(GL_TRIANGLES, modelIBO.size, GL_UNSIGNED_INT, 0);

	for (int x = 0; x < shader->attribute.size(); x++)
	{
		glDisableVertexArrayAttrib(indexVAO, shader->attribute[x].index);
	}
	glDisableVertexArrayAttrib(indexVAO, 0);

}


