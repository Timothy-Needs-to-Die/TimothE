#include "AnimatedSpritesheet.h"

AnimatedSpritesheet::AnimatedSpritesheet(Texture2D* texture, int spriteWidth, int spriteHeight)
	: SpriteSheet(texture, spriteWidth, spriteHeight)
{

}

glm::vec2* AnimatedSpritesheet::GetNextTexCoords(int row, int currentIndex)
{
	if (row > _sheetHeight)
	{
		std::cout << "[Error AnimatedSpriteSheet::GetNextAnimation]: Row was greater than amount of rows." << std::endl;
		return nullptr;
	}

	if (currentIndex == _sheetWidth) {
		currentIndex = 0;
	}

	int index = _sheetWidth * row + currentIndex;

	return _sprites[index]->GetTexCoords();
}

Sprite* AnimatedSpritesheet::GetNextSprite(int currentIndex)
{
	if (currentIndex == _numOfSprites) {
		currentIndex == 0;
	}

	return GetSpriteAtIndex(currentIndex);
}
