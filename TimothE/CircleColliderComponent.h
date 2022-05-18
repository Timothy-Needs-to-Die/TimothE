#pragma once
#include "ColliderBase.h"
class CircleColliderComponent : public ColliderBase
{
public:
	CircleColliderComponent(GameObject* owner);


	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	float GetRadius() const { return _radius; }
	glm::vec2 GetPosition() const { return _position; }

private:
	float _radius;
	
	glm::vec2 _position;

};

