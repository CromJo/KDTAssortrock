#include "MeshComponent.h"
#include "../Shader/TransformCBuffer.h"

CMeshComponent::CMeshComponent()
{
    mTransformCBuffer = new CTransformCBuffer;
}

CMeshComponent::CMeshComponent(const CMeshComponent& Com)
{
    // 값을 그대로 가지기 위한 복사생성자
    mTransformCBuffer = Com.mTransformCBuffer->Clone();;
}

CMeshComponent::CMeshComponent(CMeshComponent&& Com)
{
    // 비용을 아끼기위한 이동생성자
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
