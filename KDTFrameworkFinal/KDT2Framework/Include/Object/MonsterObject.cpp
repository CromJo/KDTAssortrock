#include "MonsterObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Share/Log.h"
#include "../Component/SpriteComponent.h"

CMonsterObject::CMonsterObject()
{
}

CMonsterObject::CMonsterObject(const CMonsterObject& Obj)   :
    CSceneObject(Obj)
{
}

CMonsterObject::CMonsterObject(CMonsterObject&& Obj) :
    CSceneObject(Obj)
{
}

CMonsterObject::~CMonsterObject()
{
}

bool CMonsterObject::Init()
{
    //mRoot = CreateComponent<CStaticMeshComponent>();
    mRoot = CreateComponent<CSpriteComponent>();
    //mBody = CreateComponent<CColliderAABB2D>();
    mBody = CreateComponent<CColliderSphere2D>();
    //mBody = CreateComponent<CColliderOBB2D>();
    mDetect = CreateComponent<CColliderSphere2D>();

    //mRoot->SetMesh("CenterRect");
    //mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);

    mBody->SetCollisionProfile("Monster");
    mBody->SetRadius(50.f);
    //mBody->SetBoxSize(100.f, 100.f);
    mBody->SetCollisionBeginFunc<CMonsterObject>(this,
        &CMonsterObject::CollisionMonster);
    mBody->SetCollisionEndFunc<CMonsterObject>(this,
        &CMonsterObject::CollisionMonsterEnd);

    mRoot->AddChild(mBody);

    mDetect->SetCollisionProfile("MonsterDetect");
    mDetect->SetRadius(500.f);
    //mBody->SetBoxSize(100.f, 100.f);
    mDetect->SetCollisionBeginFunc<CMonsterObject>(this,
        &CMonsterObject::CollisionMonsterDetect);
    mDetect->SetCollisionEndFunc<CMonsterObject>(this,
        &CMonsterObject::CollisionMonsterDetectEnd);

    mRoot->AddChild(mDetect);

    return true;
}

void CMonsterObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    // 바라볼 대상이 있다면
    if (mTarget)
    {
        // 바라볼 대상이 살아있지 않다면 대기해라
        if (!mTarget->IsActive())
        {
            mAI = EMonsterAI::Idle;
            mTarget = nullptr;
        }
    }

    // 몬스터 행동 패턴 알고리즘
    switch (mAI)
    {
    case EMonsterAI::Idle:      // 대기
        AIIdle();
        break;
    case EMonsterAI::Move:      // 이동
        AIMove();
        break;
    case EMonsterAI::Trace:     // 추적 (바라봄)
        AITrace();
        break;
    case EMonsterAI::Patrol:    // 없음
        AIPatrol();
        break;
    case EMonsterAI::Attack:    // 공격
        AIAttack();
        break;
    case EMonsterAI::Death:     // 쥬금
        AIDeath();
        break;
    case EMonsterAI::Skill:     // 스킬사용
        AISkill();
        break;
    case EMonsterAI::Custom:
        AICustom();
        break;
    }
}

float CMonsterObject::Damage(float Attack,
    CSceneObject* Obj)
{
    float Dmg = CSceneObject::Damage(Attack, Obj);

    mHP -= (int)Dmg;

    if (mHP <= 0)
        Destroy();

    return Dmg;
}

void CMonsterObject::DetectTarget()
{
}

void CMonsterObject::DetectTargetRelease()
{
}

void CMonsterObject::CollisionMonster(
    const FVector3D& HitPoint, CColliderBase* Dest)
{
    //CLog::PrintLog("Collision");
}

void CMonsterObject::CollisionMonsterEnd(
    CColliderBase* Dest)
{
    //CLog::PrintLog("CollisionEnd");
}

/// <summary>
/// 몬스터가 타겟을 감지하는 기능
/// </summary>
/// <param name="HitPoint"></param>
/// <param name="Dest"></param>
void CMonsterObject::CollisionMonsterDetect(const FVector3D& HitPoint, 
    CColliderBase* Dest)
{
    // 타겟을 설정 후 
    mTarget = Dest->GetOwner();
    mAI = EMonsterAI::Trace;
    DetectTarget();
}

void CMonsterObject::CollisionMonsterDetectEnd(CColliderBase* Dest)
{
    mTarget = nullptr;
    mAI = EMonsterAI::Idle;
    DetectTargetRelease();
}

void CMonsterObject::AIIdle()
{
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Idle]);
}

void CMonsterObject::AIPatrol()
{
}

void CMonsterObject::AITrace()
{
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Trace]);
}

void CMonsterObject::AIMove()
{
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Move]);
}

void CMonsterObject::AIAttack()
{
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Attack]);
}

void CMonsterObject::AIDeath()
{
}

void CMonsterObject::AISkill()
{
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Skill]);
}

void CMonsterObject::AICustom()
{
}
