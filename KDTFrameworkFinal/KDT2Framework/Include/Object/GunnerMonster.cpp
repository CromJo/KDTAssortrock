#include "GunnerMonster.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "PlayerObject.h"
#include "../Animation/Animation2D.h"

CGunnerMonster::CGunnerMonster()
{
}

CGunnerMonster::CGunnerMonster(const CGunnerMonster& Obj) :
    CEnemyObject(Obj)
{
}

CGunnerMonster::CGunnerMonster(CGunnerMonster&& Obj) :
    CEnemyObject(Obj)
{
}

CGunnerMonster::~CGunnerMonster()
{
}

bool CGunnerMonster::Init()
{
    CEnemyObject::Init();

    mRoot->SetPivot(0.5f, 0.5f);

    // 자기자신에 애니메이션 컴포넌트 추가
    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

    mAnimation->AddSequence("EnemyIdle", 1.f, 1.f, true, false);
    mAnimation->AddSequence("EnemyMove1", 1.f, 1.f, true, false);
    mAnimation->AddSequence("EnemyAttack", 1.f, 1.f, true, false);
    mAnimation->AddSequence("GunnerSkill", 1.f, 1.f, true, false);

    mAIAnimationName[(int)EMonsterAI::Idle] = "EnemyIdle";
    mAIAnimationName[(int)EMonsterAI::Move] = "EnemyMove1";
    mAIAnimationName[(int)EMonsterAI::Attack] = "EnemyAttack";
    mAIAnimationName[(int)EMonsterAI::Skill] = "GunnerSkill";

    // N프레임 (설정한 값 : 0)로 애니메이션이 변경되면 지정된 함수 실행
    mAnimation->AddNotify<CGunnerMonster>("EnemyAttack",
        0, this, &CGunnerMonster::AttackNotify);

    mAnimation->SetEndFunction<CGunnerMonster>("EnemyAttack",
        this, &CGunnerMonster::AttackEnd);

    //mAnimation->AddNotify<CGunnerMonster>("GunnerSkill",
    //    0, this, &CGunnerMonster::SkillNotify);
    //
    //mAnimation->SetEndFunction<CGunnerMonster>("GunnerSkill",
    //    this, &CGunnerMonster::SkillEnd);


    //mRoot->SetTexture("Monster1Tex", TEXT("Texture/block_wall.png"));
    //mRoot->SetMesh("CenterTexRect");
    //mRoot->AddTexture(0, "Teemo", TEXT("Texture/teemo.png"), 0);
    //mRoot->SetMaterial(0, "Monster1");
    //mRoot->SetShader("StaticMeshShader");
    //mRoot->SetOpacity(0, 0.5f);

    //SetTarget(mScene->FindObjectFromType<CPlayerObject>());

    return true;
}

void CGunnerMonster::Update(float DeltaTime)
{
    CEnemyObject::Update(DeltaTime);

    //if (mTarget)
    //{
    //    if (mTarget->IsEnable())
    //    {
    //        /*FVector3D   ViewDir = mTarget->GetWorldPosition() -
    //            GetWorldPosition();
    //        ViewDir.Normalize();

    //        float Angle = FVector3D::Axis[EAxis::Y].GetAngle(ViewDir);*/
    //        float Angle = GetWorldPosition().GetViewTargetAngle(
    //            mTarget->GetWorldPosition());

    //        SetWorldRotationZ(Angle);
    //    }
    //}

    //else
    //{
    //}

    /*mFireTime -= DeltaTime;

    if (mFireTime <= 0.f)
    {
        mFireTime += 1.f;

        ++mFireCount;

        CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

        Bullet->SetBulletCollisionProfile("MonsterAttack");

        CSceneComponent* Root = Bullet->GetRootComponent();

        FVector3D Pos = mRoot->GetWorldPosition();
        FVector3D Dir = mRoot->GetAxis(EAxis::Y);

        Root->SetWorldScale(50.f, 50.f);
        Root->SetWorldRotation(mRoot->GetWorldRotation());
        Root->SetWorldPos(Pos + Dir * 75.f);

        Bullet->SetLifeTime(2.f);

        if (mFireCount == 4)
        {
            mFireCount = 0;
            Bullet = mScene->CreateObj<CBulletObject>("Bullet");

            Bullet->SetBulletCollisionProfile("MonsterAttack");

            Root = Bullet->GetRootComponent();

            Pos = mRoot->GetWorldPosition();
            Dir = mRoot->GetAxis(EAxis::Y);

            Root->SetWorldScale(50.f, 50.f);
            Root->SetWorldRotation(mRoot->GetWorldRotation());
            Root->AddWorldRotationZ(-45.f);
            Root->SetWorldPos(Pos + Dir * 75.f);

            Bullet->SetLifeTime(2.f);


            Bullet = mScene->CreateObj<CBulletObject>("Bullet");

            Bullet->SetBulletCollisionProfile("MonsterAttack");

            Root = Bullet->GetRootComponent();

            Pos = mRoot->GetWorldPosition();
            Dir = mRoot->GetAxis(EAxis::Y);

            Root->SetWorldScale(50.f, 50.f);
            Root->SetWorldRotation(mRoot->GetWorldRotation());
            Root->AddWorldRotationZ(45.f);
            Root->SetWorldPos(Pos + Dir * 75.f);

            Bullet->SetLifeTime(2.f);
        }
    }*/
}

void CGunnerMonster::DetectTarget()
{
    mAI = EMonsterAI::Attack;
}

void CGunnerMonster::AIAttack()
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

            SetWorldRotationZ(Angle);
        }
    }
}

void CGunnerMonster::AttackNotify()
{
    CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

    Bullet->SetBulletCollisionProfile("MonsterAttack");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 75.f);

    Bullet->SetLifeTime(2.f);

    ++mFireCount;
}

/// <summary>
/// 공격 애니메이션 끝난 후 실행
/// 1. 4번 공격 시 스킬 발동
/// </summary>
void CGunnerMonster::AttackEnd()
{
    if (mFireCount == 4)
    {
        mAI = EMonsterAI::Skill;
    }
}

void CGunnerMonster::SkillNotify()
{
    mFireCount = 0;
    CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

    Bullet->SetBulletCollisionProfile("MonsterAttack");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 75.f);

    Bullet->SetLifeTime(2.f);

    Bullet = mScene->CreateObj<CBulletObject>("Bullet");

    Bullet->SetBulletCollisionProfile("MonsterAttack");

    Root = Bullet->GetRootComponent();

    Pos = mRoot->GetWorldPosition();
    Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->AddWorldRotationZ(-45.f);
    Root->SetWorldPos(Pos + Dir * 75.f);

    Bullet->SetLifeTime(2.f);


    Bullet = mScene->CreateObj<CBulletObject>("Bullet");

    Bullet->SetBulletCollisionProfile("MonsterAttack");

    Root = Bullet->GetRootComponent();

    Pos = mRoot->GetWorldPosition();
    Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->AddWorldRotationZ(45.f);
    Root->SetWorldPos(Pos + Dir * 75.f);

    Bullet->SetLifeTime(2.f);
}

void CGunnerMonster::SkillEnd()
{
    mAI = EMonsterAI::Attack;
}
