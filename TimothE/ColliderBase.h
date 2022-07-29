#pragma once
#include "pch.h"
#include "Component.h"


//Add a collision channel type system to colliders. Then only query intersections if these two objects can collide with eachother


enum CollisionChannel {
	CollisionChannel_None = 0x00000,
	CollisionChannel_Player = 0x00002,
	CollisionChannel_Enemy = 0x00004,
	CC_03 = 0x00006,
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
		_flags |= ch;
	}

	void RemoveCompatibleChannel(CollisionChannel ch) {
		if (IsColliderCompatible(ch)) {
			_flags ^= ch;
		}
	}

	void SetCollidersChannel(CollisionChannel ch) {
		_collidersChannel = ch;
	}

	CollisionChannel GetCollisionChannel() const {
		return _collidersChannel;
	}

	bool IsColliderCompatible(CollisionChannel ch) {
		return (_flags & ch) == ch;
	}

protected:
	bool _isTrigger;
	float _scale = 1.0f;

	int _flags;



	ColliderType _colType;

	CollisionChannel _collidersChannel;
};

