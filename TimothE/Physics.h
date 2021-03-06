#pragma once
#include "pch.h"

#include "BoxColliderComponent.h"
#include "CircleColliderComponent.h"
#include "Transform.h"
#include "Scene.h"

struct CollisionData {
	glm::vec2 collisionNormal;
	float penetration;
};

struct ColQuad {
	glm::vec2 pos;
	glm::vec2 max;
	glm::vec2 size;

	void CalculateMax() {
		max = pos + size;
	}
};

class Physics
{
public:
	static void AddCollider(ColliderBase* collider);
	static void RemoveCollider(ColliderBase* collider);

	static bool Intersects(ColQuad& a, ColQuad& b);
	static bool Intersects(BoxColliderComponent* b1, BoxColliderComponent* b2);
	static bool Intersects(BoxColliderComponent* b1, glm::vec2 p);

	static bool Intersects(CircleColliderComponent* c1, CircleColliderComponent* c2);
	static bool Intersects(CircleColliderComponent* c1, BoxColliderComponent* b1);
	static bool Intersects(CircleColliderComponent* c1, glm::vec2 point);

	static bool Intersects(glm::vec2 p, BoxColliderComponent* b1);

	static void HandleCollision(ColliderBase* c1, ColliderBase* c2);
	static void HandleNoCollision(ColliderBase* c1, ColliderBase* c2);

	static void UpdateWorld();
	static void EndFrame();

private:

	static std::vector<ColliderBase*> _pColliders;
	static std::vector<ColliderBase*> _pCollidersToRemove;
	static std::vector<std::pair<ColliderBase*, ColliderBase*>> _collidingBodies;
};

