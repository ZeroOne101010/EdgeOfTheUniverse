#include "DefaultShader.h"


DefaultShader::DefaultShader(const GLchar* pathVertex, const GLchar* pathFragment) : Shader(pathVertex, pathFragment)
	{
		worldPosIndex = createUniformIndex("worldPos");
		localPosIndex = createUniformIndex("localPos");
		angleIndex = createUniformIndex("angle");
		colorIndex = createUniformIndex("Color");
		relSizeIndex = createUniformIndex("relSize");
		correctSizeIndex = createUniformIndex("correctSize");
		sizeIndex = createUniformIndex("size");

		coordsUVIndex = createUniformIndex("textureCoords");
		textureSamplerIndex = createUniformIndex("textureSampler");

		useShaderProgram();
	}

	void DefaultShader::setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A)
	{
		GLuint index = glGetUniformLocation(shaderProgram, "Color");

		useShaderProgram();
		glUniform4f(index, R, G, B, A);
	}