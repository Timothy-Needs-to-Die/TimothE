#include "Framebuffer.h"

Framebuffer::Framebuffer(Window* pWindow, Shader* screenShader, float* quadVertices)
	: _pScreenShader(screenShader), _pQuadVertices(quadVertices), _pWindow(pWindow)
{
	CreateFramebuffer();
}

Framebuffer::Framebuffer(Window* pWindow, Shader* screenShader)
	: _pScreenShader(screenShader), _pWindow(pWindow)
{
	_pQuadVertices = new float[24]{
		// positions   // texCoords
		-1.0f,  -1.0f,  0.0f, 0.0f, //Bottom left
		-1.0f,   1.0f,	0.0f, 1.0f, //Top Left
		 1.0f,   1.0f,	1.0f, 1.0f, //Top Right

		 1.0f,  -1.0f,  1.0f, 0.0f, //Bottom Right
		-1.0f,  -1.0f,	0.0f, 0.0f, //Bottom Left
		 1.0f,   1.0f,   1.0f, 1.0f //Top Right
	};

	CreateFramebuffer();
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &_fbo);

	delete[] _pQuadVertices;
	_pQuadVertices = nullptr;
}

void Framebuffer::CreateFramebuffer()
{
	//Generate Quad VAO and VBO
	//VAO
	_vao.CreateVAO();
	//VBO
	_vbo.CreateVBO();

	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), _pQuadVertices, GL_STATIC_DRAW);

	//Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	//Texcoords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	//Set the texture to 0
	_pScreenShader->BindShader();
	_pScreenShader->SetInt("screenTexture", 0);

	//Generate frame buffer objects
	glGenFramebuffers(1, &_fbo);
	BindFramebuffer();

	// create a color attachment texture
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _pWindow->GetWidth(), _pWindow->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);
	// create a render buffer object for depth and stencil attachment (we won't be sampling these)

	//Generate the render buffer objects
	_rbo.CreateRBO();

	//Adds the depth stencil attachments
	_rbo.AddDepthStencil();

	// now that we actually created the frame buffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;


	UnbindFramebuffer();
}

void Framebuffer::BindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

void Framebuffer::UnbindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::BindShader()
{
	_pScreenShader->BindShader();
}

void Framebuffer::DrawFramebuffer()
{
	//Bind Vertex Array
	_vao.BindBuffer();

	BindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Framebuffer::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, _texture);
}
