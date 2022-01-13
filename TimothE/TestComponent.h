#pragma once
#include "Component.h"

class GameObject;

class TestComponent : public Component
{
public:
	COMPONENT_CLASS_CATEGOTY(Debug_Catagory);
	COMPONENT_CLASS_TYPE(Test_Type);
	TestComponent(GameObject* _mParentObject);
	~TestComponent();
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	void Test(int x, int y);

	GameObject* _parentObject;
	void SetGameObject(GameObject* newparent) {
		_parentObject = newparent;
	}
	// Getter
	GameObject* GetGameObject() {
		return _parentObject;
	}
};

