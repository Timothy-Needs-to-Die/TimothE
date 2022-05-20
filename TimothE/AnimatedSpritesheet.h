#pragma once
#include "SpriteSheet.h"
class AnimatedSpritesheet : public SpriteSheet
{
public:
	AnimatedSpritesheet(Texture2D* texture, int spriteWidth, int spriteHeight, std::string resourceName, bool playAll = false);

	int GetFramerate() const { return _framerate; }
	void SetFramerate(int framerate);

	int GetCurrentRow() const { return _currentRow; }
	void SetCurrentRow(int row) {
		_currentRow = row;
		_currentIndex = _currentRow * _spritesPerRow;
	}

	int GetCurrentIndex() const { return _currentIndex; }

	void SetStationary(bool isStationary) {
		_isStationary = isStationary;
	}

	void Update();

	glm::vec2* GetNextTexCoords(int row, int currentIndex);
	Sprite* GetNextSprite(int currentIndex);
private:
	int _framerate;
	bool _runThroughAll = false;

	bool _isStationary = false;

	int _rows;
	int _currentRow;

	int _currentIndex = 0;
	int _spritesPerRow = 0;

	float _timeOnEachSprite;
	float _timer;
};

