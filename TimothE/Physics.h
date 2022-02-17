#pragma once
#include "pch.h"

#include "BoxColliderComponent.h"
#include "CircleCollider.h"
#include "Transform.h"

struct CollisionData {
	glm::vec2 collisionNormal;
	float penetration;
};

struct ColQuad {
	glm::vec2 pos;
	glm::vec2 size;
};

class Physics
{
public:
	static bool Intersects(ColQuad& a, ColQuad& b);
	static bool Intersects(BoxColliderComponent* b1, BoxColliderComponent* b2);
	static bool Intersects(BoxColliderComponent* b1, CircleCollider* c1);
	static bool Intersects(CircleCollider* c1, BoxColliderComponent* b1);
	static bool Intersects(BoxColliderComponent* b1, glm::vec2 p);
	static bool Intersects(glm::vec2 p, BoxColliderComponent* b1);
	static bool Intersects(CircleCollider* c1, CircleCollider* c2);
	static bool Intersects(CircleCollider* c1, glm::vec2 p);
	static bool Intersects(glm::vec2 p, CircleCollider* c1);

private:
	static void HandleCollision(ColliderBase* c1, ColliderBase* c2);



};

