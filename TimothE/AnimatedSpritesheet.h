#pragma once
#include "SpriteSheet.h"
class AnimatedSpritesheet : public SpriteSheet
{
public:
	AnimatedSpritesheet(Texture2D* texture, int spriteWidth, int spriteHeight);

	int GetFramerate() const { return _framerate; }
	void SetFramerate(int framerate) { _framerate = framerate; }

	glm::vec2* GetNextTexCoords(int row, int currentIndex);
	Sprite* GetNextSprite(int currentIndex);
private:
	int _framerate;
};

