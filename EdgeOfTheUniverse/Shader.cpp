#include "VAO.h"
#include "Shader.h"

Shader::Shader()
{
	vertexShader = NULL;
	fragmentShader = NULL;
	shaderProgram = NULL;
	pathVertex = NULL;
	pathFragment = NULL;
}
Shader::Shader(const GLchar* pathVertex, const GLchar* pathFragment)
{
	this->pathVertex = pathVertex;
	this->pathFragment = pathFragment;
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	vertexShaderFile.exceptions(std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		vertexShaderFile.open(pathVertex);
		fragmentShaderFile.open(pathFragment);
		std::stringstream vertexShaderStream, fragmentShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		vertexShaderFile.close();
		fragmentShaderFile.close();
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Can't to read a shader file!" << std::endl;
		glfwTerminate();
	}
	const GLchar* vertexShaderCode = vertexCode.c_str();
	const GLchar* fragmentShaderCode = fragmentCode.c_str();
	GLuint vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);
	VerifySuccess(vertexShader, "VERTEX::Failed to compile vertex shader!\n");
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);
	VerifySuccess(fragmentShader, "FRAGMENT::Failed to compile fragment shader!\n");
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	VerifySuccess(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
}

void Shader::setShaderFromSource(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource)
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

void Shader::setShader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
{
	this->pathVertex = pathVertex;
	this->pathFragment = pathFragment;
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	vertexShaderFile.exceptions(std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		vertexShaderFile.open(pathVertex);
		fragmentShaderFile.open(pathFragment);
		std::stringstream vertexShaderStream, fragmentShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		vertexShaderFile.close();
		fragmentShaderFile.close();
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Can't to read a shader file!" << std::endl;
		glfwTerminate();
	}
	const GLchar* vertexShaderCode = vertexCode.c_str();
	const GLchar* fragmentShaderCode = fragmentCode.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);
	VerifySuccess(vertexShader, "VERTEX::Failed to compile vertex shader!\n");

	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);
	VerifySuccess(fragmentShader, "FRAGMENT::Failed to compile fragment shader!\n");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	VerifySuccess(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::VerifySuccess(GLuint shader, std::string error)
{
	GLint success;
	GLchar infolog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infolog);
		std::cout << error << infolog << std::endl;
	}
}

void Shader::VerifySuccess(GLuint program)
{
	GLint success;
	GLchar infolog[512];
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infolog);
		std::cout << "PROGRAM::Failed to link program!\n" << infolog << std::endl;
	}
}

void Shader::linkToVAO(VAO* vao)
{
	glBindVertexArray(vao->indexVAO);

	glBindBuffer(GL_ARRAY_BUFFER, vao->modelVBO.index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->modelIBO.index);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vao->textureUV.index);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, 0);

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
	if (IDAttributeInArray >= 2)
	{
		attribute[IDAttributeInArray - 2].vbo.UpdateData(sizeData, data, typeDraw);
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
