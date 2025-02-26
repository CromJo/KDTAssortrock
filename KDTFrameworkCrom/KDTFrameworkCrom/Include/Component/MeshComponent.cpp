#include "MeshComponent.h"
#include "../Shader/TransformCBuffer.h"

CMeshComponent::CMeshComponent()
{
    mTransformCBuffer = new CTransformCBuffer;
}

CMeshComponent::CMeshComponent(const CMeshComponent& Com)
{
    // ���� �״�� ������ ���� ���������
    mTransformCBuffer = Com.mTransformCBuffer->Clone();;
}

CMeshComponent::CMeshComponent(CMeshComponent&& Com)
{
    // ����� �Ƴ������� �̵�������
    mTransformCBuffer = Com.mTransformCBuffer;
    Com.mTransformCBuffer = nullptr;
}

CMeshComponent::~CMeshComponent()
{
    SAFE_DELETE(mTransformCBuffer)
}

bool CMeshComponent::Init()
{
    CSceneComponent::Init();

    return true;
}

bool CMeshComponent::Init(const char* FileName)
{
    CSceneComponent::Init(FileName);

    return true;
}

void CMeshComponent::PreUpdate(float DeltaTime)
{
    CSceneComponent::PreUpdate(DeltaTime);

}

void CMeshComponent::Update(float DeltaTime)
{
    CSceneComponent::Update(DeltaTime);
}

void CMeshComponent::PostUpdate(float DeltaTime)
{
    CSceneComponent::PostUpdate(DeltaTime);
}

void CMeshComponent::PreRender()
{
    CSceneComponent::PreRender();
}

void CMeshComponent::Render()
{
    CSceneComponent::Render();
}

void CMeshComponent::PostRender()
{
    CSceneComponent::PostRender();
}

CMeshComponent* CMeshComponent::Clone()
{
    return new CMeshComponent(*this);
}
