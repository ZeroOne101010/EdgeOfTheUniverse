#include "VBO.h"

VBO::VBO()
{
	index = 0;
	data = nullptr;
}

VBO::VBO(GLsizeiptr size, GLfloat* data, GLenum typeDraw)
{
	glGenBuffers(1, &index);
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, size, data, typeDraw);
	this->data = data;
}

VBO::~VBO()
{
	glDeleteBuffers(1, &index);
}

void VBO::UpdateData(GLsizeiptr size, GLfloat* data, GLenum typeDraw)
{
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, size, data, typeDraw);
	this->data = data;
}
