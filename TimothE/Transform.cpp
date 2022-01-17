#include "Transform.h"
#include "imgui.h"

Transform::Transform() : Component()
{
	_scaleX = 1;
	_scaleY = 1;
	_xPos = 0;
	_yPos = 0;
	_xRot = 0;
	_yRot = 0;
}

Transform::Transform(float x, float y, float rotx, float roty, float scalex, float scaley) : Component()
{
	_scaleX = scalex;
	_scaleY = scaley;
	_xPos = x;
	_yPos = y;
	_xRot = rotx;
	_yRot = roty;
}

void Transform::OnStart()
{

}

void Transform::OnUpdate()
{

}

void Transform::OnEnd()
{

}

void Transform::EditorUI()
{
	ImGui::Text("Transform");

	// get the position
	float* pos = new float[2]{ GetPosition()->_x, GetPosition()->_y };
	// create boxes to set the position
	if (ImGui::InputFloat2("Position", pos))
	{
		// set the position on the game object
		SetPosition(pos[0], pos[1]);
	}

	float* rot = new float[2]{ GetXrotation(), GetYrotation() };
	if (ImGui::InputFloat2("Rotation", rot))
	{
		SetXrotation(rot[0]);
		SetYrotation(rot[1]);
	}

	float* scale = new float[2]{ GetXScale(), GetYScale() };
	if (ImGui::InputFloat2("Scale", scale))
	{
		SetXScale(scale[0]);
		SetYScale(scale[1]);
	}
}

void Transform::SetPosition(float x, float y)
{
	_xPos = x;
	_yPos = y;
}

void Transform::SetXrotation(float xRot)
{
	_xRot = xRot;
}

void Transform::SetYrotation(float yRot)
{
	_yRot = yRot;
}

void Transform::SetXScale(float scale)
{
	_scaleX = scale;
}

void Transform::SetYScale(float scale)
{
	_scaleY = scale;
}
