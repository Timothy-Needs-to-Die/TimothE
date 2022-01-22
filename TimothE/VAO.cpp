#include "VAO.h"
#include "GL/glew.h"

VAO::~VAO()
{
	glDeleteBuffers(1, &_ID);
}

void VAO::CreateVAO()
{
	//Generate Vertex Array Object Buffers
	glGenVertexArrays(1, &_ID);
	glBindVertexArray(_ID);
}

void VAO::BindBuffer()
{
	//Bind VAO
	glBindVertexArray(_ID);
}

void VAO::UnbindBuffer()
{
	//Unbind VAO
	glBindVertexArray(0);
}
