#include "../../pch.h"
#include "Framebuffer.h"
#include "Base.h"
#include "OpenGLError.h"

Framebuffer::Framebuffer(Shader* screenShader, float* quadVertices)
	: _pScreenShader(screenShader), _pQuadVertices(quadVertices)
{
	_vbo = VBO::Create(_pQuadVertices, 24);
	CreateFramebuffer();
}

Framebuffer::Framebuffer(Shader* screenShader)
	: _pScreenShader(screenShader)
{
	_pQuadVertices = new float[24]{
		// positions   // texCoords
		-1.0f, -1.0f, 0.0f, 0.0f, //Bottom left
		 1.0f,  1.0f, 1.0f, 1.0f, //Top right
		-1.0f,  1.0f, 0.0f, 1.0f, //Top left

		-1.0f, -1.0f, 0.0f, 0.0f, //Bottom left
		 1.0f, -1.0f, 1.0f, 0.0f, //Bottom Right
		 1.0f,  1.0f, 1.0f, 1.0f //Top Right
	};

	_vbo = CreateRef<VBO>(_pQuadVertices, 24 * sizeof(float));
	CreateFramebuffer();
}

Framebuffer::~Framebuffer()
{
	GLCall(glDeleteFramebuffers(1, &_fbo));

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
	GLCall(glGenFramebuffers(1, &_fbo));
	BindFramebuffer();

	// create a color attachment texture
	RefreshTexture();





	// now that we actually created the frame buffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;


	UnbindFramebuffer();
}

void Framebuffer::BindFramebuffer()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, _fbo));
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Framebuffer::RefreshTexture()
{
	BindFramebuffer();

	if (_texture != 0) {
		GLCall(glDeleteTextures(1, &_texture));
	}

	GLCall(glGenTextures(1, &_texture));
	GLCall(glBindTexture(GL_TEXTURE_2D, _texture));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::GetWidth(), Window::GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0));

	UnbindFramebuffer();
}

void Framebuffer::RefreshRBO()
{
	BindFramebuffer();
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::GetWidth(), Window::GetHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	UnbindFramebuffer();
}

void Framebuffer::UnbindFramebuffer()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	glDisable(GL_DEPTH_TEST); 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Framebuffer::BindShader()
{
	_pScreenShader->BindShader();
}

void Framebuffer::DrawFramebuffer()
{
	//Bind Vertex Array
	_vao->Bind();

	_pScreenShader->BindShader();
	_pScreenShader->SetInt("screenTexture", 0);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);


	//BindTexture();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void Framebuffer::BindTexture()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, _texture));
}
