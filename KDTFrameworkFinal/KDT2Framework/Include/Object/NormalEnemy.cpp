#include "NormalEnemy.h"
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
#include "../Component/WidgetComponent.h"
#include "../UI/UserWidget/HeadInfo.h"
#include "../Scene/SceneUIManager.h"
#include "../UI/UserWidget/GuageInfo.h"

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
    mAnimation->AddSequence("EnemyMove", 2.f, 1.f, true, false);
    //mAnimation->AddSequence("EnemyMove", 2.f, 1.f, true, false);
    mAnimation->AddSequence("EnemyAttack", 1.f, 1.f, true, false);
    mAnimation->AddSequence("GunnerSkill", 1.f, 1.f, true, false);
    //mAnimation->AddSequence("EnemyAttackGuage", 1.5f, 1.f, false, false);

    mAIAnimationName[(int)EEnemyAI::Idle] = "EnemyIdle";
    mAIAnimationName[(int)EEnemyAI::Move] = "EnemyMove";
    mAIAnimationName[(int)EEnemyAI::Attack] = "EnemyAttack";
    //mAIAnimationName[(int)EEnemyAI::Skill] = "GunnerSkill";

    // N프레임 (설정한 값 : 0)로 애니메이션이 변경되면 지정된 함수 실행
    mAnimation->AddNotify<CNormalEnemy>("EnemyAttack",
        0, this, &CNormalEnemy::AttackNotify);

    mAnimation->SetEndFunction<CNormalEnemy>("EnemyAttack",
        this, &CNormalEnemy::AttackEnd);

    //mAnimation->AddNotify<CNormalEnemy>("EnemyMove",
    //    3, this, &CNormalEnemy::MovePointNotify);
    
    mAnimation->SetEndFunction<CNormalEnemy>("EnemyMove",
        this, &CNormalEnemy::MovePointEnd);



    mMovement = CreateComponent<CMovementComponent>();
    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(mSpeed);

    ////////// 게이지 애니메이션 ///////////
    mGuageBar = CreateComponent<CSpriteComponent>();
    //mGuageBar->SetPivot(0.5f, 0.5f);
    mGuageBar->SetRelativePos(-75.f, 70.f);
    mGuageBar->SetRelativeScale(1.5f, 0.2f);
    //mGuageInfo = mScene->GetUIManager()->CreateWidget<CGuageInfo>("GuageInfo");
    mRoot->AddChild(mGuageBar);

    mGuageAnimation = mGuageBar->CreateAnimation2D<CAnimation2D>();

    mGuageAnimation->AddSequence("EnemyAttackGuage", 1.5f, 1.f, true, false);
    mGuageBar->SetEnable(false);

    mGuageAnimation->SetEndFunction<CNormalEnemy>("EnemyAttackGuage",
        this, &CNormalEnemy::AttackGuageEnd);

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

// 애니메이션 용
void CNormalEnemy::MovePointNotify()
{
}

void CNormalEnemy::AttackLoop(float DeltaTime)
{
}

/// <summary>
/// 공격 수행 기능
/// </summary>
void CNormalEnemy::AttackNotify()
{

    // 애니메이션 재생
    mGuageBar->SetEnable(true);
}

void CNormalEnemy::AttackGuageEnd()
{
    CLog::PrintLog("공격 게이지 끝");

    mGuageBar->SetEnable(false);
	mGuageAnimation->ResetFrame();

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
    ChangeState(EEnemyAI::Idle);
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

/// <summary>
/// 이동 로직이 끝나면 공격하도록 하는 기능
/// </summary>
void CNormalEnemy::MovePointEnd()
{
    CLog::PrintLog("이동 끝마치고 공격");
    AttackNotify();
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
