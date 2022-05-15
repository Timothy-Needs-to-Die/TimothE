#include "../../pch.h"
#include "RBO.h"
#include "GL/glew.h"
#include "OpenGLError.h"
#include "Window.h"

RBO::~RBO()
{
	GLCall(glDeleteRenderbuffers(1, &_ID));
}

void RBO::CreateRBO()
{
	//Generate the render buffer objects
	GLCall(glGenRenderbuffers(1, &_ID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, _ID));
}

void RBO::AddDepthStencil()
{
	//Adds the depth stencil attachments
	//TODO: Link this to window size
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::GetWidth(), Window::GetHeight()));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _ID));
}
