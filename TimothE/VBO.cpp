#include "VBO.h"
#include "GL/glew.h"

VBO::~VBO()
{
	glDeleteBuffers(1, &_ID);
}

void VBO::CreateVBO()
{
	//generate vertex array object buffers
	glGenBuffers(1, &_ID);
	glBindBuffer(GL_ARRAY_BUFFER, _ID);
}
