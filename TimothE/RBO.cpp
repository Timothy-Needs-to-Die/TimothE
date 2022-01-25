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
	//TODO: Link this to window size
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _ID);
}
