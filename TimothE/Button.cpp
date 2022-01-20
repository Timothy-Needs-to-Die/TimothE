#include "Button.h"


Button::Button(string name, int width, int height) : GameObject(name, ObjectType::UI)
{
	//have to divide by two, because the origin is at centre
	//so _width goes from the origin to a side of the square
	//meaning that the scaled width is equal to 2 * width
	_width = width / 2;
	_height = height / 2;
	GetTransform()->Scale({ _width, _height });
}

Button::~Button()
{
}

void Button::Update(float deltaTime)
{
	//TODO: Bounds checking on cursor in button
	if ( Input::IsMouseButtonDown(BUTTON_1)) 
	{
		int mouseX = Input::GetMouseX();
		int mouseY = Input::GetMouseY();

		_width = GetTransform()->GetScale().x;
		_height = GetTransform()->GetScale().y;

		glm::vec2 pos = GetTransform()->GetPosition();

		std::cout << "Mouse Pos: " << mouseX << ", " << mouseY << " Button Pos: " << pos.x << ", " << pos.y << std::endl;

		if (mouseX > pos.x - _width && mouseX < pos.x + _width
			&& mouseY > pos.y - _height && mouseY < pos.y + _height)
		{
			std::cout << "Mouse clicked inside the button! " << std::endl;
		}
		
		//std::cout << "Mouse clicked X: " << mouseX << " Y: " << mouseY << std::endl;
	}

	GameObject::Update(deltaTime);
}

void Button::Render()
{

}


