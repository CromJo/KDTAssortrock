#include "PullBullet.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/MovementComponent.h"

CPullBullet::CPullBullet()
{
}

CPullBullet::CPullBullet(const CPullBullet& Obj)
{
}

CPullBullet::CPullBullet(CPullBullet&& Obj)
{
}

CPullBullet::~CPullBullet()
{
}

bool CPullBullet::Init()
{
    mMesh = CreateComponent<CStaticMeshComponent>();

    mMovement = CreateComponent<CMovementComponent>();
    mRotation = CreateComponent<CRotationComponent>();

    mMovement->SetUpdateComponent(mMesh);
    mRotation->SetUpdateComponent(mMesh);

    mRotation->SetEnable(false);
    mRotation->SetVelocityInit(false);
    
    mRotation->SetMoveZ(500.f);             // 회전용 z속도
    
    mMovement->SetMoveAxis(EAxis::Y);
    mMovement->SetMoveSpeed(mSkill6MoveSpeed);
    
    mMesh->SetWorldScale(25.f, 25.f, 1.f);

    SetRootComponent(mMesh);

    return true;
}

void CPullBullet::PreUpdate(float DeltaTime)
{
}

void CPullBullet::Update(float DeltaTime)
{
}
