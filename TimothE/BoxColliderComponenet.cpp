#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "imgui.h"
#include "Input.h"
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

		if (pow((_centre.x - mouseX), 2) + pow((_centre.y - mouseY), 2) < pow((_radius * 2), 2))
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
	ImGui::Checkbox("IsTrigger", &_isTrigger);

	if (IsTrigger())
	{
		std::cout << "I AM A TRIGGER" << std::endl;
	}
	else
	{
		std::cout << "I AM NOT A TRIGGER" << std::endl;
	}
}
BoxColliderComponent::BoxColliderComponent(GameObject* parent) : CircleColliderComponent(parent), _size({ 32,32 }), _bounds(NULL)
{
	SetType(Component::Boxcollision_Type);
	SetCategory(Component::Collisions_Category);
	_centre = Parent()->GetTransform()->GetPosition();
	_bounds = new Rect((_centre.x - (_size.x)), (_centre.x + (_size.y)), 
		(_centre.y - (_size.y)), (_centre.y + (_size.y)));
	std::cout << "BoxCollider Component has been added - centre " << _centre.x << ", " << _centre.y << std::endl;
	std::cout << "Bounds are -  bottomLeft: " << _bounds->btmLeft << "  BottomRight: " << _bounds->btmRight << "  TopLeft: " << _bounds->topLeft << "  TopRight: " << _bounds->topRight << std::endl;
}

BoxColliderComponent::~BoxColliderComponent()
{

}

void BoxColliderComponent::OnStart()
{

}

void BoxColliderComponent::OnUpdate()
{
	//std::cout << "TomthE";
	if (Input::IsMouseButtonDown(BUTTON_1))
	{
		int mouseX = Input::GetMouseX();
		int mouseY = Input::GetMouseY();

		//x < 624, x > 656, y > 344, y < 376
		if (mouseX > _bounds->btmLeft && mouseX < _bounds->btmRight
			&& mouseY > _bounds->topLeft && mouseY < _bounds->topRight)
		{
			std::cout << "Mouse clicked inside the button! " << std::endl;
		}

		//std::cout << "Mouse clicked X: " << mouseX << " Y: " << mouseY << std::endl;
	}
}

void BoxColliderComponent::OnEnd()
{

}

void BoxColliderComponent::DrawEditorUI()
{
	CircleColliderComponent::DrawEditorUI();
}