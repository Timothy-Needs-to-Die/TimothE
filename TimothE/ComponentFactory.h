#pragma once


#include "Component.h"
#include "Transform.h"
#include "Texture2D.h"
#include "TestComponent.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Camera.h"
#include "Button.h"
#include "TextComponent.h"
#include "PlayerInputComponent.h"
#include "Core.h"

class ComponentFactory {
public:
	static Component* GetComponent(Component::Types type, GameObject* pParent) {
		switch (type) {
		case Component::Types::None:
			TIM_LOG_ERROR("Component of NONE type attempting to be loaded");
			return nullptr;

		case Component::Types::Transform_Type:
			return new Transform(pParent);
		//case Component::Types::Texture_Type:
		//	return new Texture2D(pParent);
		case Component::Types::Test_Type:
			return new TestComponent(pParent);
		case Component::Types::Boxcollision_Type:
			return new BoxColliderComponent(pParent);
		case Component::Types::Camera_Type:
			return new Camera(-1.7f, 1.7f, -1.0f, 1.0f, "Cam", pParent);
		case Component::Types::Button_Type:
			return new Button(pParent);
		case Component::Types::Text_Type:
			return new TextComponent(pParent);
		case Component::PlayerInput:
			return new PlayerInputComponent(pParent);
		}
	}
};
