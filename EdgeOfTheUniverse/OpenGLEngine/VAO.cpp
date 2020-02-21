#include "VAO.h"


//VAO::VAO(GLuint VAOBufferID, Shader* shader, Texture* texture, IBO* modelIBO)
VAO::VAO(GLuint VAOBufferID, Shader* shader, TBO* texture, IBO* modelIBO)
{
	this->shader = shader;
	//this->texture = texture;
	this->tbo = texture;
	this->modelIBO = modelIBO;
	indexVAO = VAOBufferID;


	worldPosIndex = shader->getUniformIndex("worldPos");
	localPosIndex = shader->getUniformIndex("localPos");
	angleIndex = shader->getUniformIndex("angle");
	colorIndex = shader->getUniformIndex("Color");
	relSizeIndex = shader->getUniformIndex("relSize");
	correctSizeIndex = shader->getUniformIndex("correctSize");
	sizeIndex = shader->getUniformIndex("size");
	optimizeModeIndex = shader->getUniformIndex("optimizeMode");;

	int k = 0;

	coordsUVIndex = shader->getUniformIndex("textureCoords");
	textureSamplerIndex = shader->getUniformIndex("textureSampler");

	//»спользу€ функцию Texture::setSampler(), можно добавить что то типо нормаль мапы и тд.  ороче передать несколько фоток в шейдер


	shader->useShaderProgram();

	glBindVertexArray(indexVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	//textureRect = FloatRect(0, 0, texture->width, texture->height);

	//«јѕќЋЌ»“№!!!
}

GLuint VAO::createVAOBuffer()
{
	GLuint index = 0;
	glGenVertexArrays(1, &index);
	return index;
}

//void VAO::setTexture(TBO* texture)
//{
//	texture.setSampler(shader, textureSamplerIndex, 0);
//	this->texture = texture;
//	textureRect = FloatRect(0, 0, this->texture->width, this->texture->height);	textureRect = FloatRect(0, 0, this->texture->width, this->texture->height);
//}

void VAO::setColor()
{
	glUniform4f(colorIndex, Color.x / (GLfloat)255, Color.y / (GLfloat)255, Color.z / (GLfloat)255, Color.a / (GLfloat)255);
}

//void VAO::addAttribute(VBO* vbo, GLuint indexAttribute)
//{
//	glBindVertexArray(indexVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo->index);
//
//	glVertexAttribPointer(countAttribute, vbo->attribute.size, vbo->attribute.type, vbo->attribute.normalized, vbo->attribute.stride, vbo->attribute.pointer);
//	glEnableVertexAttribArray(indexAttribute);
//
//	countAttribute++;
//
//	glBindVertexArray(0);
//}
//
//void VAO::bindVBO(VBO* vbo, GLuint indexAttribute)
//{
//	glBindVertexArray(indexVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo->index);
//
//	glVertexAttribPointer(indexAttribute, vbo->attribute.size, vbo->attribute.type, vbo->attribute.normalized, vbo->attribute.stride, vbo->attribute.pointer);
//	glEnableVertexAttribArray(indexAttribute);
//
//	glBindVertexArray(0);
//}

void VAO::bindVBOIBO(VBO* vbo, IBO* ibo, GLuint indexVAO, GLuint indexAttribute)
{
	glBindVertexArray(indexVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo->index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->index);

	glVertexAttribPointer(indexAttribute, vbo->attribute.size, vbo->attribute.type, vbo->attribute.normalized, vbo->attribute.stride, vbo->attribute.pointer);
	glEnableVertexAttribArray(indexAttribute);

	//glVertexAttribPointer(indexAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, 0);
	//glEnableVertexAttribArray(indexAttribute);

	glBindVertexArray(0);
}

//#include "../Content.h"
//#include "RectangleShape.h"
////RectangleShape::RectangleShape(GLfloat sizeX, GLfloat sizeY) : Shape(VBO(sizeof(GLfloat) * 12, RectangleShapeVertices, GL_STREAM_DRAW), IBO(sizeof(GLuint) * 6, RectangleShapeIndices, GL_STREAM_DRAW), VBO(sizeof(GLfloat) * 12, RectangleShapeCoordsUV, GL_STREAM_DRAW))
//RectangleShape::RectangleShape(GLfloat sizeX, GLfloat sizeY) : Shape(Content::indexRectangleShape, Content::defaultShader, Content::spriteList_Grass, Content::rectangleShapeIBO)
//{
//	Size = glm::vec2(sizeX, sizeY);
//}
//
//RectangleShape::RectangleShape(glm::vec2 size) : Shape(Content::indexRectangleShape, Content::defaultShader, Content::spriteList_Grass, Content::rectangleShapeIBO)
//{
//	Size = size;
//}
//
//void RectangleShape::setDrawParams()
//{
//	Shape::setDrawParams();
//}


void VAO::bindVBO(VBO* vbo, GLuint indexVAO, GLuint indexAttribute)
{
	glBindVertexArray(indexVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo->index);

	glVertexAttribPointer(indexAttribute, vbo->attribute.size, vbo->attribute.type, vbo->attribute.normalized, vbo->attribute.stride, vbo->attribute.pointer);
	glEnableVertexAttribArray(indexAttribute);

	glBindVertexArray(0);
}


void VAO::draw()
{
	tbo->bindToDrawTextureBuffers();

	glBindVertexArray(indexVAO);

	shader->useShaderProgram();
	setDrawParams();
	glDrawElements(GL_TRIANGLES, modelIBO->size, GL_UNSIGNED_INT, 0);
}

void VAO::setCoords()
{
	if (optimizeMode)
	{
		glUniform2f(worldPosIndex, drawPosition.x * 2 - RenderWindow::width, -(drawPosition.y * 2 - RenderWindow::height));
		glUniform4f(coordsUVIndex, textureRect.positionX / (GLfloat)tbo->sizeTexture[0].x, textureRect.positionY / (GLfloat)tbo->sizeTexture[0].y, textureRect.sizeX / (GLfloat)tbo->sizeTexture[0].x, textureRect.sizeY / (GLfloat)tbo->sizeTexture[0].y);
	}
	else
	{
		glUniform1f(angleIndex, drawAngle);
		glUniform2f(localPosIndex, (drawOrigin.x * 2), -(drawOrigin.y * 2));
		glUniform2f(worldPosIndex, drawPosition.x * 2 - RenderWindow::width, -(drawPosition.y * 2 - RenderWindow::height));
		glUniform4f(coordsUVIndex, textureRect.positionX / (GLfloat)tbo->sizeTexture[0].x, textureRect.positionY / (GLfloat)tbo->sizeTexture[0].y, textureRect.sizeX / (GLfloat)tbo->sizeTexture[0].x, textureRect.sizeY / (GLfloat)tbo->sizeTexture[0].y);
	}

}

void VAO::setSize()
{
	if (optimizeMode)
	{
		glUniform2f(sizeIndex, Size.x * 4, Size.y * 4);
		if (RenderWindow::changeWindow)
		{
			glUniform2f(correctSizeIndex, RenderWindow::correctSize.x, RenderWindow::correctSize.y);
			RenderWindow::changeWindow = false;
		}
	}
	else
	{
		glUniform2f(sizeIndex, Size.x * 4, Size.y * 4);
		glUniform2f(relSizeIndex, drawRelSize.x, drawRelSize.y);
		if (RenderWindow::changeWindow)
		{
			glUniform2f(correctSizeIndex, RenderWindow::correctSize.x, RenderWindow::correctSize.y);
			RenderWindow::changeWindow = false;
		}
	}
}


void VAO::setDrawParams()
{
	glUniform1i(optimizeModeIndex, optimizeMode ? 1 : 0);
	setSize();
	setCoords();
	setColor();
}

void VAO::draw(Renderer* renderer, Alterable alters)
{
	if (optimizeMode)
	{
		drawPosition = alters.Position + Position * alters.RelSize;
	}
	else
	{
		drawAngle = alters.Angle + Angle;
		drawRelSize = alters.RelSize * RelSize;
		drawOrigin = Origin * alters.RelSize * RelSize;

		glm::vec2 p = Position * alters.RelSize;
		glm::vec2 localPos = glm::vec2(p.x * cos(drawAngle) - p.y * sin(drawAngle), p.x * sin(drawAngle) + p.y * cos(drawAngle));
		drawPosition = alters.Position + localPos;
	}
	draw();
}



