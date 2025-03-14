#include "HitScanBullet.h"
#include "../Scene/Scene.h"
#include "../Component/SpriteComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "SpriteEffect.h"
#include "../Share/Log.h"
#include "../UI/UserWidget/MouseWidget.h"
#include "../Scene/Input.h"

CHitScanBullet::CHitScanBullet()
{
}

CHitScanBullet::CHitScanBullet(const CHitScanBullet& Obj) :
    CSceneObject(Obj)
{
}

CHitScanBullet::CHitScanBullet(CHitScanBullet&& Obj) :
    CSceneObject(Obj)
{
}

CHitScanBullet::~CHitScanBullet()
{
}

void CHitScanBullet::SetBulletCollisionProfile(const std::string& Name)
{
}

bool CHitScanBullet::Init()
{
    mRoot = CreateComponent<CSpriteComponent>();
    mBody = CreateComponent<CColliderAABB2D>();

    // 이미지 및 중심 설정
    mRoot->SetTexture("HitScan", TEXT("Texture/HitMarker.png"));
    mRoot->SetPivot(0.5f, 0.5f);

    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);

    // 총알의 실제 충돌 범위 설정
    mBody->SetBoxSize(100.f, 100.f);

    mBody->SetCollisionBeginFunc<CHitScanBullet>(this,
        &CHitScanBullet::CollisionBullet);

    mRoot->AddChild(mBody);

    return true;
}

void CHitScanBullet::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CHitScanBullet::CollisionBullet(const FVector3D& HitPoint, CColliderBase* Dest)
{
    CLog::PrintLog("Hit Scan");

    Dest->GetOwner()->Damage(1.f, this);

    CSpriteEffect* Effect = mScene->CreateObj<CSpriteEffect>("HitEffect");

    Effect->SetAnimation("HitScan");

    Effect->SetWorldPos(HitPoint);
    Effect->SetWorldScale(100.f, 100.f);

    Destroy();
}
