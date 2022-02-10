#include "Physics.h"

bool Physics::Intersects(BoxColliderComponent* b1, BoxColliderComponent* b2)
{

}

bool Physics::Intersects(BoxColliderComponent* b1, CircleCollider* c1)
{

}

bool Physics::Intersects(BoxColliderComponent* b1, glm::vec2 p)
{

}

bool Physics::Intersects(CircleCollider* c1, CircleCollider* c2)
{

}

bool Physics::Intersects(CircleCollider* c1, glm::vec2 p)
{

}

void Physics::HandleCollision(Transform* t1, Transform* t2)
{

}


//Handlers for different orders of paramaters, just helps with usability
bool Physics::Intersects(CircleCollider* c1, BoxColliderComponent* b1)
{
	Intersects(b1, c1);
}
bool Physics::Intersects(glm::vec2 p, BoxColliderComponent* b1)
{
	Intersects(b1, p);
}
bool Physics::Intersects(glm::vec2 p, CircleCollider* c1)
{
	Intersects(c1, p);
}


