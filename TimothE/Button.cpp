#include "Button.h"


Button::Button(string name, Transform* transform, Texture2D* texture, int width, int height) : GameObject(name, ObjectType::UI, texture, transform)
{
	_width = width;
	_height = height;

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

		Transform* tranform = GetTransform();

		if (mouseX > this->GetTransform()->GetX() && mouseY > this->GetTransform()->GetY() &&
			mouseX < this->GetTransform()->GetX() + _width && mouseY < this->GetTransform()->GetY() + _height)
		{
			std::cout << "Mouse clicked inside the button! " << std::endl;
		}
		
		std::cout << "Mouse clicked X: " << mouseX << " Y: " << mouseY << std::endl;
	}

}

void Button::Render()
{
}


