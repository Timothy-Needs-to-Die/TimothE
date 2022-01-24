#include "IBO.h"

IBO::IBO(unsigned int* indices, unsigned int count)
	: _count(count)
{
	glCreateBuffers(1, &_rendererID);

	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

IBO::~IBO()
{
	glDeleteBuffers(1, &_rendererID);
}

void IBO::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
}

void IBO::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
