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

		if (mouseX > this->GetTransform()->GetPosition().x && mouseY > this->GetTransform()->GetPosition().y &&
			mouseX < this->GetTransform()->GetPosition().x + _width && mouseY < this->GetTransform()->GetPosition().y + _height)
		{
			std::cout << "Mouse clicked inside the button! " << std::endl;
		}
		
		std::cout << "Mouse clicked X: " << mouseX << " Y: " << mouseY << std::endl;
	}

	GameObject::Update(deltaTime);
}

void Button::Render()
{

}


