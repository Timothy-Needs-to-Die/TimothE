#include "pch.h"
#include "UIObject.h"


//TODO: Handling deleting an object and moving its children to this objects parent (if applicable)

UIObject::UIObject(std::string name, glm::vec2 designPos, glm::vec2 designSize) 
	: _designPosition(designPos), _designSize(designSize), _name(name)
{

}

UIObject::~UIObject()
{

}

void UIObject::Draw()
{

}

void UIObject::Update()
{
	for (auto& child : _pChildrenObjects) {
		child->Update();
	}
}

void UIObject::UpdateRenderPositionSize(float xScale, float yScale)
{
	//Update this objects position and size
	_renderSize.x = _designSize.x / xScale;
	_renderSize.y = _designSize.y / yScale;

	_renderPosition.x = _designPosition.x / xScale;
	_renderPosition.y = _designPosition.y / yScale;


	//Update all childs position and sizes
	for (auto& child : _pChildrenObjects) {
		child->UpdateRenderPositionSize(xScale, yScale);
	}
}
