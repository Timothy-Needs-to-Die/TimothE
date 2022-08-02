#include "pch.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Stream.h"
#include "ComponentFactory.h"
#include "imgui.h"
#include "Console.h"
#include "BoxColliderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Core.h"

GameObject::GameObject(std::string name, std::string tag) 
	: _name(name), _tag(tag)
{
	_UID = UID::GenerateUID();

	//If name is empty apply default name
	if (name.empty()) {
		name = "New GameObject";
	}

	_tag = tag;

	_pTransform = AddComponent<Transform>(new Transform(this));

	Start();
}

GameObject::~GameObject()
{
	Exit();
	for (int i = 0; i < _pComponents.size(); i++)
	{
		if(_pComponents[i]->GetType() == Component::Texture_Type) continue;
		
		auto it = _pComponents.erase(_pComponents.begin() + i);
		delete* it;
	}
}

void GameObject::Start()
{
	for (Component* c : _pComponents)
	{
		c->OnStart();
	}
}

void GameObject::Update()
{
	for (Component* c : _pComponents)
	{
		if (c == nullptr) continue;
		if (c->GetOwner() == nullptr) continue;
		if (c->GetOwner()->IsToBeDestroyed() || !c->GetOwner()->IsActive()) continue;

		c->OnUpdate();
		if (c->GetType() == Component::ParticleSystem_Type)
		{
			ParticleSystem* p = (ParticleSystem*)c;
			p->SetParentTransform(_pTransform);
		}
	}

	UniqueLogic();
}

void GameObject::Exit()
{
	for (Component* c : _pComponents)
	{
		c->OnEnd();
	}
}

void GameObject::DisplayInEditor()
{
	ImGui::Text(_name.c_str());

	for (auto& comp : _pComponents) {
		comp->DrawEditorUI();
	}

}

bool GameObject::SaveState(IStream& stream) const
{
	//Writes name to serialized object
	WriteString(stream, _name);

	WriteString(stream, _UID);

	//Writes number of components
	WriteInt(stream, _pComponents.size());

	for (int i = 0; i < _pComponents.size(); ++i)
	{
		//_pComponents[i]->SaveState(stream);
	}

	//TODO: GameObjects need a child system

	return true;
}

bool GameObject::LoadState(IStream& stream)
{
	//Sets our name
	_name = ReadString(stream);

	_UID = ReadString(stream);

	//Reserve the amount of components
	int noComponents = ReadInt(stream);

	for (int i = 0; i < noComponents; ++i) {
		Component::Types type = (Component::Types)ReadInt(stream);

		if (type == Component::Transform_Type) {
			//_pTransform->LoadState(stream);
		}
		else
		{
			//Make instance of component
			auto* c = ComponentFactory::GetComponent(type, this);
			if (c == nullptr) {
				TIM_LOG_ERROR("Failed to load Gameobject: " << _name << " Component is null");
				return false;
			}

			//Read instance
			//c->LoadState(stream);

			//Set component
			AddComponent(c);
		}
	}
	//Texture2D* texture = GetComponent<Texture2D>();

	return true;
}

void GameObject::OnTriggerEnter(ColliderBase* other)
{
	for (auto& comp : _pComponents) {
		comp->OnTriggerEnter(other);
	}
}

void GameObject::OnColliderEnter(ColliderBase* other)
{
	for (auto& comp : _pComponents) {
		comp->OnCollisionEnter(other);
	}
}

void GameObject::OnTriggerExit(ColliderBase* other)
{
	for (auto& comp : _pComponents) {
		comp->OnTriggerExit(other);
	}
}

void GameObject::OnColliderExit(ColliderBase* other)
{
	for (auto& comp : _pComponents) {
		comp->OnCollisionExit(other);
	}
}

void GameObject::UniqueLogic()
{
}

Component* GameObject::GetComponentInChild(std::string name, Component::Types type)
{
	//if (_pChild != nullptr)
	//{
	//	for (Component* c : _pChild->GetComponents())
	//	{
	//		if (c->GetType() == type)
	//			return c;
	//	}
	//
	//	std::cout << "[ERROR]: Component does not exist in child." << std::endl;
	//
	//	return nullptr;
	//}
	//else
	//{
	//	std::cout << "[ERROR]: GameObject child does not exist." << std::endl;
	//	return nullptr;
	//}

	for (auto& child : _pChildren) {
		if (child->GetName() != name) continue;

		for (auto& comp : child->GetComponents())
		{
			if (comp->GetType() == type) {
				return comp;
			}
		}
	}


	return nullptr;
}

std::vector<Component*> GameObject::GetComponentsInChild(std::string name)
{
	for (auto& child : _pChildren) {
		if (child->GetName() == name) {
			return child->GetComponents();
		}
	}

	return std::vector<Component*>();
}

Component* GameObject::GetComponentInParent(Component::Types type)
{
	if (_pParent != nullptr)
	{
		for (Component* c : _pParent->GetComponents())
		{
			if (c->GetType() == type)
				return c;
		}

		std::cout << "[ERROR]: Component does not exist in parent." << std::endl;

		return nullptr;
	}
	else
	{
		std::cout << "[ERROR]: GameObject parent does not exist." << std::endl;
		return nullptr;
	}
}

std::vector<Component*> GameObject::GetComponentsInParent()
{
	if (_pParent != nullptr)
		return _pParent->GetComponents();

	std::cout << "[ERROR]: GameObject parent does not exist." << std::endl;

	return std::vector<Component*>();
}

void GameObject::SwapComponents(int index1, int index2)
{
	std::iter_swap(_pComponents.begin() + index1, _pComponents.begin() + index2);
}

void GameObject::SetName(std::string name)
{
	_name = name;
}


void GameObject::SetOwner(GameObject* parent)
{
	_pParent = parent;
	_pParent->AddChild(this);
}

void GameObject::AddChild(GameObject* newChild)
{
	_pChildren.emplace_back(newChild);
}

void GameObject::AddedComponent(Component* comp)
{
	Scene::AddedComponentHandler(this, comp);
}

void GameObject::RemoveComponent(Component* comp)
{
	Scene::RemoveComponentHandler(this, comp);
	_pComponents.erase(std::find(_pComponents.begin(), _pComponents.end(), comp));
	delete comp;
}
