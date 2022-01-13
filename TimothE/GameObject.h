#pragma once
#include <vector>
#include <string>
#include "Component.h"
#include "Transform.h"

class Texture2D;

using std::vector;
using std::string;

class GameObject
{
public:
	GameObject();
	GameObject(Transform* transform, Texture2D* texture);
	~GameObject();

	Component* GetComponent(string name);
	vector<Component*> GetComponents() { return _components; }
	Transform* GetTransform() { return _pTransform; }
	void SetTexture(Texture2D* texture) { _pTexture = texture; }
private:
	vector<Component*> _components;
	Transform* _pTransform;
	Texture2D* _pTexture;
};