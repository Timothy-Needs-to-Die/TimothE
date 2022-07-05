#pragma once

#include "pch.h"

#include "UID.h"
#include "Component.h"

#include "SOIL/stb_image.h"
#include "Core/Graphics/OpenGLError.h"

class Texture2D
{
public:
	Texture2D(std::string path, bool flip = true);
	Texture2D() {}
	~Texture2D();

	//Getters
	int GetHeight() { return _height; };
	int GetWidth() { return _width; };
	GLuint GetID() const { return _ID; }

	//Sets the filter mode for the texture
	void SetFilterMode(GLenum mode);

	//Loads an image from file into a texture. Returns true if successful or false if not
	bool Load(std::string path, bool flip = false);

	void Bind(int slot) {
		GLCall(glBindTextureUnit(slot, _ID));
	}

	void Generate(unsigned int width, unsigned int height, unsigned char* data);

private:
	void GenerateTexture(unsigned char* data);

	std::string _filePath;
	std::string _UID;
	
	//texture ID
	GLuint _ID; 

	int _width;
	int _height;
	int _channels;
};