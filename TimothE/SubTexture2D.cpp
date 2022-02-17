#include "SubTexture2D.h"

SubTexture2D::SubTexture2D(Texture2D* texture, const glm::vec2& min, const glm::vec2& max)
{
	ProcessTexCoords(texture, min, max);
}

SubTexture2D SubTexture2D::CreateFromTexCoords(Texture2D* texture, const glm::vec2& coords, const glm::vec2& spriteSize)
{
	glm::vec2 min = { (coords.x * spriteSize.x) / texture->GetWidth(), (coords.y * spriteSize.y) / texture->GetHeight() };
	glm::vec2 max = { ((coords.x + 1) * spriteSize.x) / texture->GetWidth(), ((coords.y + 1) * spriteSize.y) / texture->GetHeight() };
	
	SubTexture2D subTexture(texture, min, max);
	return subTexture;
}

SubTexture2D::~SubTexture2D()
{
}

void SubTexture2D::ProcessTexCoords(Texture2D* texture, const glm::vec2& min, const glm::vec2& max)
{
	_texture = texture;

	_texCoords[0] = { min.x, min.y };
	_texCoords[1] = { max.x, min.y };
	_texCoords[2] = { max.x, max.y };
	_texCoords[3] = { min.x, max.y };
}
