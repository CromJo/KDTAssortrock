#include "MeshComponent.h"
#include "../Shader/TransformCBuffer.h"

CMeshComponent::CMeshComponent()
{
    mTransformCBuffer = new CTransformCBuffer;

    mTransformCBuffer->Init();
}

CMeshComponent::CMeshComponent(const CMeshComponent& Com) :
    CSceneComponent(Com)
{
    mTransformCBuffer = Com.mTransformCBuffer->Clone();
}

CMeshComponent::CMeshComponent(CMeshComponent&& Com):
    CSceneComponent(Com)
{
    mTransformCBuffer = Com.mTransformCBuffer;
    Com.mTransformCBuffer = nullptr;
}

CMeshComponent::~CMeshComponent()
{
    SAFE_DELETE(mTransformCBuffer);
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

void CMeshComponent::PreUpdate(float deltaTime)
{
    CSceneComponent::PreUpdate(deltaTime);
}

void CMeshComponent::Update(float deltaTime)
{
    CSceneComponent::Update(deltaTime);
}

void CMeshComponent::PostUpdate(float deltaTime)
{
    CSceneComponent::PostUpdate(deltaTime);
}

void CMeshComponent::Collision(float deltaTime)
{
    CSceneComponent::Collision(deltaTime);
}

void CMeshComponent::PreRender()
{
    CSceneComponent::PreRender();
}

void CMeshComponent::Render()
{
    //CSceneComponent::Render();
    mTransformCBuffer->SetWorldMatrix(mMatrixWorld);

    FMatrix matProj = DirectX::XMMatrixPerspectiveFovLH(
        DirectX::XMConvertToRadians(90.f), 
        1280.f / 720.f, 0.5f, 1000.f);

    mTransformCBuffer->SetProjMatrix(matProj);
    mTransformCBuffer->UpdateBuffer();
}

void CMeshComponent::PostRender()
{
    CSceneComponent::PostRender();
}

CMeshComponent* CMeshComponent::Clone()
{
    return nullptr;
}
