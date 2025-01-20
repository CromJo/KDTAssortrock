#include "SceneObject.h"
#include "../Component/SceneComponent.h"

CSceneObject::CSceneObject()
{
}

CSceneObject::CSceneObject(const CSceneObject& Obj)
{
}

CSceneObject::CSceneObject(CSceneObject&& Obj)
{
}

CSceneObject::~CSceneObject()
{
}

void CSceneObject::SetRootComponent(CSceneComponent* Root)
{
    mRootComponent = Root;
}

bool CSceneObject::Init()
{
    return true;
}

bool CSceneObject::Init(const char* FileName)
{
    return true;
}

void CSceneObject::PreUpdate(float deltaTime)
{
}

void CSceneObject::Update(float deltaTime)
{
}

void CSceneObject::PostUpdate(float deltaTime)
{
}

void CSceneObject::Collision(float deltaTime)
{
}

void CSceneObject::PreRender()
{
}

void CSceneObject::Render()
{
}

void CSceneObject::PostRender()
{
}

CSceneObject* CSceneObject::Clone()
{
    return nullptr;
}
