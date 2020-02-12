#include "VAO.h"

VAO::VAO(VBO modelVBO, IBO modelIBO, VBO textureUV)
{
	this->modelVBO = modelVBO;
	this->modelIBO = modelIBO;
	this->textureUV = textureUV;
	glGenVertexArrays(1, &indexVAO);
	shader->linkToVAO(this);
	worldPosIndex = glGetUniformLocation(shader->shaderProgram, "worldPos");
	localPosIndex = glGetUniformLocation(shader->shaderProgram, "localPos");
	rotationMatrixIndex = glGetUniformLocation(shader->shaderProgram, "rotation");
	colorIndex = glGetUniformLocation(shader->shaderProgram, "Color");
	relSizeIndex = glGetUniformLocation(shader->shaderProgram, "relSize");
	correctSizeIndex = glGetUniformLocation(shader->shaderProgram, "correctSize");
	sizeIndex = glGetUniformLocation(shader->shaderProgram, "size");

	shader->useShaderProgram();

	glBindVertexArray(indexVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	//ÇÀÏÎËÍÈÒÜ!!!
}

VAO::VAO(Shader* shader, VBO modelVBO, IBO modelIBO, VBO textureUV)
{
	this->modelVBO = modelVBO;
	this->modelIBO = modelIBO;
	this->textureUV = textureUV;
	this->shader = shader;

	glGenVertexArrays(1, &indexVAO);
	shader->linkToVAO(this);
	worldPosIndex = glGetUniformLocation(shader->shaderProgram, "worldPos");
	localPosIndex = glGetUniformLocation(shader->shaderProgram, "localPos");
	rotationMatrixIndex = glGetUniformLocation(shader->shaderProgram, "rotation");
	colorIndex = glGetUniformLocation(shader->shaderProgram, "Color");
	relSizeIndex = glGetUniformLocation(shader->shaderProgram, "relSize");
	correctSizeIndex = glGetUniformLocation(shader->shaderProgram, "correctSize");
	sizeIndex = glGetUniformLocation(shader->shaderProgram, "size");

	shader->useShaderProgram();

	glUniform3f(correctSizeIndex, correctSize.x, correctSize.y, 1);

	glBindVertexArray(indexVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
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
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->index);
	texture->setSampler(shader);
	glBindVertexArray(indexVAO);
	
	shader->useShaderProgram(); 
	setDrawParams();
	glDrawElements(GL_TRIANGLES, modelIBO.size, GL_UNSIGNED_INT, 0);
	//std::cout << position.x << " " << position.y << std::endl;
}

void VAO::setCoords()
{

	//glUniformMatrix4fv(rotationMatrixIndex, 1, GL_FALSE, glm::value_ptr(Rotation));
	////glUniform3f(localPosIndex, ((originPos.x / size.x * 250) / (Initialization::sizeConst / 2)), -((originPos.y / size.y * 250) / (Initialization::sizeConst / 2)), 0);
	//glUniform3f(localPosIndex, (Origin.x  / (RenderWindow::sizeConst / 2)), -(Origin.y / (RenderWindow::sizeConst / 2)), 0);
	////glUniform3f(localPosIndex, originPos.x, originPos.y, 0);
	//glUniform3f(worldPosIndex, (Position.x / RenderWindow::sizeConst) * 2 - 1, -((Position.y / RenderWindow::sizeConst) * 2 - 1), 0);
	////glUniform3f(worldPosIndex, position.x, position.y, 0);

	glUniformMatrix4fv(rotationMatrixIndex, 1, GL_FALSE, glm::value_ptr(Rotation));
	//glUniform3f(localPosIndex, ((originPos.x / size.x * 250) / (Initialization::sizeConst / 2)), -((originPos.y / size.y * 250) / (Initialization::sizeConst / 2)), 0);
	glUniform3f(localPosIndex, (drawOrigin.x / (RenderWindow::sizeConst / 2)), -(drawOrigin.y / (RenderWindow::sizeConst / 2)), 0);
	//glUniform3f(localPosIndex, originPos.x, originPos.y, 0);
	glUniform3f(worldPosIndex, (drawPosition.x / RenderWindow::sizeConst) * 2 - 1, -((drawPosition.y / RenderWindow::sizeConst) * 2 - 1), 0);
	//glUniform3f(worldPosIndex, position.x, position.y, 0);
}

void VAO::setSize()
{
	//glUniform3f(sizeIndex, size.x * (4 / RenderWindow::sizeConst), size.y * (4 / RenderWindow::sizeConst), 1);
	//glUniform3f(relSizeIndex, RelSize.x, RelSize.y, 0);
	//correctSize = glm::vec2(RenderWindow::sizeConst / RenderWindow::width, RenderWindow::sizeConst / RenderWindow::height);
	//glUniform3f(correctSizeIndex, correctSize.x, correctSize.y, 1);

	glUniform3f(sizeIndex, size.x * (4 / RenderWindow::sizeConst), size.y * (4 / RenderWindow::sizeConst), 1);
	glUniform3f(relSizeIndex, drawRelSize.x, drawRelSize.y, 0);
	correctSize = glm::vec2(RenderWindow::sizeConst / RenderWindow::width, RenderWindow::sizeConst / RenderWindow::height);
	glUniform3f(correctSizeIndex, correctSize.x, correctSize.y, 1);
}


void VAO::setDrawParams()
{
	setSize();
	setCoords();
	setColor();
}

void VAO::draw(Renderer* renderer, Alterable alters)
{
	//RelSize = alters.RelSize * relSize;
	//Position = (alters.Position + alters.Origin);
	//Origin = (origin + alters.Origin + position) * alters.RelSize;
	//Rotation = alters.Rotation * rotationMatrix;

	//RelSize = alters.RelSize * relSize;
	//Position = (alters.Position + alters.Origin);
	//Origin = (origin + alters.Origin + position) * alters.RelSize;
	Rotation = alters.Rotation * rotationMatrix;

	drawRelSize = alters.RelSize * RelSize;
	drawOrigin = Origin * alters.RelSize * RelSize;
	drawPosition = alters.Position + Position * alters.RelSize;

	draw();
}



