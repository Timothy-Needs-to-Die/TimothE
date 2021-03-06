#include "pch.h"
#include "Bed.h"

#include "Button.h"
#include "Physics.h"

Button::Button(GameObject* parent) : Component(parent)
{
	SetType(Component::Button_Type);

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
		Console::Print("[LOG: Button::Constructor]: Created Component::BoxCollider");// as is required for Button::OnUpdate");
		//std::cout << "BUTTON COMPONENT: created default box component for object" << std::endl;
		GetParent()->AddComponent(new BoxColliderComponent(GetParent()));
	}
	// If there is no text component, add one since the button needs one
	if (GetParent()->GetComponent<TextComponent>() == nullptr)
	{
		// Print to console to let the user know a new component was added
		Console::Print("[LOG: Button::Constructor]: Created Component::TextComponent");
		//std::cout << "BUTTON COMPONENT: created default text component for object" << std::endl;
		GetParent()->AddComponent(new TextComponent(GetParent()));
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
		// Check if the mouse is inside the button
		if (Physics::Intersects(_pParentObject->GetComponent<BoxColliderComponent>(), Input::GetMouseScreenCoords()))
		{
			// If the mouse is inside the button then we are now hovering over the button;
			_isHovering = true;

			// Check if the button is now being clicked
			if (!_isClicked)
			{
				if (Input::IsMouseButtonDown(BUTTON_1))
				{
					_isClicked = true;

					// debug
					std::cout << "[LOG: Button::OnUpdate]: Button Clicked" << std::endl;

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
			}
			else
			{
				if (Input::IsMouseButtonUp(BUTTON_1))
				{
					// We are not clicking the button
					_isClicked = false;
				}
			}
		}
		else
		{
			// We are not hovering over the button
			_isHovering = false;
		}
	}
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
