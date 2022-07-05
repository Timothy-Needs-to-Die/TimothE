#include "pch.h"
#include "PostProcessor.h"
#include <iostream>

PostProcessor::PostProcessor(Shader* shader, unsigned int width, unsigned int height)
	: _postProcessingShader(shader), _width(width), _height(height), _texture(), _confuse(false), _chaos(false), _shake(false)
{
	_texture.Generate(width, height, NULL);
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture.GetID(), 0));
	
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	// create a color attachment texture
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture.GetID(), 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "[PostProcessor.cpp]: Failed to initialize FBO" << std::endl;
	}

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	InitRenderData();

	_postProcessingShader->BindShader();
	_postProcessingShader->SetInt("screenTexture", 0);
}

void PostProcessor::BeginRender()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, FBO));
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void PostProcessor::EndRender()
{
	//GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, MSFBO));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void PostProcessor::Render(float time)
{
	_postProcessingShader->BindShader();

	GLCall(glActiveTexture(GL_TEXTURE0));
	_texture.Bind(0);
	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	GLCall(glBindVertexArray(0));
}

void PostProcessor::ResetState()
{
	_confuse = false;
	_chaos = false;
	_shake = false;
}

void PostProcessor::InitRenderData()
{
	unsigned int VBO;
	float vertices[] = {
		// pos        // tex
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f
	};
	GLCall(glGenVertexArrays(1, &this->VAO));
	GLCall(glGenBuffers(1, &VBO));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLCall(glBindVertexArray(this->VAO));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}
