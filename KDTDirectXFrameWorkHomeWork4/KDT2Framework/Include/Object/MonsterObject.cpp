#include "MonsterObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "BulletObject.h"
#include "../Component/MovementComponent.h"

CMonsterObject::CMonsterObject()
{
}

CMonsterObject::CMonsterObject(const CMonsterObject& Obj)
{
}

CMonsterObject::CMonsterObject(CMonsterObject&& Obj)
{
}

CMonsterObject::~CMonsterObject()
{
}

bool CMonsterObject::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    mRotationPivot = CreateComponent<CSceneComponent>();
    mMovement = CreateComponent<CMovementComponent>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldPos(12.f, 12.f, 0.f);
    mRoot->SetWorldScale(120.f, 150.f, 1.f);


    SetRootComponent(mRoot);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(200.f);

	return false;
}

void CMonsterObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    FVector3D Rot = mRotationPivot->GetRelativeRotation();

    Rot.z += DeltaTime * mPivotRotationSpeed;

    mRotationPivot->SetRelativeRotationZ(Rot.z);
}

void CMonsterObject::MoveUp(float DeltaTime)
{
    //mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y));
}

void CMonsterObject::MoveDown(float DeltaTime)
{
}

void CMonsterObject::RotationZ(float DeltaTime)
{
}

void CMonsterObject::RotationZInv(float DeltaTime)
{
}

void CMonsterObject::Fire(float DeltaTime)
{
}
