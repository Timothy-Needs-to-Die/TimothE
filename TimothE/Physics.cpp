#include "pch.h"
#include "Physics.h"

std::vector<ColliderBase*> Physics::_pColliders = std::vector<ColliderBase*>();
std::vector<ColliderBase*> Physics::_pCollidersToRemove = std::vector<ColliderBase*>();
std::vector<std::pair<ColliderBase*, ColliderBase*>> Physics::_collidingBodies = std::vector<std::pair<ColliderBase*, ColliderBase*>>();

void Physics::AddCollider(ColliderBase* collider)
{
	_pColliders.emplace_back(collider);
	//TIM_LOG_LOG("ADDING COLLIDER: No of Colliders in scene: " << _pColliders.size());
}

void Physics::RemoveCollider(ColliderBase* collider)
{
	if (collider == nullptr) return; 

	std::vector<ColliderBase*>::const_iterator it = std::find(_pCollidersToRemove.begin(), _pCollidersToRemove.end(), collider);

	if (it == _pCollidersToRemove.end()) {
		_pCollidersToRemove.emplace_back(collider);
	}

	//TIM_LOG_LOG("REMOVING COLLIDER: No of Colliders in scene: " << _pColliders.size());
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
				col.collisionNormal = n.x < 0 ? glm::vec2(-1.0f, 0.0f) : glm::vec2(1.0f, 0.0f);
				col.penetration = xOverlap;
			}
			else
			{
				col.collisionNormal = n.y < 0 ? glm::vec2{0.0f, -1.0f} : glm::vec2{0.0f, 1.0f};
				col.penetration = yOverlap;
			}
		}
		else {
			HandleCollision(b1, b2);
		}

		return true;
	}
	HandleNoCollision(b1, b2);
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
		HandleCollision(c1, c2);

		return true;
	}

	HandleNoCollision(c1, c2);
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
		HandleCollision(c1, b1);

		return true;
	}
	
	HandleNoCollision(c1, b1);
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

bool Physics::Intersects(glm::vec2 p, BoxColliderComponent* b1)
{
	return Intersects(b1, p);
}

void Physics::HandleCollision(ColliderBase* c1, ColliderBase* c2 /*= nullptr*/)
{
	std::vector<std::pair<ColliderBase*, ColliderBase*>>::iterator it = std::find(_collidingBodies.begin(), _collidingBodies.end(), std::make_pair(c1, c2));
	if (it == _collidingBodies.end()) {
		_collidingBodies.emplace_back(std::make_pair(c1, c2));

		if (c1->IsTrigger()) {
			if (c1->GetParent() != nullptr && c2->GetParent() != nullptr) {
				c1->GetParent()->OnTriggerEnter(c2);
			}
		}
		if (c2->IsTrigger()) {
			if (c2->GetParent() != nullptr && c1->GetParent() != nullptr) {
				c2->GetParent()->OnTriggerEnter(c1);
			}
		}
	}
}

void Physics::HandleNoCollision(ColliderBase* c1, ColliderBase* c2)
{
	std::vector<std::pair<ColliderBase*, ColliderBase*>>::iterator it = std::find(_collidingBodies.begin(), _collidingBodies.end(), std::make_pair(c1, c2));
	if (it != _collidingBodies.end()) {
		if (c1->GetParent() != nullptr && c1->IsTrigger()) {
			if (c2->GetParent() != nullptr) {
				c1->GetParent()->OnTriggerExit(c2);
			}
		}

		if (c2->GetParent() != nullptr && c2->IsTrigger()) {
			if (c1->GetParent() != nullptr) {
				c2->GetParent()->OnTriggerExit(c1);
			}
		}

		_collidingBodies.erase(it);
	}
}

void Physics::UpdateWorld()
{
	constexpr float MAX_DISTANCE = 8.0f;



	for (int i = 0; i < _pColliders.size(); ++i) {
		ColliderBase* pColA = _pColliders[i];
		ColliderType aType = pColA->GetColliderType();
		CollisionChannel colAChannel = pColA->GetCollisionChannel();


		if (colAChannel == CollisionChannel_None) continue;

		glm::vec2 colAPos = pColA->GetParent()->GetTransform()->GetPosition();

		for (int j = i; j < _pColliders.size(); ++j) {
			if (j == i) continue;


			ColliderBase* pColB = _pColliders[j];
			CollisionChannel colBChannel = pColB->GetCollisionChannel();

			if(colBChannel == CollisionChannel_None) continue;

			if (glm::distance(colAPos, pColB->GetParent()->GetTransform()->GetPosition()) > MAX_DISTANCE) continue;

			if (pColA->IsColliderCompatible(colBChannel) || pColB->IsColliderCompatible(colAChannel)) {
				ColliderType bType = pColB->GetColliderType();
				if (aType == ColliderType::Circle && bType == ColliderType::Circle) {
					Intersects((CircleColliderComponent*)pColA, (CircleColliderComponent*)pColB);
				}
				else if (aType == ColliderType::Box && bType == ColliderType::Box) {
					Intersects((BoxColliderComponent*)pColA, (BoxColliderComponent*)pColB);
				}
				else if (aType == ColliderType::Box && bType == ColliderType::Circle) {
					Intersects((CircleColliderComponent*)pColB, (BoxColliderComponent*)pColA);
				}
				else if (aType == ColliderType::Circle && bType == ColliderType::Box) {
					Intersects((CircleColliderComponent*)pColA, (BoxColliderComponent*)pColB);
				}
			}
		}
	}


}

void Physics::EndFrame()
{
	if (_pCollidersToRemove.empty()) return;

	for (std::vector<ColliderBase*>::iterator it = _pCollidersToRemove.begin(); it != _pCollidersToRemove.end(); ++it) {
		std::vector<ColliderBase*>::iterator it2 = std::find(_pColliders.begin(), _pColliders.end(), *it);

		if (it2 != _pColliders.end()) {
			_pColliders.erase(it2);
		}
		
		//TIM_LOG_LOG("No of Colliders in scene: " << _pColliders.size());
	}

	_pCollidersToRemove.clear();
}

