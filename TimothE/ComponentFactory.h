#pragma once


#include "Component.h"
#include "Transform.h"
#include "Texture2D.h"
#include "TestComponent.h"

class ComponentFactor {
public:
	static Component* GetComponent(Component::Types type) {
		switch (type) {
		case Component::Types::Transform_Type:
			return new Transform();
		case Component::Types::Texture_Type:
			return new Texture2D();
		case Component::Types::Test_Type:
			return new TestComponent();
		}
	}
};
