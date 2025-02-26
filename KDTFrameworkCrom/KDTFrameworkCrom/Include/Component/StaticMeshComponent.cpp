#include "StaticMeshComponent.h"

CStaticMeshComponent::CStaticMeshComponent()
{
}

CStaticMeshComponent::CStaticMeshComponent(const CStaticMeshComponent& Com)
{
}

CStaticMeshComponent::CStaticMeshComponent(CStaticMeshComponent&& Com)
{
}

CStaticMeshComponent::~CStaticMeshComponent()
{
}

bool CStaticMeshComponent::Init()
{
    CMeshComponent::Init();

    return true;
}

bool CStaticMeshComponent::Init(const char* FileName)
{
    CMeshComponent::Init(FileName);

    return true;
}

void CStaticMeshComponent::PreUpdate(float DeltaTime)
{
    CMeshComponent::PreUpdate(DeltaTime);

}

void CStaticMeshComponent::Update(float DeltaTime)
{
    CMeshComponent::Update(DeltaTime);
}

void CStaticMeshComponent::PostUpdate(float DeltaTime)
{
    CMeshComponent::PostUpdate(DeltaTime);
}

void CStaticMeshComponent::PreRender()
{
    CMeshComponent::PreRender();
}

void CStaticMeshComponent::Render()
{
    CMeshComponent::Render();
}

void CStaticMeshComponent::PostRender()
{
    CMeshComponent::PostRender();
}

CStaticMeshComponent* CStaticMeshComponent::Clone()
{
    return new CStaticMeshComponent(*this);
}
