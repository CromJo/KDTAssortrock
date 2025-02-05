#include "ColliderSphere2D.h"
#include "../Collision.h"
#include "../Asset/Mesh/Mesh.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Mesh/MeshManager.h"
#include "ColliderAABB2D.h"

// Sphere상태로 만들어주는 생성자
CColliderSphere2D::CColliderSphere2D()
{
    mColliderType = EColliderType::Colider2D;
    mColliderShape = EColliderShape::Sphere2D;
}

CColliderSphere2D::CColliderSphere2D(const CColliderSphere2D& Com) :
    CColliderBase(Com)
{
    mColliderType = EColliderType::Colider2D;
    mColliderShape = EColliderShape::Sphere2D;
}

CColliderSphere2D::CColliderSphere2D(CColliderSphere2D&& Com) :
    CColliderBase(Com)
{
    mColliderType = EColliderType::Colider2D;
    mColliderShape = EColliderShape::Sphere2D;
}

CColliderSphere2D::~CColliderSphere2D()
{
}

bool CColliderSphere2D::Init()
{  
    // Collider가 기본생성 (초기화)가 되었는지 체크
    if (!CColliderBase::Init())
        return false;

#ifdef _DEBUG
    // 라인렌더 그려주기
    mMesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh("FrameSphere2D");

#endif // _DEBUG


    return true;
}

// 파일에서 불러오는 용도의 초기화
bool CColliderSphere2D::Init(const char* FileName)
{
    if (!CColliderBase::Init(FileName))
        return false;

    return true;
}

void CColliderSphere2D::PreUpdate(float DeltaTime)
{
    CColliderBase::PreUpdate(DeltaTime);
}

void CColliderSphere2D::Update(float DeltaTime)
{
    CColliderBase::Update(DeltaTime);

    mMin.x = mWorldPos.x - mRadius;
    mMin.y = mWorldPos.y - mRadius;

    mMax.x = mWorldPos.x + mRadius;
    mMax.y = mWorldPos.y + mRadius;

    SetWorldScale(FVector2D(mRadius * 2.f, mRadius * 2.f));
}

void CColliderSphere2D::PostUpdate(float DeltaTime)
{
    CColliderBase::PostUpdate(DeltaTime);
}

void CColliderSphere2D::Collision(float DeltaTime)
{
    CColliderBase::Collision(DeltaTime);
}

void CColliderSphere2D::PreRender()
{
    CColliderBase::PreRender();
}

void CColliderSphere2D::Render()
{
    CColliderBase::Render();
}

void CColliderSphere2D::PostRender()
{
    CColliderBase::PostRender();
}

CColliderSphere2D* CColliderSphere2D::Clone()
{
    return new CColliderSphere2D(*this);
}

bool CColliderSphere2D::Collision(FVector3D& HitPoint,
    CColliderBase* Dest)
{
    if (Dest->GetColliderType() == EColliderType::Colider3D)
        return false;

    switch (Dest->GetColliderShape())
    {
    case EColliderShape::AABB2D:
        return CCollision::CollisionAABB2DToSphere2D(
            HitPoint, (CColliderAABB2D*)Dest, this);
    case EColliderShape::Sphere2D:
        return CCollision::CollisionSphere2DToSphere2D(
            HitPoint, this,
            (CColliderSphere2D*)Dest);
    }

    return false;
}


