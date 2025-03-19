﻿#include "HitScanBullet.h"
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
    mBody->SetCollisionProfile(Name);
}

bool CHitScanBullet::Init()
{
    mRoot = CreateComponent<CSpriteComponent>();
    mBody = CreateComponent<CColliderAABB2D>();

    // 이미지 및 중심 설정
    mRoot->SetTexture("Miss", TEXT("Texture/HitMarker.png"));
    
    mRoot->SetPivot(0.5f, 0.5f);
    
	// 이미지 크기 설정
    mRoot->SetWorldScale(50.f, 50.f, 1.f);

    SetRootComponent(mRoot);

    // 총알의 실제 충돌 범위 설정
    mBody->SetBoxSize(50.f, 50.f);

	// 충돌 시작 함수 설정
    mBody->SetCollisionBeginFunc<CHitScanBullet>(this,
        &CHitScanBullet::CollisionHitScan);

    mRoot->AddChild(mBody);

    return true;
}

void CHitScanBullet::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

/// <summary>
/// 충돌 시 실행할 함수 
/// </summary>
/// <param name="HitPoint"></param>
/// <param name="Dest"></param>
void CHitScanBullet::CollisionHitScan(const FVector3D& HitPoint, CColliderBase* Dest)
{
    CLog::PrintLog("Hit Scan");

    Dest->GetOwner()->Damage(1.f, this);
    
    CSpriteEffect* Effect = mScene->CreateObj<CSpriteEffect>("HitEffect");

    Effect->SetAnimation("HitScan");
    
    Effect->SetWorldPos(HitPoint);
    Effect->SetWorldScale(100.f, 100.f);

    Destroy();
}
