#include "CircleCollider.h"
#include <cmath>

CircleColliderComponent::CircleColliderComponent(GameObject* parent) : Component(parent), _radius(NULL), _centre(NULL), _isTrigger(NULL)
{
	SetType(Component::Boxcollision_Type);
	SetCategory(Component::Collisions_Category);

	_radius = parent->GetTransform()->GetScale().x / 2;
	std::cout << "BoxCollider Component has been added - centre " << _centre.x << ", " << _centre.y << std::endl;
	std::cout << "BoxCollider Component has been added - radius " << _radius;
}

CircleColliderComponent::~CircleColliderComponent()
{

}

void CircleColliderComponent::OnStart()
{

}

void CircleColliderComponent::OnUpdate()
{
	_centre = Parent()->GetTransform()->GetPosition();
	//std::cout << _centre.x << " " << _centre.y << std::endl;
	if (Input::IsMouseButtonDown(BUTTON_1))
	{
		int mouseX = Input::GetMouseX();
		int mouseY = Input::GetMouseY();

		if (pow((_centre.x - mouseX), 2) + pow((_centre.y - mouseY),2) < pow((_radius * 2),2))
		{
			std::cout << "Mouse clicked inside the circle! at pos " << mouseX << ", " << mouseY << std::endl;
		}

		//std::cout << "Mouse clicked X: " << mouseX << " Y: " << mouseY << std::endl;
	}
}

void CircleColliderComponent::OnEnd()
{

}

void CircleColliderComponent::DrawEditorUI()
{

}
