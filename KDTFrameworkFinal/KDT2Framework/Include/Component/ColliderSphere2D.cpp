#include "ColliderSphere2D.h"
#include "../Collision.h"
#include "../Asset/Mesh/Mesh.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Mesh/MeshManager.h"
#include "ColliderAABB2D.h"
#include "ColliderOBB2D.h"
#include "ColliderLine2D.h"

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
    if (!CColliderBase::Init())
        return false;

#ifdef _DEBUG

    mMesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh("FrameSphere2D");

#endif // _DEBUG


    return true;
}

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

    FVector2D Scale = { mOriginRadius, mOriginRadius };
    Scale *= 2.f;

    FVector2D temp = ApplyVirtualScale(Scale);
    // 매 프레임 충돌체 크기 업데이트    
    mRadius = mOriginRadius * temp.x;
    
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

/// <summary>
/// 충돌 시 동작하는 기능 (사거리 계산시 사용 중)
/// </summary>
/// <param name="HitPoint"></param>
/// <param name="Dest"></param>
/// <returns></returns>
bool CColliderSphere2D::Collision(FVector3D& HitPoint,
    CColliderBase* Dest)
{
    // 3D 객체면 종료
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
    case EColliderShape::OBB2D:
        return CCollision::CollisionSphere2DToOBB2D(
            HitPoint, this,
            (CColliderOBB2D*)Dest);
    case EColliderShape::Line2D:
        return CCollision::CollisionLine2DToSphere2D(HitPoint,
            (CColliderLine2D*)Dest, this);
    }

    return false;
}


