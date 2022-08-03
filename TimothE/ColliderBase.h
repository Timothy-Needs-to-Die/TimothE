#pragma once
#include "pch.h"
#include "Component.h"

/*
In order for a collision/triggers to occur between two objects
- Both colliders must have a collision channel set. e.g. SetCollisionChannel(CollisionChannel_Enemy). 
CollisionChannel_None will result in that object being skipped
- The channels that the objects want to collide with must be added. e.g. AddCompatibleChannel(CollisionChannel_Player)
- You can check if a channel has been added to a collider by querying it. e.g. IsColliderCompatible(CollisionChannel_Player)

This collision channel system is in place to reduce collision checks between objects that don't need to check for collisions with each other.
For example projectiles from the player may not want to hit guards. 
*/

/*
Example of Creating a Box Collider
	BoxColliderComponent* pBox = AddComponent(new BoxColliderComponent(this));
	pBox->SetTrigger(true);
	pBox->SetCollidersChannel(CollisionChannel_Enemy);
	pBox->AddCompatibleChannel(CollisionChannel_Player);

	This is creating a Box Collider that will act as a trigger, is on the enemy collision channel
	and will only collide with the player collision channel
*/

//Collision channels are used a way to represent what objects can collide with.
//Use all of these channels before adding anymore. Rename channels as needed (Will require full rebuild due to how entwined physics is)
enum CollisionChannel {
	CollisionChannel_None = 0x00000,
	CollisionChannel_Player = 0x00002,
	CollisionChannel_Enemy = 0x00004,
	CollisionChannel_SceneTransition = 0x00006,
	CC_04 = 0x00008,
	CC_05 = 0x00010,
	CC_06 = 0x00012,
	CC_07 = 0x00014,
	CC_08 = 0x00016,
	CC_09 = 0x00018,
	CC_10 = 0x00020,
	CC_11 = 0x00022,
	CC_12 = 0x00024,
	CC_13 = 0x00026,
	CC_14 = 0x00028,
	CC_15 = 0x00030,
	CC_16 = 0x00032,
	CC_17 = 0x00034,
	CC_18 = 0x00036,
	CC_19 = 0x00038,
	CC_20 = 0x00040,
	CC_21 = 0x00042,
	CC_22 = 0x00044,
	CC_23 = 0x00046,
	CC_24 = 0x00048,
	CC_25 = 0x00050,
	CC_26 = 0x00052,
	CC_27 = 0x00054,
	CC_28 = 0x00056,
	CC_29 = 0x00058,
	CC_30 = 0x00060,
	CC_31 = 0x00062,
};


enum class ColliderType{
	Circle,
	Box
};


class ColliderBase : public Component
{
public:
	ColliderBase(GameObject* parent, ColliderType type);
	~ColliderBase();

	COMPONENT_STATIC_TYPE(Collider)

	bool IsTrigger() const { return _isTrigger; }
	void SetTrigger(bool val) { _isTrigger = val; }

	ColliderType GetColliderType() const { return _colType; }

	float GetScale() const { return _scale; }
	void SetScale(float val) { _scale = val; }

	void AddCompatibleChannel(CollisionChannel ch) {
		_compatibleChannels |= ch;
	}

	void RemoveCompatibleChannel(CollisionChannel ch) {
		if (IsColliderCompatible(ch)) {
			_compatibleChannels ^= ch;
		}
	}

	void SetCollidersChannel(CollisionChannel ch) {
		_collidersChannel = ch;
	}

	CollisionChannel GetCollisionChannel() const {
		return _collidersChannel;
	}

	bool IsColliderCompatible(CollisionChannel ch) {
		return (_compatibleChannels & ch) == ch;
	}

protected:
	//Is this collider a trigger. e.g. Does it go through objects without a physical reaction
	bool _isTrigger;

	//Scale of the collider against the size of the object. If this is 10.0 then the collider will be 10x larger than the object.
	float _scale = 1.0f;

	//This int represents this colliders compatible channels. 
	int _compatibleChannels;


	//Holds the type of collider this object is (Currently Box or Circle)
	ColliderType _colType;

	//Holds what channel this collider belongs to.
	CollisionChannel _collidersChannel;
};

