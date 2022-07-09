#pragma once
#include "UIObject.h"
#include "Core/Graphics/VAO.h"
#include "Sprite.h"
#include "Core/Graphics/Shader.h"

class ImageUIObject : public UIObject
{
public:
	ImageUIObject(Sprite* sprite, std::string name, glm::vec2 designPos = glm::vec2{ 0.0f }, glm::vec2 designSize = glm::vec2{ 100.0f });
	~ImageUIObject();

	virtual void Draw() override;
	virtual void Update() override;

private:
	Sprite* _pSprite;
	Shader* _pShader;

	std::shared_ptr<VAO> _pVao;


};

