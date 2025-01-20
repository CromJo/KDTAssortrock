#include "StaticMeshComponent.h"
#include "../Asset/Mesh/StaticMesh.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Mesh/MeshManager.h"

CStaticMeshComponent::CStaticMeshComponent()
{
}

CStaticMeshComponent::CStaticMeshComponent(const CStaticMeshComponent& Com):
    CMeshComponent(Com)
{
}

CStaticMeshComponent::CStaticMeshComponent(CStaticMeshComponent&& Com) :
    CMeshComponent(Com)
{
}

CStaticMeshComponent::~CStaticMeshComponent()
{
}

void CStaticMeshComponent::SetShader(const std::string& Name)
{
    mShader = CShaderManager::GetInstance()->FindShader(Name);
}

void CStaticMeshComponent::SetShader(CShader* Shader)
{
    mShader = Shader;
}

void CStaticMeshComponent::SetMesh(const std::string& Name)
{
    mMesh = (CStaticMesh*)CAssetManager::GetInstance()->GetMeshManager()->FindMesh(Name);
}

void CStaticMeshComponent::SetMesh(CMesh* Mesh)
{
    mMesh = (CStaticMesh*)Mesh;
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

void CStaticMeshComponent::PreUpdate(float deltaTime)
{
    CMeshComponent::PreUpdate(deltaTime);
}

void CStaticMeshComponent::Update(float deltaTime)
{
    CMeshComponent::Update(deltaTime);
}

void CStaticMeshComponent::PostUpdate(float deltaTime)
{
    CMeshComponent::PostUpdate(deltaTime);
}

void CStaticMeshComponent::Collision(float deltaTime)
{
    CMeshComponent::Collision(deltaTime);
}

void CStaticMeshComponent::PreRender()
{
    CMeshComponent::PreRender();
}

void CStaticMeshComponent::Render()
{
    CMeshComponent::Render();

    // Static Mesh Ãâ·Â
    mShader->SetShader();

    mMesh->Render();
}

void CStaticMeshComponent::PostRender()
{
    CMeshComponent::PostRender();
}

CStaticMeshComponent* CStaticMeshComponent::Clone()
{
    return new CStaticMeshComponent(*this);
}
