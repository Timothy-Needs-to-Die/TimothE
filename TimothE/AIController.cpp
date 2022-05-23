#include "AIController.h"

#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "TileMap.h"
#include "Time.h"
#include "SceneManager.h"


void AIController::Move(glm::vec2 moveToVec)
{
	Transform* transform = _pParentObject->GetTransform();
	transform->SetPosition(moveToVec);
}



void AIController::OnStart()
{

}

void AIController::OnUpdate()
{

}

void AIController::OnEnd()
{

}
