#pragma once
#include "pch.h"
#include "Texture2D.h"
#include "Sprite.h"

class SpriteSheet
{
public:
	SpriteSheet(Texture2D* texture, int spriteWidth, int spriteHeight, std::string resourceName);

	//Returns the total number of sprites in the sprite sheet
	int GetNumberOfSprites() const { return _numOfSprites; }

	//Returns the width of the sprite sheet in pixels e.g. 2560
	int GetPixelWidth() const { return _sheetWidthInPixels; }

	//Returns the height of the sprite sheet in pixels e.g. 1664
	int GetPixelHeight() const { return _sheetHeightInPixels; }

	//Returns the width of the sheet in sprites e.g. 20 sprites wide
	int GetSheetWidth() const { return _sheetWidth; }

	//Returns the height of the sheet in sprites e.g. 13 sprites tall
	int GetSheetHeight() const { return _sheetHeight; }

	//Returns the pixel width of each sprite e.g. 128
	int GetSpriteWidth() const { return _spriteWidth; }

	//Returns the pixel height of each sprite e.g. 128
	int GetSpriteHeight() const { return _spriteHeight; }

	//Returns the texture associated with this spritesheet
	Texture2D* GetTexture() const { return _pTexture; }

	//Returns the sprite at a specified index.
	Sprite* GetSpriteAtIndex(int index);

	//Returns the sprite at a specified position on the sheet.
	Sprite* GetSpriteAtPosition(int x, int y) { return _sprites[y * _spriteWidth + x]; }

	std::string GetResourceName() const { return _resourceName; }

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

	//Name of the sprite sheet in the resource manager
	std::string _name;

	std::string _resourceName;
};

