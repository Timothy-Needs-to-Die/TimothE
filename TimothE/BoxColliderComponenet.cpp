#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "imgui.h"
#include "Input.h"
#include "Physics.h"

BoxColliderComponent::BoxColliderComponent(GameObject* parent) : ColliderBase(parent, Box)
{
	SetType(Component::Collider);
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
	ColliderBase::~ColliderBase();
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
		glm::vec2 scale = _pParentObject->GetTransform()->GetScale() * _scale;

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

void BoxColliderComponent::DrawEditorUI()
{
	if (ImGui::CollapsingHeader("Box Collider Component"))
	{
		Component::DrawEditorUI();
	}
}