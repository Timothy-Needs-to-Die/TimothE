#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(Texture2D* texture, int spriteWidth, int spriteHeight)
	: _pTexture(texture), _spriteWidth(spriteWidth), _spriteHeight(spriteHeight)
{
	_sheetWidthInPixels = texture->GetWidth();
	_sheetHeightInPixels = texture->GetHeight();

	_sheetWidth = _sheetWidthInPixels / _spriteWidth;
	_sheetHeight = _sheetHeightInPixels / _spriteHeight;

	_spriteHeight = _sheetHeightInPixels / _sheetHeight;
	_spriteWidth = _sheetWidthInPixels / _sheetWidth;

	_numOfSprites = _sheetWidth * _sheetHeight;

	_sprites.resize(_numOfSprites);

	for (int y = 0; y < _sheetHeight; y++) {
		for (int x = 0; x < _sheetWidth; x++) {
			glm::vec2* uvCoords = new glm::vec2[4];
			uvCoords[0].x = (x * (float)_spriteWidth) / (float)_sheetWidthInPixels;
			uvCoords[0].y = (y * (float)_spriteHeight) / (float)_sheetHeightInPixels;

			uvCoords[1].x = ((x + 1) * (float)_spriteWidth) / (float)_sheetWidthInPixels;
			uvCoords[1].y = (y * (float)_spriteHeight) / (float)_sheetHeightInPixels;

			uvCoords[2].x = ((x + 1) * (float)_spriteWidth) / (float)_sheetWidthInPixels;
			uvCoords[2].y = ((y + 1)* (float)_spriteHeight) / (float)_sheetHeightInPixels;

			uvCoords[3].x = (x * (float)_spriteWidth) / (float)_sheetWidthInPixels;
			uvCoords[3].y = ((y + 1) * (float)_spriteHeight) / (float)_sheetHeightInPixels;

			Sprite* sprite = new Sprite(_pTexture, uvCoords);
			_sprites[_sheetWidth * y + x] = sprite;
		}
	}
}
