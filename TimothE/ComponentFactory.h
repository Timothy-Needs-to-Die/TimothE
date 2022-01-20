#pragma once


#include "Component.h"
#include "Transform.h"
#include "Texture2D.h"
#include "TestComponent.h"
#include "GameObject.h"

class ComponentFactory {
public:
	static Component* GetComponent(Component::Types type, GameObject* pParent) {
		switch (type) {
		case Component::Types::None:
			std::cout << "Error: Component of NONE type attempting to be loaded" << std::endl;
			return nullptr;

		case Component::Types::Transform_Type:
			return new Transform(pParent);
		case Component::Types::Texture_Type:
			return new Texture2D(pParent);
		case Component::Types::Test_Type:
			return new TestComponent(pParent);
		}
	}
};
