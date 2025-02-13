#include "BrickObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BallObject.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Share/Log.h"

CBrickObject::CBrickObject()
{
}

CBrickObject::CBrickObject(const CBrickObject& Obj)   :
    CSceneObject(Obj)
{
}

CBrickObject::CBrickObject(CBrickObject&& Obj) :
    CSceneObject(Obj)
{
}

CBrickObject::~CBrickObject()
{
}

bool CBrickObject::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    //mBody = CreateComponent<CColliderAABB2D>();
    mBody = CreateComponent<CColliderSphere2D>();
    //mBody = CreateComponent<CColliderOBB2D>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);

    mBody->SetCollisionProfile("Brick");
    mBody->SetRadius(50.f);
    //mBody->SetBoxSize(100.f, 100.f);
    mBody->SetCollisionBeginFunc<CBrickObject>(this,
        &CBrickObject::CollisionBrick);
    mBody->SetCollisionEndFunc<CBrickObject>(this,
        &CBrickObject::CollisionBrickEnd);

    mRoot->AddChild(mBody);

    return true;
}

void CBrickObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    if (mTarget)
    {
        if (!mTarget->IsActive())
            mTarget = nullptr;
    }
}

float CBrickObject::Damage(float Attack,
    CSceneObject* Obj)
{
    float Dmg = CSceneObject::Damage(Attack, Obj);

    mHP -= (int)Dmg;

    if (mHP <= 0)
        Destroy();

    return Dmg;
}

void CBrickObject::CollisionBrick(
    const FVector3D& HitPoint, CColliderBase* Dest)
{
    CLog::PrintLog("Collision");
}

void CBrickObject::CollisionBrickEnd(
    CColliderBase* Dest)
{
    CLog::PrintLog("CollisionEnd");
}
