#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "BallObject.h"
#include "TornadoBullet.h"
#include "TalonR.h"
#include "GravityBullet.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "BulletDot.h"
#include "PenetrationBullet.h"

CPlayerObject::CPlayerObject()
{
}

CPlayerObject::CPlayerObject(const CPlayerObject& Obj)  :
    CSceneObject(Obj)
{
}

CPlayerObject::CPlayerObject(CPlayerObject&& Obj) :
    CSceneObject(Obj)
{
}

CPlayerObject::~CPlayerObject()
{
}

bool CPlayerObject::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    //mBody = CreateComponent<CColliderAABB2D>();
    //mBody = CreateComponent<CColliderSphere2D>();
    mBody = CreateComponent<CColliderOBB2D>();
    mLine = CreateComponent<CColliderLine2D>();
    mRotationPivot = CreateComponent<CSceneComponent>();
    mCamera = CreateComponent<CCameraComponent>();

    mMovement = CreateComponent<CMovementComponent>();
    mRotation = CreateComponent<CRotationComponent>();

    mRoot->SetMesh("CenterTexRect");
    mRoot->AddTexture(0, "Teemo", TEXT("Texture/teemo.png"), 0);
    mRoot->SetOpacity(0, 0.5f);
    mRoot->SetWorldPos(0.f, 0.f, 0.f);
    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);
    
    mBody->SetCollisionProfile("Player");
    mBody->SetBoxSize(100.f, 30.f);
    //mBody->SetRadius(50.f);

    // 총알 생성
    BallInit();

    mRoot->AddChild(mBody);

    mRoot->AddChild(mLine);

    mLine->SetCollisionProfile("Player");
    mLine->SetRelativePos(0.f, 50.f);
    mLine->SetLineDistance(300.f);

    mCamera->SetProjectionType(ECameraProjectionType::Ortho);

    mRoot->AddChild(mCamera);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(200.f);

    mRotation->SetUpdateComponent(mRotationPivot);

    mRotation->SetVelocityInit(false);

    mRotation->SetMoveZ(360.f);

    mScene->GetInput()->AddBindKey("Left", 'A');
    mScene->GetInput()->AddBindKey("Right", 'D');
    mScene->GetInput()->AddBindKey("BallFire", VK_SPACE);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Left",
        EInputType::Hold, this, &CPlayerObject::MoveLeft);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Right",
        EInputType::Hold, this, &CPlayerObject::MoveRight);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("BallFire",
        EInputType::Hold, this, &CPlayerObject::BallFire);

    return true;
}

void CPlayerObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    if (mSkill4Enable)
    {
        UpdateSkill4(DeltaTime);
    }
}

void CPlayerObject::Damage(int Dmg)
{
    mHP -= Dmg;
}

void CPlayerObject::MoveLeft(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1.f);
}

void CPlayerObject::MoveRight(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * 1.f);
}

void CPlayerObject::BallInit()
{
    // 총알 생성
    //CBallObject* Ball = mScene->CreateObj<CBallObject>("Ball");

    mBall = mScene->CreateObj<CBallObject>("Ball");

    mBall->SetBallCollisionProfile("BallFire");

    CSceneComponent* Root = mBall->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(10.f, 10.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 25.f);

    //Ball->SetLifeTime(2.f);
}

void CPlayerObject::BallFire(float DeltaTime)
{
    // 게임 시작이 된 상태면 종료
    if (mBall->GetAlive())
        return;

    // 게임 시작이 된 상태가 아니였다면 
    // 공을 발사
    mBall->SetAlive(true);
    //mBall->GetMovement()->SetMoveAxis(EAxis::Y);

    //mBall->GetMovement()->AddMove()
}

void CPlayerObject::Skill1(float DeltaTime)
{
    if (!mSkill1Object)
    {
        mSkill1Object = mScene->CreateObj<CBallObject>("Bullet");
        mSkill1Object->SetSpeed(0.f);
    }

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D   Dir = mRoot->GetAxis(EAxis::Y);

    mSkill1Object->GetRootComponent()->SetWorldRotation(mRoot->GetWorldRotation());
    mSkill1Object->GetRootComponent()->SetWorldPos(Pos + Dir);

    FVector3D   Scale = mSkill1Object->GetRootComponent()->GetWorldScale();

    Scale.x += DeltaTime * 0.5f;
    Scale.y += DeltaTime * 0.5f;

    if (Scale.x >= 4.f)
        Scale.x = 4.f;

    if (Scale.y >= 4.f)
        Scale.y = 4.f;

    mSkill1Object->GetRootComponent()->SetWorldScale(Scale);
}

void CPlayerObject::Skill1Fire(float DeltaTime)
{
    mSkill1Object->SetSpeed(2.f);

    mSkill1Object->SetLifeTime(1.f);

    mSkill1Object = nullptr;
}

void CPlayerObject::Skill2(float DeltaTime)
{
    // 스킬 2번이 비활성화일 경우 활성화한다.
    if (!mSkill2Enable)
    {
        mSkill2Enable = true;
        mSkill2Time = 3.f;
        mSkill2TimeAcc = 0.f;
        mSkill2TimeInterval = 0.2f;
    }
}

void CPlayerObject::Skill3(float DeltaTime)
{
    CTornadoBullet* Bullet = mScene->CreateObj<CTornadoBullet>("Bullet");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D   Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir);

    Bullet->SetLifeTime(10.f);
}

void CPlayerObject::Skill4(float DeltaTime)
{
    if (!mSkill4Enable)
    {
        mSkill4Enable = true;
        mSkill4Time = 5.f;
        mSkill4TimeAcc = 0.f;
        mSkill4ReadyTime = 2.f;

        mPivotRotationSpeed = 360.f;
        mSkill4State = ESkill4State::Expansion;
    }
}

void CPlayerObject::Skill5(float DeltaTime)
{
    // 8개 방향에 총알을 생성한다.
    FVector3D   Dir = mRoot->GetAxis(EAxis::Y);
    FVector3D   Rot = mRoot->GetWorldRotation();

    FMatrix matRot;
    matRot.RotationZ(45.f);

    for (int i = 0; i < 8; ++i)
    {
        CTalonR* Bullet = mScene->CreateObj<CTalonR>("Bullet");

        Bullet->SetTarget(this);

        CSceneComponent* Root = Bullet->GetRootComponent();

        FVector3D Pos = mRoot->GetWorldPosition();

        Root->SetWorldRotation(Rot);
        Root->SetWorldPos(Pos + Dir);

        Rot.z += 45.f;

        Dir = Dir.TransformNormal(matRot);
        Dir.Normalize();
    }
}

void CPlayerObject::Skill6(float DeltaTime)
{
    CGravityBullet* Bullet = mScene->CreateObj<CGravityBullet>("Bullet");

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Bullet->SetWorldScale(50.f, 50.f);
    Bullet->SetWorldRotation(mRoot->GetWorldRotation());
    Bullet->SetWorldPos(Pos + Dir * 75.f);
}

void CPlayerObject::Skill7(float DeltaTime)
{
    CGravityBullet* Bullet = mScene->CreateObj<CGravityBullet>("Bullet");

    Bullet->SetGravityType(EGravityType::Push);

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Bullet->SetWorldScale(50.f, 50.f);
    Bullet->SetWorldRotation(mRoot->GetWorldRotation());
    Bullet->SetWorldPos(Pos + Dir * 75.f);
}

void CPlayerObject::Skill8(float DeltaTime)
{
    CBulletDot* Bullet = mScene->CreateObj<CBulletDot>("Bullet");

    Bullet->SetBulletCollisionProfile("BallFire");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(300.f, 300.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 75.f);

    Bullet->SetBoxSize(300.f, 300.f);
}

void CPlayerObject::Skill9(float DeltaTime)
{
    CPenetrationBullet* Bullet =
        mScene->CreateObj<CPenetrationBullet>("Bullet");

    Bullet->SetBulletCollisionProfile("BallFire");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 75.f);
}

void CPlayerObject::UpdateSkill4(float DeltaTime)
{
    mSkill4TimeAcc += DeltaTime;

    switch (mSkill4State)
    {
    case ESkill4State::Expansion:
        // DeltaTime / mSkill4ReadyTime 을 하게 되면 확장되는 2초라는
        // 시간에 대해서 현재 DeltaTime이 몇퍼센트의 시간이 흘렀는지를
        // 구해낸다.
        mSkill4Range += DeltaTime / mSkill4ReadyTime * 
            mSkill4RangeLength;
        if (mSkill4TimeAcc >= mSkill4ReadyTime)
        {
            mSkill4TimeAcc -= mSkill4ReadyTime;
            mSkill4Range = mSkill4MaxRange;
            mSkill4State = ESkill4State::Maintain;
        }

        break;
    case ESkill4State::Maintain:

        if (mSkill4TimeAcc >= mSkill4Time)
        {
            mSkill4TimeAcc = 0.f;
            mSkill4State = ESkill4State::Reduction;
        }
        break;
    case ESkill4State::Reduction:

        mSkill4Range -= DeltaTime / mSkill4ReadyTime *
            mSkill4RangeLength;
        if (mSkill4TimeAcc >= mSkill4ReadyTime)
        {
            mSkill4Enable = false;
            mSkill4TimeAcc = 0.f;
            mSkill4Range = 2.f;
            mSkill4State = ESkill4State::Expansion;
            mPivotRotationSpeed = 180.f;
        }

        break;
    }

}
