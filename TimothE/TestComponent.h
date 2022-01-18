#pragma once
#include "Component.h"

class GameObject;

class TestComponent : public Component
{
public:
	TestComponent() {
		SetType(Component::Types::Test_Type);
		SetCategory(Component::Categories::Debug_Category);
	}

	COMPONENT_STATIC_TYPE(Test_Type)

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

	// Inherited via ISerializable
	virtual bool SaveState(IStream& stream) const override {
		Component::SaveState(stream);

		return true;
	}
	virtual bool LoadState(IStream& stream) override {
		Component::LoadState(stream);

		return true;
	}
	// Inherited via Component
	virtual void DrawEditorUI() override;
};

