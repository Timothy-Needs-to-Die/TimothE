#include "RBO.h"
#include "GL/glew.h"

RBO::~RBO()
{
	glDeleteRenderbuffers(1, &_ID);
}

void RBO::CreateRBO()
{
	//Generate the render buffer objects
	glGenRenderbuffers(1, &_ID);
	glBindRenderbuffer(GL_RENDERBUFFER, _ID);
}

void RBO::AddDepthStencil()
{
	//Adds the depth stencil attachments
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _ID);
}
