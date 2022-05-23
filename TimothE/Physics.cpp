#include "Physics.h"

void Physics::SetupScenePhysics()
{
	std::vector<ColliderBase*> colliders = Scene::FindObjectsOfType<ColliderBase>();
	std::cout << "No. Of Colliders: " << colliders.size() << std::endl;

	if (colliders.size() == 1) return;
}

bool Physics::Intersects(BoxColliderComponent* b1, BoxColliderComponent* b2)
{
	Rect* r1 = b1->GetCollisionRect();
	Rect* r2 = b2->GetCollisionRect();

	glm::vec2 n = { r1->xPos - r2->xPos, r1->yPos - r2->yPos };

	float r1Extents = r1->width / 2;
	float r2Extents = r2->width / 2;
	float xOverlap = r1Extents + r2Extents - abs(n.x);

	if ((r1->xPos < r2->xPos + r2->width) &&
		(r1->xPos + r1->width > r2->xPos) &&
		(r1->yPos < r2->yPos + r2->height) &&
		(r1->yPos + r1->height > r2->yPos)) 
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

bool Physics::Intersects(BoxColliderComponent* b1, glm::vec2 p)
{
	Rect* r1 = b1->GetCollisionRect();
	if (p.x > r1->xPos && p.x < r1->xPos + r1->width && p.y > r1->yPos && p.y < r1->yPos + r1->height) {
		
		return true;
	}
	return false;
}

bool Physics::Intersects(ColQuad& a, ColQuad& b)
{
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



bool Physics::Intersects(glm::vec2 p, BoxColliderComponent* b1)
{
	return Intersects(b1, p);
}

