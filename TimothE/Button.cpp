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

		glm::vec2 tranformPosition = this->GetTransform()->GetPosition();

		if (mouseX > tranformPosition.x && mouseY > tranformPosition.y &&
			mouseX < tranformPosition.x + _width && mouseY < tranformPosition.y + _height)
		{
			std::cout << "Mouse clicked inside the button! " << std::endl;
		}
		
		std::cout << "Mouse clicked X: " << mouseX << " Y: " << mouseY << std::endl;
	}

}

void Button::Render()
{
}


