#pragma once
#include "Component.h"

class GameObject;

class TestComponent : public Component
{
public:
	TestComponent() {}
	COMPONENT_CLASS_CATEGORY(Debug_Category);
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

	// Inherited via ISerializable
	virtual bool Write(IStream& stream) const override {
		Component::Write(stream);

		return true;
	}
	virtual bool Read(IStream& stream) override {
		Component::Read(stream);

		return true;
	}
	virtual void Fixup() override {

	}

	// Inherited via Component
	virtual void DrawEditorUI() override;
};

