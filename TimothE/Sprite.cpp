#include "Sprite.h"

Sprite::Sprite(Texture2D* texture, glm::vec2* pTexCoords /*= nullptr*/)
	: _pTexture(texture)
{
	if (pTexCoords == nullptr) {
		_pTexCoords = new glm::vec2[4];

		_pTexCoords[0] = glm::vec2(0.0f, 0.0f);
		_pTexCoords[1] = glm::vec2(1.0f, 0.0f);
		_pTexCoords[2] = glm::vec2(1.0f, 1.0f);
		_pTexCoords[3] = glm::vec2(0.0f, 1.0f);
	}
	else {
		_pTexCoords = pTexCoords;
	}

}

Sprite::~Sprite()
{
	delete _pTexCoords;
	_pTexCoords = nullptr;
}
