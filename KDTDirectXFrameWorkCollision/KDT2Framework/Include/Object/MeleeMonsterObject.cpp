#include "MeleeMonsterObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"


CMeleeMonsterObject::CMeleeMonsterObject()
{
}

CMeleeMonsterObject::CMeleeMonsterObject(const CMeleeMonsterObject& Obj)
	: CSceneObject(Obj)
{
}

CMeleeMonsterObject::CMeleeMonsterObject(CMeleeMonsterObject&& Obj)
	: CSceneObject(Obj) 
{
}

CMeleeMonsterObject::~CMeleeMonsterObject()
{
}

bool CMeleeMonsterObject::Init()
{
    // 컴포넌트
    mRoot = CreateComponent<CStaticMeshComponent>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);

    return true;
}

void CMeleeMonsterObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);            // 씬 오브젝트 업데이트

    // 타겟이 존재하는지 체크
    if (!mTarget->IsActive())
        mTarget = nullptr;

    // 타겟이 활성화 되어있는지 체크
    else if (mTarget->IsEnable())
    {
        /*FVector3D   ViewDir = mTarget->GetWorldPosition() -
            GetWorldPosition();
        ViewDir.Normalize();

        float Angle = FVector3D::Axis[EAxis::Y].GetAngle(ViewDir);*/
        float Angle = GetWorldPosition().GetViewTargetAngle(
            mTarget->GetWorldPosition());

        SetWorldRotationZ(Angle);
    }

    mFireTime -= DeltaTime;

    if (mFireTime <= 0.f)
    {
        mFireTime += 0.5f;                              // 공격 쿨타임

        CBulletObject* MeleeAttack = mScene->CreateObj<CBulletObject>("Bullet");

        CSceneComponent* Root = MeleeAttack->GetRootComponent();    // 공격 기능 생성

        FVector3D Pos = mRoot->GetWorldPosition();                  // 근접몬스터 포지션 대입
        FVector3D Dir = mRoot->GetAxis(EAxis::Y);                   // 근접몬스터 

        Root->SetWorldScale(100.f, 35.f);                           // 공격 크기 설정
        Root->SetWorldRotation(mRoot->GetWorldRotation());          // 공격 회전값 근접몬스터와 동일하게 설정
        Root->SetWorldPos(Pos + Dir * 75.f);                        // 공격 위치 근접몬스터 정면 앞으로 설정

        MeleeAttack->SetLifeTime(0.5f);                             // 공격몬스터 이펙트 시간
    }
}
