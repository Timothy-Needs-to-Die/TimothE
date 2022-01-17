#include "GameObject.h"
#include "Texture2D.h"
#include "Stream.h"
#include "ComponentFactory.h"
#include "imgui.h"

GameObject::GameObject(string name, ObjectType tag) : _name(name), _tag(tag)
{
	_UID = UID::GenerateUID();
	AddComponent(new Transform(), Component::Types::Transform_Type);
	Start();
}

GameObject::GameObject(string name, ObjectType tag, Transform* transform) : _name(name), _tag(tag)
{
	_UID = UID::GenerateUID();
	AddComponent(transform, Component::Types::Transform_Type);
	Start();
}

GameObject::GameObject() : _name("New GameObject")
{
	Transform* pTransform = new Transform();
	AddComponent(pTransform, Component::Transform_Type);
}

GameObject::GameObject(string name) : _name(name)
{
	Transform* pTransform = new Transform();
	AddComponent(pTransform, Component::Transform_Type);
}

GameObject::~GameObject()
{
	Exit();
	for (Component* c : _pComponents)
	{
		delete(c);
	}
}

void GameObject::Start()
{
	for (Component* c : _pComponents)
	{
		c->OnStart();
	}
}

void GameObject::Update(float deltaTime)
{
	for (Component* c : _pComponents)
	{
		c->OnUpdate();
	}
}

void GameObject::Exit()
{
	for (Component* c : _pComponents)
	{
		c->OnEnd();
	}
}

void GameObject::LoadTexture(char* path, string mode)
{
	if (GetTexture() == nullptr)
	{
		Texture2D* texture = new Texture2D();
		texture->Load(path, mode);
		_textureID = texture->GetID();
		AddComponent(texture, Component::Types::Texture_Type);

		return;
	}
	else
	{
		GetTexture()->Load(path, mode);
	}
}

void GameObject::DisplayInEditor()
{
	ImGui::Text(_name.c_str());

	for (auto& comp : _pComponents) {
		comp->DrawEditorUI();
	}

}

bool GameObject::Write(IStream& stream) const
{
	//TODO: Implement writing and reading component information

	//Writes name to serialized object
	WriteString(stream, _name);

	WriteString(stream, _UID);

	//Writes number of components
	WriteInt(stream, _pComponents.size());

	for (int i = 0; i < _pComponents.size(); ++i) 
	{
		_pComponents[i]->Write(stream);
	}

	//TODO: GameObjects need a child system

	return true;
}

bool GameObject::Read(IStream& stream)
{
	//Sets our name
	_name = ReadString(stream);

	_UID = ReadString(stream);

	//Reserve the amount of components
	int noComponents = ReadInt(stream);
	_pComponents.reserve(noComponents);

	for (int i = 0; i < noComponents; ++i) {
		Component::Types type = (Component::Types)ReadInt(stream);
		Component::Categories cat = (Component::Categories)ReadInt(stream);


		//Make instance of component
		Component* c = ComponentFactor::GetComponent(type);
		if (c == nullptr) {
			std::cout << "Failed to load gameobject: " << _name << " Component is null" << std::endl;
			return false;
		}

		//Read instance
		c->Read(stream);

		//Set component

		_pComponents[i] = c;
	}

	return true;
}

void GameObject::Fixup()
{

}

void GameObject::SetName(string name)
{
	_name = name;
}

void GameObject::SetType(ObjectType tag)
{
	_tag = tag;
}

Component* GameObject::GetComponent(Component::Types componentType)
{
	for (Component* c : _pComponents)
	{
		if (c->GetType() == componentType)
		{
			return c;
		}
	}
	return nullptr;
}

void GameObject::AddComponent(Component* component, Component::Types type)
{
	component->SetType(type);
	_pComponents.push_back(component);
}
