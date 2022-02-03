#include "Framebuffer.h"
#include "Base.h"

Framebuffer::Framebuffer(Shader* screenShader, float* quadVertices)
	: _pScreenShader(screenShader), _pQuadVertices(quadVertices)
{
	CreateFramebuffer();
	_vbo = VBO::Create(_pQuadVertices, 24);
}

Framebuffer::Framebuffer(Shader* screenShader)
	: _pScreenShader(screenShader)
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

	_vbo = CreateRef<VBO>(_pQuadVertices, 24);
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
	_vbo->SetLayout({
		{ ShaderDataTypes::Float2, "aPos"     },
		{ ShaderDataTypes::Float2, "aTexCoords"     },
		});

	_vao = VAO::Create();

	_vao->AddVertexBuffer(_vbo);

	//Set the texture to 0
	_pScreenShader->BindShader();
	_pScreenShader->SetInt("screenTexture", 0);

	//Generate frame buffer objects
	glGenFramebuffers(1, &_fbo);
	BindFramebuffer();

	// create a color attachment texture
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::GetWidth(), Window::GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);
	// create a render buffer object for depth and stencil attachment (we won't be sampling these)

	//Generate the render buffer objects
	_rbo = new RBO();
	_rbo->CreateRBO();

	//Adds the depth stencil attachments
	_rbo->AddDepthStencil();

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
	_vao->Bind();

	BindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Framebuffer::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, _texture);
}
