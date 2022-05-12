#pragma once
#include <glm.hpp>
//#include <gl/glew.h>
#include "../../Texture2D.h"

// SubTexture referrs to a smaller texture created from a larger spritesheet
class SubTexture2D
{
public:
	SubTexture2D(Texture2D* texture, const glm::vec2& min, const glm::vec2& max);

	SubTexture2D CreateFromTexCoords(Texture2D* texture, const glm::vec2& coords, const glm::vec2& spriteSize);
	~SubTexture2D();

	const glm::vec2* GetTexCoords()const { return _texCoords; }
	const Texture2D* GetTexture() const { return _texture; }

private:

	//Processes the required spacing and division needed to create subtextures
	//from spritesheets (individual small textures from large multi texture image)
	void ProcessTexCoords(Texture2D* texture, const glm::vec2& min, const glm::vec2& max);
	
	GLuint _ID;
	glm::vec2 _texCoords[4];
	Texture2D* _texture;

};

