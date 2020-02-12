#include "IBO.h"

IBO::IBO()
{
	index = 0;
}

IBO::~IBO()
{
	glDeleteBuffers(1, &index);
}

IBO::IBO(GLsizeiptr size, GLuint* data, GLenum typeDraw)
{
	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	this->size = size / sizeof(GLuint);
}

void IBO::UpdateIBO(GLsizeiptr size, GLuint* data, GLenum typeDraw)
{
	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	this->size = size / sizeof(GLuint);
}
