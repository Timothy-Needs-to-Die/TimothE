#include "Button.h"


Button::Button(string name, int width, int height) : GameObject(name, ObjectType::UI)
{
	_width = width;
	_height = height;
	GetTransform()->Scale({ width, height });
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

		glm::vec2 pos = GetTransform()->GetPosition();

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


