#include "Physics.h"

std::vector<ColliderBase*> Physics::_pColliders = std::vector<ColliderBase*>();
std::vector<ColliderBase*> Physics::_pCollidersToRemove = std::vector<ColliderBase*>();

void Physics::AddCollider(ColliderBase* collider)
{
	_pColliders.emplace_back(collider);
	TIM_LOG_LOG("No of Colliders in scene: " << _pColliders.size());
}

void Physics::RemoveCollider(ColliderBase* collider)
{
	_pCollidersToRemove.emplace_back(collider);
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
				b1->GetParent()->OnTriggerEnter(b2);
			}
			if (b2->IsTrigger()) {
				b2->GetParent()->OnTriggerEnter(b1);
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

bool Physics::Intersects(CircleColliderComponent* c1, CircleColliderComponent* c2)
{
	float distance = glm::distance(c1->GetPosition(), c2->GetPosition());

	float resultingRadius = c1->GetRadius() + c2->GetRadius();

	if (distance < resultingRadius) {
		if (c1->IsTrigger()) {
			c1->GetParent()->OnTriggerEnter(c2);
		}
		if (c2->IsTrigger()) {
			c2->GetParent()->OnTriggerEnter(c1);
		}

		return true;
	}

	return false;
}

bool Physics::Intersects(CircleColliderComponent* c1, BoxColliderComponent* b1)
{
	glm::vec2 cPos = c1->GetPosition();
	glm::vec2 bPos = { b1->GetCollisionRect()->xPos, b1->GetCollisionRect()->yPos };
	glm::vec2 bSize = { b1->GetCollisionRect()->width, b1->GetCollisionRect()->height };

	float cX;
	if (cPos.x < bPos.x) {
		cX = bPos.x;
	}
	else if (cPos.x > bPos.x + bSize.x) {
		cX = bPos.x + bSize.x;
	}
	else {
		cX = bPos.x;
	}

	float cY;
	if (cPos.y < bPos.y) {
		cY = bPos.y;
	}
	else if (cPos.y > bPos.y + bSize.y) {
		cY = bPos.y + bSize.y;
	}
	else {
		cY = bPos.y;
	}

	float dX = cX - cPos.x;
	float dY = cY - cPos.y;
	float d = dX * dX + dY * dY;

	if (d < c1->GetRadius() * c1->GetRadius()) {
		if (c1->IsTrigger()) {
			c1->GetParent()->OnTriggerEnter(b1);
		}
		if (b1->IsTrigger()) {
			b1->GetParent()->OnTriggerEnter(c1);
		}

		return true;
	}
	
	return false;
}

bool Physics::Intersects(CircleColliderComponent* c1, glm::vec2 point)
{
	glm::vec2 cPos = c1->GetPosition();

	float distX = point.x - cPos.x;
	float distY = point.y - cPos.y;

	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance < c1->GetRadius()) {
		return true;
	}

	return false;
}

void Physics::HandleCollision(ColliderBase* c1, ColliderBase* c2)
{
}


bool Physics::Intersects(glm::vec2 p, BoxColliderComponent* b1)
{
	return Intersects(b1, p);
}

void Physics::UpdateWorld()
{
	for (int i = 0; i < _pColliders.size(); ++i) {
		ColliderBase* pColA = _pColliders[i];
		ColliderType aType = pColA->GetType();

		for (int j = i; j < _pColliders.size(); ++j) {
			if (j == i) continue;

			ColliderBase* pColB = _pColliders[j];
			ColliderType bType = pColB->GetType();

			if (aType == Circle && bType == Circle) {
				Intersects((CircleColliderComponent*)pColA, (CircleColliderComponent*)pColB);
			}
			else if (aType == Box && bType == Box) {
				Intersects((BoxColliderComponent*)pColA, (BoxColliderComponent*)pColB);
			}
			else if (aType == Box && bType == Circle) {
				Intersects((CircleColliderComponent*)pColB, (BoxColliderComponent*)pColA);
			}
			else if (aType == Circle && bType == Box) {
				Intersects((CircleColliderComponent*)pColA, (BoxColliderComponent*)pColB);
			}
		}
	}

	for (int i = 0; i < _pCollidersToRemove.size(); ++i) {
		_pColliders.erase(std::find(_pColliders.begin(), _pColliders.end(), _pCollidersToRemove[i]));
	}

	_pCollidersToRemove.clear();
}

