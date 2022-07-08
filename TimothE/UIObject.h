#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

class UIObject
{

public:

	virtual void Draw();
	virtual void Update();
	void UpdateRenderPositionSize(float xScale, float yScale);


	//Getters
	glm::vec2 GetDesignPosition() const { return _designPosition; }
	glm::vec2 GetDesignSize() const { return _designSize; }

	glm::vec2 GetRenderPosition() const { return _renderPosition; }
	glm::vec2 GetRenderSize() const { return _renderSize; }

	std::string GetName() const { return _name; }

	bool IsActive() const { return _isActive; }

	UIObject* GetParent() { return _pParentObject; }

	std::vector<UIObject*> GetChildren() { return _pChildrenObjects; }

	UIObject* GetChildByName(const std::string& name) {
		for (auto& child : _pChildrenObjects) {
			if (child->GetName() == name) {
				return child;
			}
		}

		return nullptr;
	}

	//Setters
	void SetDesignPosition(glm::vec2 pos) { _designPosition = pos; }
	void SetDesignSize(glm::vec2 size) { _designSize = size; }

	void SetRenderPosition(glm::vec2 pos) { _renderPosition = pos; }
	void SetRenderSize(glm::vec2 size) { _renderSize = size; }


	void SetName(const std::string& name) { _name = name; }

	void SetActive(bool val) { _isActive = val; }

	void SetParent(UIObject* parent) {
		_pParentObject = parent;
	}

	void AddChild(UIObject* child) {
		_pChildrenObjects.emplace_back(child);

		child->SetParent(this);
	}
private:
	glm::vec2 _designPosition;
	glm::vec2 _designSize;

	glm::vec2 _renderPosition;
	glm::vec2 _renderSize;

	std::string _name;

	bool _isActive;

	UIObject* _pParentObject = nullptr;
	std::vector<UIObject*> _pChildrenObjects;

protected:

};

