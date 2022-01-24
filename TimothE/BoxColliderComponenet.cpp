#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "imgui.h"
#include "Input.h"

BoxColliderComponent::BoxColliderComponent(GameObject* parent) : Component(parent), _size({ 32, 32 }), _isTrigger(NULL)
{
	SetType(Component::Boxcollision_Type);
	SetCategory(Component::Collisions_Category);
	_centre = Parent()->GetTransform()->GetPosition();
	bounds = new Rect((_centre.x - (_size.x)), (_centre.x + (_size.y)), 
		(_centre.y - (_size.y)), (_centre.y + (_size.y)));
	std::cout << "BoxCollider Component has been added - centre " << _centre.x << ", " << _centre.y << std::endl;
	std::cout << "Bounds are -  bottomLeft: " << bounds->btmLeft << "  BottomRight: " << bounds->btmRight << "  TopLeft: " << bounds->topLeft << "  TopRight: " << bounds->topRight << std::endl;
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
		if (mouseX > bounds->btmLeft && mouseX < bounds->btmRight
			&& mouseY > bounds->topLeft && mouseY < bounds->topRight)
		{
			std::cout << "Mouse clicked inside the button! " << std::endl;
		}

		//std::cout << "Mouse clicked X: " << mouseX << " Y: " << mouseY << std::endl;
	}
}

void BoxColliderComponent::OnEnd()
{

}

bool BoxColliderComponent::CollideDetect(glm::vec2 objectPos)
{
	if (objectPos.x > bounds->btmLeft && objectPos.x < bounds->btmRight
		&& objectPos.y > bounds->topLeft && objectPos.y < bounds->topRight)
	{
		return true;
	}
	return false;
}

void BoxColliderComponent::DrawEditorUI()
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