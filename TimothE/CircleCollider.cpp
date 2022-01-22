#include "CircleCollider.h"

CircleCollider::CircleCollider(GameObject* parent) : Component(parent), _radius(NULL), _centre(NULL), _isTrigger(NULL)
{
	SetType(Component::Boxcollision_Type);
	SetCategory(Component::Collisions_Category);

	_centre = Parent()->GetTransform()->GetPosition();
	_radius = parent->GetTransform()->GetScale().x / 2;
	bounds = new Rect((_centre.x - _radius), (_centre.x + _radius),
		(_centre.y - _radius), (_centre.y + _radius));
	std::cout << "BoxCollider Component has been added - centre " << _centre.x << ", " << _centre.y << std::endl;
	std::cout << "BoxCollider Component has been added - radius " << _radius;
}

CircleCollider::~CircleCollider()
{

}

void CircleCollider::OnStart()
{

}

void CircleCollider::OnUpdate()
{
	//if (Input::IsMouseButtonDown(BUTTON_1))
	//{
	//	int mouseX = Input::GetMouseX();
	//	int mouseY = Input::GetMouseY();
	//	//x < 624, x > 656, y > 344, y < 376
	//	if (bounds->btmLeft + bounds->btmRight) << 2)// + (bounds->topRight - bounds->topLeft) << 2) <= (mouseX + mouseY) << 2)
	//	{
	//		std::cout << "Mouse clicked inside the button! " << std::endl;
	//	}

	//	//std::cout << "Mouse clicked X: " << mouseX << " Y: " << mouseY << std::endl;
	//}
}

void CircleCollider::OnEnd()
{

}

void CircleCollider::DrawEditorUI()
{

}
