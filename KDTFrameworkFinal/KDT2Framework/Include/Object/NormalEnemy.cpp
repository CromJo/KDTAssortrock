﻿#include "NormalEnemy.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Scene/Scene.h"
#include "../Device.h"
#include "BulletObject.h"
#include "PlayerObject.h"
#include "../Animation/Animation2D.h"
#include "../Component/MovementComponent.h"
#include "../Share/Log.h"
#include "../Object/HitScanBullet.h"

CNormalEnemy::CNormalEnemy()
{
}

CNormalEnemy::CNormalEnemy(const CNormalEnemy& Obj) :
    CEnemyObject(Obj)
{
}

CNormalEnemy::CNormalEnemy(CNormalEnemy&& Obj) :
    CEnemyObject(Obj)
{
}

CNormalEnemy::~CNormalEnemy()
{
}

bool CNormalEnemy::Init()
{
    CEnemyObject::Init();

    mRoot->SetPivot(0.5f, 0.5f);

    // 자기자신에 애니메이션 컴포넌트 추가
    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

    mAnimation->AddSequence("EnemyIdle", 1.f, 1.f, true, false);
    mAnimation->AddSequence("EnemyMove1", 1.f, 1.f, true, false);
    mAnimation->AddSequence("EnemyAttack", 1.f, 1.f, true, false);
    mAnimation->AddSequence("GunnerSkill", 1.f, 1.f, true, false);

    mAIAnimationName[(int)EEnemyAI::Idle] = "EnemyIdle";
    mAIAnimationName[(int)EEnemyAI::Move] = "EnemyMove1";
    mAIAnimationName[(int)EEnemyAI::Attack] = "EnemyAttack";
    //mAIAnimationName[(int)EEnemyAI::Skill] = "GunnerSkill";

    // N프레임 (설정한 값 : 0)로 애니메이션이 변경되면 지정된 함수 실행
    mAnimation->AddNotify<CNormalEnemy>("EnemyAttack",
        0, this, &CNormalEnemy::AttackNotify);

    mAnimation->SetEndFunction<CNormalEnemy>("EnemyAttack",
        this, &CNormalEnemy::AttackEnd);

    mAnimation->AddNotify<CNormalEnemy>("EnemyMove1",
        0, this, &CNormalEnemy::MovePoint);

    mMovement = CreateComponent<CMovementComponent>();
    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(mSpeed);

    return true;
}

void CNormalEnemy::PreUpdate(float DeltaTime)
{
    CEnemyObject::PreUpdate(DeltaTime);
}

void CNormalEnemy::Update(float DeltaTime)
{
    CEnemyObject::Update(DeltaTime);
}

/// <summary>
/// 타겟을 찾았다면 실행되는 기능
/// </summary>
void CNormalEnemy::DetectTarget()
{
    mAI = EEnemyAI::Attack;
}

void CNormalEnemy::Move()
{
    mAI = EEnemyAI::Move;
}

/// <summary>
/// 
/// </summary>
void CNormalEnemy::AIAttack()
{
    CEnemyObject::AIAttack();

    if (mTarget)
    {
        if (mTarget->IsEnable())
        {
            /*FVector3D   ViewDir = mTarget->GetWorldPosition() -
                GetWorldPosition();
            ViewDir.Normalize();

            float Angle = FVector3D::Axis[EAxis::Y].GetAngle(ViewDir);*/
            float Angle = GetWorldPosition().GetViewTargetAngle(
                mTarget->GetWorldPosition());

            // 공격할때 이미지만 회전하는 기능
            //SetWorldRotationZ(Angle);
        }
    }
}

void CNormalEnemy::MovePoint()
{
    // 현재 화면 크기를 불러온다.
    const FResolution& RS = CDevice::GetInst()->GetResolution();

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(200.f);

    int randX = rand() % (RS.Width / 2);
    int randY = rand() % (RS.Height / 2);

    switch (mMoveDirect)
    {
    case EEnemyMoveDirect::None:
        break;
    case EEnemyMoveDirect::Left:
        randX *= -1;
        break;
    case EEnemyMoveDirect::Right:
        break;
    default:
        break;
    }

    // 랜덤한 좌표를 설정해준다.
    //mMovement->SetMoveRandomPoint(FVector3D(randX - mRoot->GetWorldPosition().x,
    //    randY - mRoot->GetWorldPosition().y, 0.f));

    mMovement->SetMoveRandomPoint(FVector3D(randX - mRoot->GetWorldPosition().x,
        0.f, 0.f));
}

/// <summary>
/// 공격 수행 기능
/// </summary>
void CNormalEnemy::AttackNotify()
{
    CHitScanBullet* HitScan = mScene->CreateObj<CHitScanBullet>("HitScan");
    HitScan->SetBulletCollisionProfile("EnemyAttack");

    CSceneComponent* Root = HitScan->GetRootComponent();

    FVector3D Pos = mTarget->GetWorldPosition();

    HitScan->SetWorldScale(50.f, 50.f);
    HitScan->SetWorldPos(Pos);
    HitScan->SetLifeTime(1.f);
}

/// <summary>
/// 공격 애니메이션 끝난 후 실행
/// 1. 4번 공격 시 스킬 발동
/// </summary>
void CNormalEnemy::AttackEnd()
{
    //if (mFireCount == 4)
    //{
    //    mAI = EEnemyAI::Skill;
    //}
}

void CNormalEnemy::SkillNotify()
{
    mFireCount = 0;
    CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

    Bullet->SetBulletCollisionProfile("EnemyAttack");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 75.f);

    Bullet->SetLifeTime(2.f);

    Bullet = mScene->CreateObj<CBulletObject>("Bullet");

    Bullet->SetBulletCollisionProfile("EnemyAttack");

    Root = Bullet->GetRootComponent();

    Pos = mRoot->GetWorldPosition();
    Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->AddWorldRotationZ(-45.f);
    Root->SetWorldPos(Pos + Dir * 75.f);

    Bullet->SetLifeTime(2.f);


    Bullet = mScene->CreateObj<CBulletObject>("Bullet");

    Bullet->SetBulletCollisionProfile("EnemyAttack");

    Root = Bullet->GetRootComponent();

    Pos = mRoot->GetWorldPosition();
    Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->AddWorldRotationZ(45.f);
    Root->SetWorldPos(Pos + Dir * 75.f);

    Bullet->SetLifeTime(2.f);
}

//void CNormalEnemy::SkillEnd()
//{
//    mAI = EEnemyAI::Attack;
//}

//FVector3D CNormalEnemy::MovePoint()
//{
//    return FVector3D();
//}

//void CNormalEnemy::MovePoint()
//{
//
//}
