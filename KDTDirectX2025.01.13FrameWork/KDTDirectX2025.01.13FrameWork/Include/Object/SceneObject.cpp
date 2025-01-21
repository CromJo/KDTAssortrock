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
    mRootComponent->PreUpdate(deltaTime);
}

void CSceneObject::Update(float deltaTime)
{
    mRootComponent->Update(deltaTime);
}

void CSceneObject::PostUpdate(float deltaTime)
{
    mRootComponent->PostUpdate(deltaTime);
}

void CSceneObject::Collision(float deltaTime)
{
    mRootComponent->Collision(deltaTime);
}

void CSceneObject::PreRender()
{
    mRootComponent->PreRender();
}

void CSceneObject::Render()
{
    mRootComponent->Render();
}

void CSceneObject::PostRender()
{
    mRootComponent->PostRender();
}

CSceneObject* CSceneObject::Clone()
{
    return nullptr;
}
