#include "IBO.h"
#include "Base.h"
#include "OpenGLError.h"


IBO::IBO(unsigned int* indices, unsigned int count)
	: _count(count)
{
	GLCall(glCreateBuffers(1, &_rendererID));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

IBO::~IBO()
{
	GLCall(glDeleteBuffers(1, &_rendererID));
}

void IBO::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
}
 
void IBO::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

std::shared_ptr<IBO> IBO::Create(unsigned int* indices, unsigned int count)
{
	return CreateRef<IBO>(indices, count);
}
