#include "RectangleShape.h"
GLfloat RectangleShape::RectangleShapeVertices[] = 
{
	 //0.0f,  0.0f, 0.0f,
	 //0.5f,  0.0f, 0.0f,
	 //0.5f,  -0.5f, 0.0f,
	 //0.0f,  -0.5f, 0.0f,
	 0.0f,  0.0f, 0.0f,
	 0.5f,  0.0f, 0.0f,
	 0.5f,  -0.5f, 0.0f,
	 0.0f,  -0.5f, 0.0f,
	// 0.5f,  0.5f, 0.0f,	
	// 0.5f, -0.5f, 0.0f,	
	//-0.5f, -0.5f, 0.0f,	
	//-0.5f,  0.5f, 0.0f,
};
GLuint RectangleShape::RectangleShapeIndices[] = 
{
	0, 1, 3,
	1, 2, 3
	//0, 1, 3,
	//1, 2, 3
};
GLfloat RectangleShape::RectangleShapeCoordsUV[] =
{
	 //1.0f, 1.0f,
	 //1.0f, 0.0f,
	 //0.0f, 0.0f,
	 //0.0f, 1.0f
	 0.0f, 0.0f,
	 1.0f, 0.0f,
	 1.0f, 1.0f,
	 0.0f, 1.0f
};
RectangleShape::RectangleShape(GLfloat sizeX, GLfloat sizeY) : Shape(VBO(sizeof(GLfloat) * 12, RectangleShapeVertices, GL_STREAM_DRAW), IBO(sizeof(GLuint) * 6, RectangleShapeIndices, GL_STREAM_DRAW), VBO(sizeof(GLfloat) * 12, RectangleShapeCoordsUV, GL_STREAM_DRAW))
{
	setRectangleSize();
	std::cout << "k" << std::endl;
	size = glm::vec2(sizeX, sizeY);
	//GLfloat vertices[] = {
	// 0.5f,  0.5f, 0.0f,
	// 0.5f, -0.5f, 0.0f,
	//-0.5f, -0.5f, 0.0f,
	//-0.5f,  0.5f, 0.0f
	//};
	//GLuint indices[] = {
	//0, 1, 3,
	//1, 2, 3
	//};
	//VBO modelVBO(sizeof(vertices), vertices, GL_STREAM_DRAW);
	//IBO modelIBO(sizeof(indices), indices, GL_STREAM_DRAW);
	//this->modelVBO = modelVBO;
	//this->modelIBO = modelIBO;
}

RectangleShape::RectangleShape(glm::vec2 size) : Shape(VBO(sizeof(GLfloat) * 12, RectangleShapeVertices, GL_STREAM_DRAW), IBO(sizeof(GLuint) * 6, RectangleShapeIndices, GL_STREAM_DRAW), VBO(sizeof(GLfloat) * 12, RectangleShapeCoordsUV, GL_STREAM_DRAW))
{
	setRectangleSize();
}

void RectangleShape::setDrawParams()
{
	Shape::setDrawParams();
}

void RectangleShape::setRectangleSize()
{

}
