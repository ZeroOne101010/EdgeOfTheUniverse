#include "VAO.h"
#include "Shader.h"

Shader::Shader()
{
	vertexShader = NULL;
	fragmentShader = NULL;
	shaderProgram = NULL;
}

Shader::Shader(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::setShaderSource(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::linkToVAO(VAO* vao)
{
	glBindVertexArray(vao->indexVAO);

	glBindBuffer(GL_ARRAY_BUFFER, vao->modelVBO.index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->modelIBO.index);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);
	for (int x = 0; x < attribute.size(); x++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, attribute[x].vbo.index);
		glVertexAttribPointer(attribute[x].index, attribute[x].size, attribute[x].type, attribute[x].normalized, attribute[x].stride, attribute[x].pointer);
		glEnableVertexAttribArray(attribute[x].index);
	}

	glBindVertexArray(0);
}

void Shader::updateData(VAO * vao, GLuint IDAttributeInArray, GLsizeiptr sizeData, GLfloat* data, GLenum typeDraw)
{
	if (IDAttributeInArray >= 1)
	{
		attribute[IDAttributeInArray - 1].vbo.UpdateData(sizeData, data, typeDraw);
	}
	else
	{
		vao->modelVBO.UpdateData(sizeData, data, typeDraw);
	}
}



void Shader::useShaderProgram()
{
	glUseProgram(shaderProgram);
}

void Shader::addAttribute(VBO vbo, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	Attribute attribute;
	attribute.vbo = vbo;
	attribute.index = index;
	attribute.size = size;
	attribute.type = type;
	attribute.normalized = normalized;
	attribute.stride = stride;
	attribute.pointer = pointer;
	this->attribute.push_back(attribute);
}
