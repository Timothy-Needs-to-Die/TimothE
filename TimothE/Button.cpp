#include "Button.h"

void TestFunction1()
{
	cout << "Test1" << endl;
}

void TestFunction2()
{
	cout << "Test2" << endl;
}

void TestFunction3()
{
	cout << "Test3" << endl;
}

Button::Button(string name, int width, int height) : GameObject(name, ObjectType::UI)
{
	//have to divide by two, because the origin is at centre
	//so _width goes from the origin to a side of the square
	//meaning that the scaled width is equal to 2 * width
	_width = width / 2;
	_height = height / 2;
	GetTransform()->Scale({ _width, _height });

	_isClicked = false;
	_isHovering = false;
}

Button::~Button()
{
}

void Button::Update(float deltaTime)
{
	int mouseX = Input::GetMouseX();
	int mouseY = Input::GetMouseY();

	glm::vec2 pos = GetTransform()->GetPosition();

	// Check if the mouse is inside the button
	if (mouseX > pos.x - _width && mouseX < pos.x + _width
		&& mouseY > pos.y - _height && mouseY < pos.y + _height)
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

	GameObject::Update(deltaTime);
}

void Button::Render()
{

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



