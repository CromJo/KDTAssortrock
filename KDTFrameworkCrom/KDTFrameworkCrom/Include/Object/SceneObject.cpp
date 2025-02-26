#include "SceneObject.h"
#include "../Component/SceneComponent.h"

CSceneObject::CSceneObject()
{
}

CSceneObject::CSceneObject(const CSceneObject& Object)
{
}

CSceneObject::CSceneObject(CSceneObject&& Object)
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
	return false;
}

bool CSceneObject::Init(const char* FileName)
{
	return false;
}

void CSceneObject::PreUpdate(float DeltaTime)
{
}

void CSceneObject::Update(float DeltaTime)
{
}

void CSceneObject::PostUpdate(float DeltaTime)
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
