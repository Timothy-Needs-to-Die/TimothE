#include "VBO.h"
#include "Base.h"

VBO::VBO(unsigned int size)
{
	glCreateBuffers(1, &_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VBO::VBO(float* vertices, unsigned int size)
{
	glCreateBuffers(1, &_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &_rendererID);
}

std::shared_ptr<VBO> VBO::Create(unsigned int size)
{
	return CreateRef<VBO>(size);
}

std::shared_ptr<VBO> VBO::Create(float* vertices, unsigned int size)
{
	return CreateRef<VBO>(vertices, size);
}



void VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
}

void VBO::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::SetData(const void* data, unsigned int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
