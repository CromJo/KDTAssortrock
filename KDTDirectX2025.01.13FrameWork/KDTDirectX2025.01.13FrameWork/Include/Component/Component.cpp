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
    return false;
}

bool CComponent::Init(const char* FileName)
{
    return false;
}

void CComponent::PreUpdate(float deltaTime)
{
}

void CComponent::Update(float deltaTime)
{
}

void CComponent::PostUpdate(float deltaTime)
{
}

void CComponent::Collision(float deltaTime)
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

CComponent* CComponent::Clone()
{
    return nullptr;
}
