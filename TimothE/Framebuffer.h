#pragma once

#include "GL/glew.h"
#include <glfw/glfw3.h>

#include "Shader.h"

#include <iostream>

//TODO: Add a way to take in a custom texture size
class Framebuffer
{
public:
	//Creates a frame buffer with a predefined set of vertices
	Framebuffer(Shader* screenShader, float* quadVertices);
	//Creates a frame buffer with a whole screen quad defined for vertices
	Framebuffer(Shader* screenShader);

	~Framebuffer();

	//Binds this frame buffer to the opengl pipeline
	void BindFramebuffer();

	//Unbinds this frame buffer to the opengl pipeline
	void UnbindFramebuffer();

	//Binds the quad vao attached to this frame buffer
	void BindVAO();

	//Unbinds the quad vao attached to this frame buffer
	void UnbindVAO();

	//Binds the screen shader 
	void BindShader();

	//Draws the quad to the screen
	void DrawFramebuffer();

	//Binds the texture
	void BindTexture();

	int GetTexture() const { return _texture; }

	//Gets the shader attached to this framebuffer
	Shader* GetAttachedShader() const { return _pScreenShader; }
private:
	//TODO: Abstract VAO and VBO generation to separate classes
	//Creates the frame buffer, render buffer, texture, quadVAO, and quadVBO
	void CreateFramebuffer();

	Shader* _pScreenShader;

	float* _pQuadVertices;

	unsigned int _fbo;
	unsigned int _rbo;
	unsigned int _texture;
	unsigned int _VAO;
	unsigned int _VBO;
};

