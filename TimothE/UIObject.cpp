#include "pch.h"
#include "UIObject.h"

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
