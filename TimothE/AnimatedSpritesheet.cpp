#include "AnimatedSpritesheet.h"
#include "Time.h"

AnimatedSpritesheet::AnimatedSpritesheet(Texture2D* texture, int spriteWidth, int spriteHeight, bool playAll)
	: SpriteSheet(texture, spriteWidth, spriteHeight), _rows(_sheetHeightInPixels / _spriteHeight)
{
	_spritesPerRow = _numOfSprites / _rows;
}

void AnimatedSpritesheet::SetFramerate(int framerate)
{
	_framerate = framerate;
	
	if (_runThroughAll) {
		_timeOnEachSprite = 1.0f / (_framerate);
	}
	else
	{
		_timeOnEachSprite = 1.0f / (_framerate);
	}
}

void AnimatedSpritesheet::Update()
{
	_timer += Time::GetDeltaTime();

	if (_timer > _timeOnEachSprite) {
		_timer = 0.0f;

		if (_runThroughAll) {
			_currentIndex = (_currentIndex + 1) % _numOfSprites;
		} else {
			_currentIndex = (_currentIndex + 1) % _spritesPerRow;
		}

		_currentIndex += (_currentRow * _spritesPerRow);

		std::cout << "Current Index: " << _currentIndex << std::endl;
	}

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
