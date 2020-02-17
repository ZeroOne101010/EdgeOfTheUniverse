#include "VBO.h"

VBO::VBO()
{
	index = NULL;
	data = nullptr;
	attribute = Attribute();
}

VBO::VBO(GLsizeiptr size, GLfloat* data, GLenum typeDraw, Attribute attribute)
{
	glGenBuffers(1, &index);
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, size, data, typeDraw);
	this->data = data;
	this->attribute = attribute;
}

VBO::VBO(GLsizeiptr size, GLfloat* data, GLenum typeDraw, GLint sizeAttribute, GLenum typeAttribute, GLboolean normalizedAttribute, GLsizei strideAttribute, const void* pointerAttribute)
{
	glGenBuffers(1, &index);
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, size, data, typeDraw);
	this->data = data;
	Attribute attribute;
	attribute.size = size;
	attribute.type = typeAttribute;
	attribute.normalized = normalizedAttribute;
	attribute.stride = strideAttribute;
	attribute.pointer = pointerAttribute;
	this->attribute = attribute;
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

void VBO::setAttribute(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	Attribute attribute;
	attribute.size = size;
	attribute.type = type;
	attribute.normalized = normalized;
	attribute.stride = stride;
	attribute.pointer = pointer;
	this->attribute = attribute;
}
