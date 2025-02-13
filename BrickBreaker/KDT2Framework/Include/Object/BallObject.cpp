#include "BallObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Share/Log.h"

CBallObject::CBallObject()
{
}

CBallObject::CBallObject(const CBallObject& Obj)  :
    CSceneObject(Obj)
{
}

CBallObject::CBallObject(CBallObject&& Obj) :
    CSceneObject(Obj)
{
}

CBallObject::~CBallObject()
{
}

void CBallObject::SetBallCollisionProfile(
    const std::string& Name)
{
    mBody->SetCollisionProfile(Name);
}

bool CBallObject::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    mBody = CreateComponent<CColliderAABB2D>();

    mMovement = CreateComponent<CMovementComponent>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(0.15f, 0.15f, 1.f);

    SetRootComponent(mRoot);

    mBody->SetBoxSize(15.f, 15.f);

    mBody->SetCollisionBeginFunc<CBallObject>(this,
        &CBallObject::CollisionBall);

    mRoot->AddChild(mBody);

    mMovement->SetUpdateComponent(mRoot);

    //mMovement->SetMoveAxis(EAxis::Y);
    mMovement->SetMoveSpeed(250.f);

    return true;
}

void CBallObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CBallObject::CollisionBall(const FVector3D& HitPoint,
    CColliderBase* Dest)
{
    //CLog::PrintLog("Collision");

    Dest->GetOwner()->Damage(1.f, this);

    Destroy();
}
