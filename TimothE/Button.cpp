#include "Button.h"

Button::Button(GameObject* parent) : Component(parent)
{
	SetType(Component::Button_Type);
	SetCategory(Component::UI_Category);

	// Set buttons to be enabled by default
	_isEnabled = true;

	_isClicked = false;
	_isHovering = false;

	// Editor UI Vars
	_editorIsEnabled = &_isEnabled;

	// If there is no box collider component, add one since the button needs one
	if (GetParent()->GetComponent<BoxColliderComponent>() == nullptr)
	{
		// Print to console to let the user know a new component was added
		Console::Print("BUTTON COMPONENT: Created Component::BoxCollider as is required for Button::OnUpdate");
		//std::cout << "BUTTON COMPONENT: created default box component for object" << std::endl;
		GetParent()->AddComponent(new BoxColliderComponent(GetParent()));
	}
}

Button::~Button()
{

}

void Button::OnStart()
{
}

void Button::OnUpdate()
{	
	if (Component::IsEnabled())
	{
		// Get the mouse positions
		int mouseX = Input::GetMouseX();
		int mouseY = Input::GetMouseY();

		// Get the position of the button through the transforms - THIS SHOULD BE HANDLED BY BOX COLLIDER 
		Transform* transform = GetParent()->GetComponent<Transform>();

		glm::vec2 pos = transform->GetPosition();
		float width = transform->GetScale().x;
		float height = transform->GetScale().y;

		// Check if the mouse is inside the button
		if (GetParent()->GetComponent<BoxColliderComponent>()->IsPointInside({mouseX, mouseY}))
		{
			// If the mouse is inside the button then we are now hovering over the button;
			_isHovering = true;

			// Check if the button is now being clicked
			if (Input::IsMouseButtonDown(BUTTON_1))
			{
				_isClicked = true;
				
				// debug
				std::cout << "Button Clicked" << std::endl;

				// If we have function calls to perform when the button is clicked
				if (!_onClickCalls.empty())
				{
					// Perform them all
					for (int i = 0; i < _onClickCalls.size(); i++)
					{
						_onClickCalls[i]();
					}
				}
			}
			else
			{
				// We are not clicking the button
				_isClicked = false;
			}
		}
		else
		{
			// We are not hovering over the button
			_isHovering = false;
		}

		// debug
		//std::cout << "isHovering = " << _isHovering << " isClicked = " << _isClicked << std::endl;
	}

	//std::cout << "Mouse clicked X: " << mouseX << " Y: " << mouseY << std::endl;
}

void Button::OnEnd()
{
}

void Button::DrawEditorUI()
{
	if (ImGui::CollapsingHeader("Button Component"))
	{
		Component::DrawEditorUI();
	}
}

void Button::AddClickEvent(void(*function)())
{
	_onClickCalls.push_back(function);
}

void Button::RemoveClickEvent(void(*function)())
{
	for (int i = 0; i < _onClickCalls.size(); i++)
	{
		if (_onClickCalls[i] == function)
		{
			_onClickCalls.erase(_onClickCalls.begin() + i);
		}
	}
}



