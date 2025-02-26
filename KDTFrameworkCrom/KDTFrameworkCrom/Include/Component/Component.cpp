#include "Component.h"

CComponent::CComponent()
{
}

CComponent::CComponent(const CComponent& Com)
{
}

CComponent::CComponent(CComponent&& Com)
{
}

CComponent::~CComponent()
{
}

bool CComponent::Init()
{
    return true;
}

bool CComponent::Init(const char* FileName)
{
    return false;
}

void CComponent::PreUpdate(float DeltaTime)
{
}

void CComponent::Update(float DeltaTime)
{
}

void CComponent::PostUpdate(float DeltaTime)
{
}

void CComponent::PreRender()
{
}

void CComponent::Render()
{
}

void CComponent::PostRender()
{
}
