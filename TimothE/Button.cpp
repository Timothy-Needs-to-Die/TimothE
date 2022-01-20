#include "Button.h"

Button::Button(GameObject* parent) : Component(parent)
{
	_isClicked = false;
	_isHovering = false;
}

Button::~Button()
{
}

void Button::OnStart()
{
}

void Button::OnUpdate()
{
	int mouseX = Input::GetMouseX();
	int mouseY = Input::GetMouseY();

	Transform* transform = Parent()->GetComponent<Transform>();

	//glm::vec2* pos = Parent()->GetComponent<Transform>();
	glm::vec2 pos = transform->GetPosition();
	float width = transform->GetScale().x;
	float height = transform->GetScale().y;

	// Check if the mouse is inside the button
	if (mouseX > pos.x - width && mouseX < pos.x + width
		&& mouseY > pos.y - height && mouseY < pos.y + height)
	{
		// If the mouse is inside the button then we are now hovering over the button;
		_isHovering = true;
		
		// Check if the button is now being clicked
		if (Input::IsMouseButtonDown(BUTTON_1))
		{
			_isClicked = true;

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

	//Debug 
	//cout << "isHovering = " << _isHovering << " isClicked = " << _isClicked << endl;
}

void Button::OnEnd()
{
}

void Button::DrawEditorUI()
{
	ImGui::Text("Button");

	
}

void Button::AddOnClickCall(void(*function)())
{
	_onClickCalls.push_back(function);
}

void Button::RemoveOnClickCall(void(*function)())
{
	for (int i = 0; i < _onClickCalls.size(); i++)
	{
		if (_onClickCalls[i] == function)
		{
			_onClickCalls.erase(_onClickCalls.begin() + i);
		}
	}
}



