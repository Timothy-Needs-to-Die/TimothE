#pragma once
#include "SpriteSheet.h"
#include "Time.h"

struct Animation {
	std::vector<int> _animationIDs;

	int _currentIndex = 0;
	
	std::string _name = "WALK_LEFT";

	int _framesInAnimation;

	float _duration = 1.0f;
	float _timer = 0.0f;

	int GetCurrentID() {
		return _animationIDs[_currentIndex];
	}

	int GetCurrentIndex() {
		return _currentIndex;
	}

	void AddAnimationID(int index) {
		_animationIDs.emplace_back(index);
		_framesInAnimation++;
		_duration = 1.0f / _framesInAnimation;
	}

	void Update() {
		_timer += Time::GetDeltaTime();

		if (_timer > _duration) {
			_timer = 0.0f;

			_currentIndex = (_currentIndex + 1) % _framesInAnimation;
		}
	}

	void SetIndex(int newIndex) {
		_currentIndex = newIndex;
	}

	void EndAnimation() {
		_currentIndex = 0;
		_timer = 0.0f;
	}
};


class AnimatedSpritesheet : public SpriteSheet
{
public:
	AnimatedSpritesheet(Texture2D* texture, int spriteWidth, int spriteHeight, bool playAll = false);

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

	Animation* GetAnimationByName(std::string& name) {
		return _animations[name];
	}

	void AddAnimation(std::string name, Animation* pAnimation) {
		_animations[name] = pAnimation;
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

	std::unordered_map<std::string, Animation*> _animations;
};

