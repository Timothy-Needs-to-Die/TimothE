#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "imgui.h"
#include "Input.h"

BoxColliderComponent::BoxColliderComponent(GameObject* parent) : ColliderBase(parent)
{
	SetType(Component::Boxcollision_Type);
	SetCategory(Component::Collisions_Category);

	// Set the boxcollider to be enabled by default
	_isEnabled = true;

	// Transform.GetPosition() returns the center of an object
	glm::vec2 objectCenterPoint = GetParent()->GetTransform()->GetPosition();
	glm::vec2 objectScale = GetParent()->GetTransform()->GetScale();
	
	
	// Create a box around the "object"  ERROR: current *2 because transform doesnt return the true scale???
	_boxCollider = new Rect(
		objectCenterPoint.x - objectScale.x,	// xPos
		objectCenterPoint.y - objectScale.y,	// yPos
		objectScale.x * 2,						// Width
		objectScale.y * 2);						// Height
	
	// Editor UI Vars
	_editorIsEnabled = &_isEnabled;
}

BoxColliderComponent::~BoxColliderComponent()
{
	delete _boxCollider;
}

void BoxColliderComponent::OnStart()
{

}

void BoxColliderComponent::OnUpdate()
{
	if (Component::IsEnabled())
	{
		// Update our center and size from the transform incase its moved.
		glm::vec2 position = _pParentObject->GetTransform()->GetPosition();
		glm::vec2 scale = _pParentObject->GetTransform()->GetScale();

		// Update our collider to the correct position
		_boxCollider->xPos = position.x;
		_boxCollider->yPos = position.y;
		_boxCollider->width = scale.x;
		_boxCollider->height = scale.y;

		// debug	
		//float mouseX = Input::GetMouseX();
		//float mouseY = Input::GetMouseY();
		//std::cout << IsPointInside({mouseX, mouseY}) << std::endl;
	}
}

void BoxColliderComponent::OnEnd()
{

}

bool BoxColliderComponent::Intersects(Rect* box)
{
	if (Component::IsEnabled())
	{
		if ((_boxCollider->xPos + _boxCollider->width >= box->xPos)
			&& (box->xPos + _boxCollider->width >= _boxCollider->xPos)
			&& (_boxCollider->yPos + _boxCollider->height >= box->yPos)
			&& (box->yPos + _boxCollider->height >= _boxCollider->yPos))
		{
			return true;
		}
	}
	return false;
}

bool BoxColliderComponent::IsPointInside(glm::vec2 point)
{
	if (Component::IsEnabled())
	{
		if (point.x > _boxCollider->xPos && point.x < _boxCollider->xPos + _boxCollider->width
			&& point.y > _boxCollider->yPos && point.y < _boxCollider->yPos + _boxCollider->height)
		{
			return true;
		}
	}
	return false;
}



void BoxColliderComponent::DrawEditorUI()
{
	if (ImGui::CollapsingHeader("Box Collider Component"))
	{
		Component::DrawEditorUI();
	}
}