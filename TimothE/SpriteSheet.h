#pragma once
#include "pch.h"
#include "Texture2D.h"
#include "Sprite.h"

class SpriteSheet
{
public:
	SpriteSheet(Texture2D* texture, int spriteWidth, int spriteHeight);


	int GetNumberOfSprites() const { return _numOfSprites; }
	int GetPixelWidth() const { return _sheetWidthInPixels; }
	int GetPixelHeight() const { return _sheetHeightInPixels; }
	int GetSheetWidth() const { return _sheetWidth; }
	int GetSheetHeight() const { return _sheetHeight; }
	int GetSpriteWidth() const { return _spriteWidth; }
	int GetSpriteHeight() const { return _spriteHeight; }

	Texture2D* GetTexture() const { return _pTexture; }

	Sprite* GetSpriteAtIndex(int index) { return _sprites[index]; }
protected:
	//Number of sprites on the spritesheet
	int _numOfSprites;

	//Width of sprite sheet in pixels
	int _sheetWidthInPixels;

	//Height of sprite sheet in pixels
	int _sheetHeightInPixels;

	//How many sprites per row
	int _sheetWidth;
	//How many sprites per column
	int _sheetHeight;

	//Width of each sprite in pixels
	int _spriteWidth;

	//Height of each sprite in pixels
	int _spriteHeight;

	//All the sprites associated with this sheet
	std::vector<Sprite*> _sprites;

	//The loaded texture for this sheet
	Texture2D* _pTexture;
};

