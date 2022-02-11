#include "Physics.h"

bool Physics::Intersects(BoxColliderComponent* b1, BoxColliderComponent* b2)
{
	Rect* r1 = b1->GetCollisionRect();
	Rect* r2 = b2->GetCollisionRect();

	glm::vec2 n = { r1->xPos - r2->xPos, r1->yPos - r2->yPos };

	float r1Extents = r1->width / 2;
	float r2Extents = r2->width / 2;
	float xOverlap = r1Extents + r2Extents - abs(n.x);

	if ((r1->xPos + r1->width >= r2->xPos) &&
		(r2->xPos + r1->width >= r1->xPos) &&
		(r1->yPos + r1->height >= r2->yPos) &&
		(r2->yPos + r1->height >= r1->yPos)) 
	{
		if (!b1->IsTrigger() && !b2->IsTrigger()) {
			CollisionData col;

			r1Extents = r1->height / 2;
			r2Extents = r2->height / 2;
			float yOverlap = r1Extents + r2Extents - abs(n.y);

			if (yOverlap > 0) {
				if (n.x < 0) {
					col.collisionNormal = { -1.0f,0.0f };
				}
				else {
					col.collisionNormal = { 0.0f,0.0f };
				}
				col.penetration = xOverlap;
			}
			else
			{
				if (n.y < 0) {
					col.collisionNormal = { 0.0f,-1.0f };
				}
				else
				{
					col.collisionNormal = { 0.0f,1.0f };
				}
				col.penetration = yOverlap;
			}

			HandleCollision(b1, b2);
		}
		else {
			if (b1->IsTrigger()) {
				b1->Triggered();
			}
			if (b2->IsTrigger()) {
				b2->Triggered();
			}
		}

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

		if (!b1->IsTrigger() && !c1->IsTrigger()) {
			//HandleCollision(b1, c1);
		}
		else {
			if (b1->IsTrigger()) {
				b1->Triggered();
			}
			if (c1->IsTrigger()) {
				c1->Triggered();
			}
		}
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
		if (!c2->IsTrigger() && !c1->IsTrigger()) {
			//HandleCollision(c2, c1);
		}
		else {
			if (c2->IsTrigger()) {
				c2->Triggered();
			}
			if (c1->IsTrigger()) {
				c1->Triggered();
			}
		}
		return true;
	}
	return false;
}

bool Physics::Intersects(CircleCollider* c1, glm::vec2 p)
{
	glm::vec2 cp = c1->GetPosition();

	float distX = p.x - cp.x;
	float distY = p.y - cp.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance < c1->GetColliderSize()) {
		return true;
	}
	return false;
}

bool Physics::Intersects(ColQuad& a, ColQuad& b)
{
	//(player1.x < player2.x + player2.width &&
	//	player1.x + player1.width > player2.x &&
	//	player1.y < player2.y + player2.height &&
	//	player1.y + player1.height > player2.y)

	//std::cout << "Intersect" << std::endl;

	if ((a.pos.x < b.pos.x + b.size.x) &&
		(a.pos.x + a.size.x > b.pos.x) &&
		(a.pos.y < b.pos.y + b.size.y) &&
		(a.pos.y + a.size.y > b.pos.y))
	{
		return true;
	}
	return false;
}

void Physics::HandleCollision(ColliderBase* c1, ColliderBase* c2)
{
	c1->Collided();
	c2->Collided();
}


//Handlers for different orders of paramaters, just helps with usability
bool Physics::Intersects(CircleCollider* c1, BoxColliderComponent* b1)
{
	return Intersects(b1, c1);
}
bool Physics::Intersects(glm::vec2 p, BoxColliderComponent* b1)
{
	return Intersects(b1, p);
}
bool Physics::Intersects(glm::vec2 p, CircleCollider* c1)
{
	return Intersects(c1, p);
}
