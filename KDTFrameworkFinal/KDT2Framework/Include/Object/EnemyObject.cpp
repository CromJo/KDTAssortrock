﻿#include "EnemyObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Share/Log.h"
#include "../Component/SpriteComponent.h"
#include "../Device.h"
#include "../Component/MovementComponent.h"
#include "../Scene/Navigation.h"

CEnemyObject::CEnemyObject()
{
}

CEnemyObject::CEnemyObject(const CEnemyObject& Obj)   :
    CSceneObject(Obj)
{
}

CEnemyObject::CEnemyObject(CEnemyObject&& Obj) :
    CSceneObject(Obj)
{
}

CEnemyObject::~CEnemyObject()
{
}

/// <summary>
/// 적의 기본적인 초기화 기능
/// </summary>
/// <returns></returns>
bool CEnemyObject::Init()
{
    //mRoot = CreateComponent<CStaticMeshComponent>();
    mRoot = CreateComponent<CSpriteComponent>();
    //mBody = CreateComponent<CColliderAABB2D>();
    mBody = CreateComponent<CColliderSphere2D>();
    //mBody = CreateComponent<CColliderOBB2D>();
    mDetect = CreateComponent<CColliderSphere2D>();
    mMovement = CreateComponent<CMovementComponent>();

    //mRoot->SetMesh("CenterRect");
    //mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);

    mBody->SetCollisionProfile("Enemy");
    mBody->SetRadius(50.f);
    //mBody->SetBoxSize(100.f, 100.f);
    mBody->SetCollisionBeginFunc<CEnemyObject>(this,
        &CEnemyObject::CollisionEnemy);
    mBody->SetCollisionEndFunc<CEnemyObject>(this,
        &CEnemyObject::CollisionEnemyEnd);

    mRoot->AddChild(mBody);

    mDetect->SetCollisionProfile("EnemyDetect");
    mDetect->SetRadius(1000.f);
    //mBody->SetBoxSize(100.f, 100.f);
    mDetect->SetCollisionBeginFunc<CEnemyObject>(this,
        &CEnemyObject::CollisionEnemyDetect);
    mDetect->SetCollisionEndFunc<CEnemyObject>(this,
        &CEnemyObject::CollisionEnemyDetectEnd);

    mRoot->AddChild(mDetect);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(200.f);

    return true;
}

void CEnemyObject::PreUpdate(float DeltaTime)
{
    mLogicTime += DeltaTime;

    // 바라볼 대상이 있다면 (추후 삭제 예정)
    if (mTarget)
    {
        // 바라볼 대상이 살아있지 않다면 대기해라
        if (!mTarget->IsActive())
        {
            mAI = EEnemyAI::Idle;
            mTarget = nullptr;
        }
    }

    if (mLogicTime > 2.f)
    {
        //mLogicTime -= 2.f;
        // AI로직을 랜덤 실행하기 위한 난수 적용
        int random = rand() % (int)EEnemyAI::End;

        //mAI = (EEnemyAI)random;
        if(rand()% 2 == 0)
			ChangeState(EEnemyAI::Idle);
		else
			ChangeState(EEnemyAI::Move);
        //ChangeState((EEnemyAI)random);
        //mAI = EEnemyAI::Idle;
    }

    LoopState(DeltaTime);

}

/// <summary>
/// 모든 적 오브젝트의 업데이트를 관장하는 기능.
/// 1. 전체적인 적 오브젝트이기 때문에,
///     전체적으로 수행할 기능들만 작성한다.
/// 2. 만약 적오브젝트 고유의 기능이 있다면 고유 클래스에서 작성해야한다.
/// </summary>
/// <param name="DeltaTime"></param>
void CEnemyObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    // 출력
    if (mLogicTime > 2.f)
    {
        mLogicTime -= 2.f;

        std::string str;
        str += "랜덤 로직 실행 : ";
        str += EnumString(mAI);
        CLog::PrintLog(str);
    }

}

float CEnemyObject::Damage(float Attack,
    CSceneObject* Obj)
{
    float Dmg = CSceneObject::Damage(Attack, Obj);

    mHP -= (int)Dmg;

    if (mHP <= 0)
        Destroy();

    return Dmg;
}

void CEnemyObject::DetectTarget()
{
}

void CEnemyObject::DetectTargetRelease()
{
}

/// <summary>
/// 적이 충돌 되었다면 실행되는 기능
/// </summary>
/// <param name="HitPoint"></param>
/// <param name="Dest"></param>
void CEnemyObject::CollisionEnemy(const FVector3D& HitPoint, CColliderBase* Dest)
{
    CLog::PrintLog("적이 충돌 되었음.");
}

void CEnemyObject::CollisionEnemyEnd(
    CColliderBase* Dest)
{
    CLog::PrintLog("적 충돌이 끝이났음");
}

/// <summary>
/// 몬스터가 타겟을 감지하는 기능
/// </summary>
/// <param name="HitPoint"></param>
/// <param name="Dest"></param>
void CEnemyObject::CollisionEnemyDetect(const FVector3D& HitPoint, 
    CColliderBase* Dest)
{
    // 타겟을 설정 후 
    mTarget = Dest->GetOwner();
    //mAI = EEnemyAI::Trace;
    //DetectTarget();
}

void CEnemyObject::CollisionEnemyDetectEnd(CColliderBase* Dest)
{
    mTarget = nullptr;
    mAI = EEnemyAI::Idle;
    DetectTargetRelease();
}


void CEnemyObject::MovePointLoop(float DeltaTime)
{
    /// 해결 방안
    /// 1. 이동 위치에 도달하면 이동기능 비활성화
    /// 2. 애니메이션 루프 
    
    FVector3D Target = mSaveMoveData;
    FVector3D CurrentTransform = GetWorldPosition();

    float 어그래 = CurrentTransform.Distance(Target);
    if (어그래 <= 50.f)
    {
        //멈췅!
        mMovement->SetMoveRandomPoint(FVector3D::Zero);
    }

}

void CEnemyObject::MovePointOnce()
{
    // 애니메이션 재생
    mAnimation->ChangeAnimation(mAIAnimationName[(int)EEnemyAI::Move]);

    // 현재 화면 크기를 불러온다.
    const FResolution& RS = CDevice::GetInst()->GetResolution();

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(200.f);

    int randX = rand() % (RS.Width / 2);
    int randY = rand() % (RS.Height / 2);

    mAnimation->SetAnimationReverseX(true);
    randX *= -1;

    FVector3D Dir = { randX - mRoot->GetWorldPosition().x, 0.f, 0.f };
    mSaveMoveData = Dir;
    Dir.Normalize();
    mMovement->SetMoveRandomPoint(Dir);
}

/*
    애니메이션 Notify 역할
        - 쓰지마라 (디테일 용임)
    
    Once 
        - 한번만 변경하게끔 해주는 기능

    Loop :
        - 기능을 수행하는 기능임 (Update)
*/


/// <summary>
/// 디버깅 용임 아무 효과 없음
/// </summary>
/// <param name="ai"></param>
/// <returns></returns>
std::string CEnemyObject::EnumString(EEnemyAI ai)
{
    switch (ai) {
    case EEnemyAI::Idle:
        return "Idle";
    case EEnemyAI::Move:
        return "MoveLeft";
    case EEnemyAI::Attack:
        return "Attack";
    }
}

void CEnemyObject::ChangeState(EEnemyAI Type)
{
    if (mAI == Type)
        return;

    mAI = Type;

    switch (Type)
    {
    case EEnemyAI::Idle:
        break;
    case EEnemyAI::Move:
        MovePointOnce();
        break;
    case EEnemyAI::Attack:
        // 어택 에니메이숀 재생
        break;
    case EEnemyAI::End:
        break;
    }
}

void CEnemyObject::LoopState(float DeltaTime)
{
    // 몬스터 행동 패턴 알고리즘
    switch (mAI)
    {
    case EEnemyAI::Idle:      // 대기
        AIIdle();
        break;
    case EEnemyAI::Move:      // 이동
        //MovePoint();
        mMovement->SetMoveRandomPoint(mSaveMoveData);
        AIMove();
        break;
        //case EEnemyAI::Trace:     // 추적 (바라봄)
        //    AIChangeMove();
        //    break;
        //case EEnemyAI::Patrol:    // 순찰
        //    AIChangeMove();
        //    break;
    case EEnemyAI::Attack:    // 공격
        AIAttack();
        break;
        //case EEnemyAI::Death:     // 쥬금
        //    AIChangeMove();
        //    break;
        //case EEnemyAI::Skill:     // 스킬사용
        //    AIChangeMove();
        //    break;
        //case EEnemyAI::Custom:
        //    AIChangeMove();
        //    break;
    }

}

/// <summary>
/// 적의 대기 동작 기능 
/// </summary>
void CEnemyObject::AIIdle()
{
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EEnemyAI::Idle]);
}

void CEnemyObject::AIPatrol()
{
}

//void CEnemyObject::AITrace()
//{
//    if (mAnimation)
//        mAnimation->ChangeAnimation(mAIAnimationName[(int)EEnemyAI::Trace]);
//}

/// <summary>
/// 적오브젝트의 공통 이동 기능
/// </summary>
void CEnemyObject::AIMove()
{
    if (mAnimation)
    {
        // 애니메이션 변경
        //if (mAI == EEnemyAI::Move)
        //    mAnimation->ChangeAnimation(mAIAnimationName[(int)EEnemyAI::Move]);
    }
}

void CEnemyObject::AIAttack()
{
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EEnemyAI::Attack]);
}

void CEnemyObject::AIDeath()
{
}

//void CEnemyObject::AISkill()
//{
//    if (mAnimation)
//        mAnimation->ChangeAnimation(mAIAnimationName[(int)EEnemyAI::Skill]);
//}

void CEnemyObject::AICustom()
{
}

void CEnemyObject::AIChangeMove()
{
    AIMove();
}
