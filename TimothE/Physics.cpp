#include "Physics.h"

bool Physics::Intersects(BoxColliderComponent* b1, BoxColliderComponent* b2)
{
	Rect* r1 = b1->GetCollisionRect();
	Rect* r2 = b2->GetCollisionRect();

	if ((r1->xPos + r1->width >= r2->xPos) &&
		(r2->xPos + r1->width >= r1->xPos) &&
		(r1->yPos + r1->height >= r2->yPos) &&
		(r2->yPos + r1->height >= r1->yPos)) 
	{
		HandleCollision(b1->GetParent()->GetTransform(), b2->GetParent()->GetTransform());
		return true;
	}
	return false;
}

bool Physics::Intersects(BoxColliderComponent* b1, CircleCollider* c1)
{
	Rect* r1 = b1->GetCollisionRect();

	glm::vec2 cp = c1->GetPosition();
	float cr = c1->GetColliderSize();

	float testX = cp.x;
	float testY = cp.y;

	if (cp.x < r1->xPos) testX = r1->xPos;
	else if (cp.x > r1->xPos + r1->width) testX = r1->xPos + r1->width;

	if (cp.y < r1->yPos) testY = r1->yPos;
	else if (cp.y > r1->yPos + r1->height) testY = r1->yPos + r1->height;

	float distX = cp.x - testX;
	float distY = cp.y - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= cr) {
		HandleCollision(b1->GetParent()->GetTransform(), c1->GetParent()->GetTransform());
		return true;
	}

	return false;
	
}

bool Physics::Intersects(BoxColliderComponent* b1, glm::vec2 p)
{
	Rect* r1 = b1->GetCollisionRect();
	if (p.x > r1->xPos && p.x < r1->xPos + r1->width && p.y > r1->yPos && p.y < r1->yPos + r1->height) {
		
		return true;
	}
	return false;
}

bool Physics::Intersects(CircleCollider* c1, CircleCollider* c2)
{
	glm::vec2 c1p = c1->GetPosition();
	float c1r = c1->GetColliderSize();

	glm::vec2 c2p = c2->GetPosition();
	float c2r = c2->GetColliderSize();

	float distX = c1p.x - c2p.x;
	float distY = c1p.y - c1p.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= c1r + c2r) {
		HandleCollision(c1->GetParent()->GetTransform(), c2->GetParent()->GetTransform());
		return true;
	}
	return false;
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


