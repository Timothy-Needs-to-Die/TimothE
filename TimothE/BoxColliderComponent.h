#pragma once
#include "UID.h"
#include <glm.hpp>
#include "Component.h"

struct Rect
{
	float btmLeft;
	float btmRight;
	float topLeft;
	float topRight;

	Rect(int xp, int yp, int w, int h) {
		btmLeft = xp;
		btmRight = yp;
		topLeft = w;
		topRight = h;
	}
}; 

class BoxColliderComponent : public Component		
{
public:
	COMPONENT_STATIC_TYPE(Boxcollision_Type)

	BoxColliderComponent(GameObject* parent);
	~BoxColliderComponent();

	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	//virtual void GetComponent() = 0;

	virtual void DrawEditorUI() override;

	virtual bool SaveState(IStream& stream) const override {
		//Write type
		WriteInt(stream, _type);

		//Write category
		WriteInt(stream, _category);

		return true;
	}
	virtual bool LoadState(IStream& stream) override {
		return true;
	}

	//Sets the size of the collider using a vec2
	void SetColliderSize(glm::vec2 size) { _size = size; };
	//Gets the size of the collider as a vec2
	glm::vec2 GetColliderSize() { return _size; };

	//Sets the colliders X size, based around the centre of the gameobject
	void SetColliderXSize(float x) { _size.x = x; };
	//Sets the colliders Y size, based around the centre of the gameobject
	void SetColliderYSize(float y) { _size.y = y; };

	/*
	* if the collider is a trigger, an interaction/encounter could occur
	* if not set to a trigger, then typical collisions take place
	*/

	//Sets the collider to be a trigger or not
	void SetTrigger(bool isTrigger) { _isTrigger = isTrigger; };
	//Checks to see if the collider is a trigger
	bool IsTrigger() {
		return _isTrigger;
	};
private:
	glm::vec2 _size;
	glm::vec2 _centre;
	bool _isTrigger;
	Rect* bounds;
};