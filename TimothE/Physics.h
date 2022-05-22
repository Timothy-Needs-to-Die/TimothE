#pragma once
#include "pch.h"

#include "BoxColliderComponent.h"
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
	static void SetupScenePhysics();
	static bool Intersects(ColQuad& a, ColQuad& b);
	static bool Intersects(BoxColliderComponent* b1, BoxColliderComponent* b2);
	static bool Intersects(BoxColliderComponent* b1, glm::vec2 p);
	static bool Intersects(glm::vec2 p, BoxColliderComponent* b1);

private:
	static void HandleCollision(ColliderBase* c1, ColliderBase* c2);



};

