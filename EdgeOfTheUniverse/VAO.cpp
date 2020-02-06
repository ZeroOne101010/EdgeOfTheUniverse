#include "VAO.h"

VAO::VAO(VBO modelVBO, IBO modelIBO)
{
	this->modelVBO = modelVBO;
	this->modelIBO = modelIBO;

	glGenVertexArrays(1, &indexVAO);
	shader.linkToVAO(this);

	//ÇÀÏÎËÍÈÒÜ!!!
}

VAO::VAO(Shader shader, VBO modelVBO, IBO modelIBO)
{
	this->modelVBO = modelVBO;
	this->modelIBO = modelIBO;
	this->shader = shader;

	glGenVertexArrays(1, &indexVAO);
	shader.linkToVAO(this);

	shader.useShaderProgram();
}

void VAO::updateData(GLuint IDAttributeInArray, GLsizeiptr sizeData, GLfloat* data, GLenum typeDraw)
{
	shader.updateData(this, IDAttributeInArray, sizeData, data, typeDraw);
}

void VAO::draw()
{
	glBindVertexArray(indexVAO);
	glEnableVertexArrayAttrib(indexVAO, 0);
	for (int x = 0; x < shader.attribute.size(); x++)
	{
		glEnableVertexArrayAttrib(indexVAO, shader.attribute[x].index);
	}
	shader.useShaderProgram();
	glDrawElements(GL_TRIANGLES, modelIBO.size, GL_UNSIGNED_INT, 0);

	for (int x = 0; x < shader.attribute.size(); x++)
	{
		glDisableVertexArrayAttrib(indexVAO, shader.attribute[x].index);
	}
	glDisableVertexArrayAttrib(indexVAO, 0);

}


