﻿#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "HitScanBullet.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "../Component/SpriteComponent.h"
#include "../Animation/Animation2D.h"
#include "../Share/Log.h"
#include "SpriteEffect.h"
#include "../Component/WidgetComponent.h"
#include "../Scene/SceneUIManager.h"
#include "../UI/Common/ProgressBar.h"
#include "../UI/UserWidget/HeadInfo.h"
#include "../Component/InventoryComponent.h"
#include "../Scene/SceneAssetManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Texture/Texture.h"
#include "../Asset/Texture/TextureManager.h"
//#include "../Animation/Animation2DSequence.h"
//#include "../Animation/Animation2D.h"

// 추후 삭제 전처리기
#include "BulletObject.h"
#include "BulletDot.h"

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

bool CPlayerObject::KeyInput()
{
    mScene->GetInput()->AddBindKey("Reloading", mReloadingKey);

    return true;
}

bool CPlayerObject::Init()
{
    //__super::Init();
    CSceneObject::Init();

    KeyInput();

    //mRoot = CreateComponent<CStaticMeshComponent>();
    mRoot = CreateComponent<CSpriteComponent>("Player");
    //mBody = CreateComponent<CColliderAABB2D>();
    //mBody = CreateComponent<CColliderSphere2D>();
    mBody = CreateComponent<CColliderOBB2D>();
    //mLine = CreateComponent<CColliderLine2D>();
    mRotationPivot = CreateComponent<CSceneComponent>();
    mCamera = CreateComponent<CCameraComponent>();
    mHPBar = CreateComponent<CWidgetComponent>();

    mHPBar->SetRelativePos(-75.f, 150.f);
    CHeadInfo* HeadInfo = mScene->GetUIManager()->CreateWidget<CHeadInfo>("HeadInfo");
    mHPBar->SetWidget(HeadInfo);

    mRoot->AddChild(mHPBar);

    mMovement = CreateComponent<CMovementComponent>();
    mRotation = CreateComponent<CRotationComponent>();

    //mRoot->SetTexture("Teemo", TEXT("Texture/teemo.png"));
    mRoot->SetPivot(0.5f, 0.5f);

    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

    mAnimation->AddSequence("PlayerIdle", 2.5f, 1.f, true, false);
    mAnimation->AddSequence("PlayerAttack", 0.1f, 1.f, false, false);
    mAnimation->AddSequence("PlayerReloading", 1.2f, 1.f, false, false);
    mAnimation->AddSequence("PlayerCoverHit", 0.33f, 1.f, false, false);
    mAnimation->AddSequence("PlayerStanceHit", 0.33f, 1.f, false, false);
    mAnimation->AddSequence("PlayerCoverToStance", 0.33f, 1.f, false, false);
    mAnimation->AddSequence("PlayerStanceToCover", 0.33f, 1.f, false, false);

    // 애니메이션의 마지막 프레임 동작 후 부가적인 이벤트 실행 (부가적 이벤트 : AttackEnd)
    //mAnimation->SetEndFunction<CPlayerObject>("PlayerAttack",
    //    this, &CPlayerObject::ActionEnd);
    
    // 애니메이션의 부가적인 이벤트를 추가 및 실행. (부가적 이벤트 : AttackNotify함수)
    //mAnimation->SetLoop("PlayerAttack", true);
    mAnimation->AddNotify<CPlayerObject>("PlayerAttack",
        1, this, &CPlayerObject::AttackNotify);
    
    // 장전 모션 끝난 후 이벤트 설정
    mAnimation->SetEndFunction<CPlayerObject>("PlayerReloading",
        this, &CPlayerObject::ReloadingEnd);

    mAnimation->SetEndFunction<CPlayerObject>("PlayerCoverToStance",
        this, &CPlayerObject::CoverToStanceEnd);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerStanceToCover",
        this, &CPlayerObject::StanceToCoverEnd);

    mAnimation->SetEndFunction<CPlayerObject>("PlayerCoverHit",
        this, &CPlayerObject::CoverHitEnd);
    mAnimation->SetEndFunction<CPlayerObject>("PlayerStanceHit",
        this, &CPlayerObject::StanceHitEnd);

    mRoot->SetWorldPos(0.f, -200.f, 0.f);
    mRoot->SetWorldScale(300.f, 300.f, 1.f);

    SetRootComponent(mRoot);
    
    mBody->SetCollisionProfile("Player");
    mBody->SetBoxSize(200.f, 300.f);
    //mBody->SetRadius(50.f);

    mRoot->AddChild(mBody);

    //mRoot->AddChild(mLine);

    mRoot->SetRenderLayerName("Object");

    // 카메라 최종 세팅타입 : 직교 투영 방식
    // 원근 투영방식 다시는 보지말자 시부레 
    mCamera->SetProjectionType(ECameraProjectionType::Ortho);

    //mCamera->SetRelativePos(0.f, 200.f, -400.f);
    mCamera->SetRelativePos(0.f, 200.f, 0.f);

    mRoot->AddChild(mCamera);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(200.f);

    mRotation->SetUpdateComponent(mRotationPivot);

    mRotation->SetVelocityInit(false);

    mRotation->SetMoveZ(360.f);

    /*
    mRoot->AddChild(mRotationPivot);
    mRotationPivot->AddChild(mSub);
    mRotationPivot->AddChild(mSub2);

    mSub->SetTexture("Teemo", TEXT("Texture/teemo.png"));
    mSub->SetPivot(0.5f, 0.5f);
    mSub->SetWorldScale(50.f, 50.f, 1.f);
    mSub->SetRelativePos(100.f, 0.f, 0.f);

    mSub2->SetTexture("Teemo", TEXT("Texture/teemo.png"));
    mSub2->SetPivot(0.5f, 0.5f);
    mSub2->SetRelativeScale(0.5f, 0.5f, 1.f);
    mSub2->SetRelativePos(-100.f, 0.f, 0.f);

    mScene->GetInput()->AddBindKey("MoveUp", 'W');
    mScene->GetInput()->AddBindKey("MoveDown", 'S');

    mScene->GetInput()->AddBindKey("RotationZ", 'D');
    mScene->GetInput()->AddBindKey("RotationZInv", 'A');

    mScene->GetInput()->AddBindKey("MoveRight", 'D');
    mScene->GetInput()->AddBindKey("MoveLeft", 'A');
    mScene->GetInput()->AddBindKey("MovePoint", VK_RBUTTON);
    */
    mScene->GetInput()->AddBindKey("MoveUp", 'W');
    mScene->GetInput()->AddBindKey("MoveDown", 'S');

    mScene->GetInput()->AddBindKey("MouseFire", VK_LBUTTON);

    mScene->GetInput()->AddBindKey("Skill8", '8');

    mScene->GetInput()->AddBindKey("Reloading", mReloadingKey);

#ifdef _DEBUG
    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveUp",
        EInputType::Hold, this, &CPlayerObject::MoveUp);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveDown",
        EInputType::Hold, this, &CPlayerObject::MoveDown);
#endif
    //mScene->GetInput()->AddBindFunction<CPlayerObject>("MouseFire",
    //    EInputType::Hold, this, &CPlayerObject::MouseFire);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Reloading",
        EInputType::Hold, this, &CPlayerObject::Reloading);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill8",
        EInputType::Down, this, &CPlayerObject::Skill8);

    return true;
}

void CPlayerObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    // 왼클릭 중이고, 탄창이 남아있다면
    //if (mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton) &&
    //    mAmmo > 0)
    //{
    //    // 현재 상태를 Idle -> CoverToStance로
    //    if (mPlayerState == EPlayerState::Idle)
    //        ChangeState(EPlayerState::CoverToStance);
    //    // 현재 상태를 CoverToStance -> Attack으로
    //    else if (mPlayerState == EPlayerState::CoverToStance)
    //        ChangeState(EPlayerState::Attack);
    //}
    // 현재 상태를 Attack -> StanceToCover로 변경한다.
    //else if (mPlayerState == EPlayerState::Attack)
    //    ChangeState(EPlayerState::StanceToCover);

    // 왼쪽클릭 누르는 중이고 탄창이 차있으면
    if (mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton) &&
        mAmmo > 0)
    {
        ChangeState(EPlayerState::CoverToStance);
    }

	LoopState(DeltaTime);
}

void CPlayerObject::Render()
{
    CSceneObject::Render();
}

/// <summary>
/// 자신 피격 기능
/// </summary>
/// <param name="Dmg"></param>
void CPlayerObject::Damage(int Dmg)
{
    mHP -= Dmg;
}

/// <summary>
/// 상대 오브젝트로 인한 자신 피격 기능
/// </summary>
/// <param name="Attack"></param>
/// <param name="Obj"></param>
/// <returns></returns>
float CPlayerObject::Damage(float Attack, CSceneObject* Obj)
{
    // 상대 Obj의 공격력을 Attack에 대입 후
    Attack = CSceneObject::Damage(Attack, Obj);
    // 플레이어의 HP를 깎는다.
    mHP -= (int)Attack;

    // 재장전 중 피격 애니메이션 무시
    if (mReloadState)
        return Attack;

    // 현재 상태에서 피격 애니메이션 설정
    if (mPlayerState == EPlayerState::StanceHit)
    {
        ChangeState(mPlayerState);
    }
    else if (mPlayerState == EPlayerState::CoverHit)
    {
        ChangeState(mPlayerState);
    }
    else
    {
        EPlayerState HitState =
            (mPlayerState == EPlayerState::Attack) ?
            EPlayerState::StanceHit : EPlayerState::CoverHit;

        ChangeState(HitState);
    }

    
    
    // 죽었을때 로직 추가 해줘야 함.

    // 공격 값을 반환
    return Attack;
}

/// <summary>
/// 1번만 실행 될 상태 변경 기능
/// </summary>
/// <param name="State"></param>
void CPlayerObject::ChangeState(EPlayerState State)
{
    if (mPlayerState == State)
        return;

    bool CanChange = true;

    // 4가지 중 1개라도 일치하면 true반환
    if ((mPlayerState == EPlayerState::CoverToStance ||
        mPlayerState == EPlayerState::StanceToCover) &&
        (State == EPlayerState::CoverHit ||
            State == EPlayerState::StanceHit))
        CanChange = false;

    if (!CanChange)
        return;

    // 장전 중일 때
    if (mReloadState)
    {
        if (mPlayerState == EPlayerState::Reloading)
        {
            // 재장전 자세가 아니면 전부 종료
            if (State != EPlayerState::Reloading)
            {
                CLog::PrintLog("재장전 중에는 자세를 변경할 수 없습니다.");
                // 장전을 계속 실행하도록 처리함.
                return;
            }
        }
    }

    // 피격 애니메이션을 받아왔다면
    if (State == EPlayerState::StanceHit)
    {
        if (mPlayerState == EPlayerState::Idle)
        {
            State = EPlayerState::CoverHit;
        }
        // 수정해줍시다.
        else if (mPlayerState == EPlayerState::StanceToCover ||
            mPlayerState == EPlayerState::CoverToStance)
            return;

        CLog::PrintLog("피격");
    }

    // 다르다면 이전 상태를 현재 상태로 변경 후
    // 현재 상태를 받은 상태로 변경
    mPlayerStatePrev = mPlayerState;
    mPlayerState = State;

    std::string str;
    str += "현재 자세 : ";
    str += DebugState();
    CLog::PrintLog(str);
    
    switch (mPlayerState)
    {
    case EPlayerState::Idle:
        IdleAnimation();            // 대기모션으로 변경
        break;
    case EPlayerState::Attack:
        AttackAnimation();          // 공격모션으로 변경  
        break;
    case EPlayerState::Reloading:
		ReloadingAnimation();       // 재장전모션으로 변경
        break;
    case EPlayerState::CoverToStance:
        CoverToStanceAnimation();   // 스탠스 자세로 변경
        break;
    case EPlayerState::StanceToCover:
        StanceToCoverAnimation();   // 커버 자세로 변경
        break;
    case EPlayerState::CoverHit:
		CoverHitAnimation();        // 커버히트모션으로 변경
        break;
    case EPlayerState::StanceHit:
		StanceHitAnimation();       // 스탠스히트모션으로 변경
        break;
    default:
        break;
    }
}

void CPlayerObject::LoopState(float DeltaTime)
{
    switch (mPlayerState)
    {
    case EPlayerState::Idle:
		// 동작할 기능이 굳이 없음 (애니메이션만 출력해주면 되기 때문)
        break;
    case EPlayerState::Attack:
		// 공격 애니메이션 실행시 동시실행하는 함수
        break;
    case EPlayerState::Reloading:
        break;
    case EPlayerState::CoverToStance:
        break;
    case EPlayerState::StanceToCover:
        break;
    case EPlayerState::CoverHit:
        break;
    case EPlayerState::StanceHit:
        break;
    default:
        break;
    }
}

void CPlayerObject::MoveUp(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y));

    mAnimation->ChangeAnimation("PlayerIdle");

}

void CPlayerObject::MoveDown(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * -1.f);

    mAnimation->ChangeAnimation("PlayerIdle");

}

void CPlayerObject::MovePoint(float DeltaTime)
{
    mMovement->SetMovePoint(
        mScene->GetInput()->GetMouseWorldPos2D());
}

void CPlayerObject::MoveRight(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X));

    //mAnimation->ChangeAnimation("PlayerIdle");

    //mAnimation->SetAnimationReverseX(false);
}

void CPlayerObject::MoveLeft(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1);

    //mAnimation->ChangeAnimation("PlayerIdle");

    //mAnimation->SetAnimationReverseX(true);
}

void CPlayerObject::Skill8(float DeltaTime)
{
    CBulletDot* Bullet = mScene->CreateObj<CBulletDot>("Bullet");

    Bullet->SetBulletCollisionProfile("PlayerAttack");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(300.f, 300.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 75.f);

    Bullet->SetBoxSize(300.f, 300.f);
}

void CPlayerObject::Reloading(float DeltaTime)
{
    // 탄창이 꽉 차있거나, 장전 상태에 돌입했다면 종료
    if (mAmmo == mAmmoMax || mReloadState)
        return;

    // Attack 상태에서 Reloading시도 시 StanceToCover
    // Attack Or StanceHit -> Reloading
    if(mPlayerState == EPlayerState::Attack ||
        mPlayerState == EPlayerState::StanceHit)
    {
        ChangeState(EPlayerState::StanceToCover);

        return;
    }

    // 대기모션이거나 또는 커버상태 피격 애니메이션이면
    // 재장전 자세로 변경
    if (mPlayerState == EPlayerState::Idle ||
        mPlayerState == EPlayerState::CoverHit)
    {
        mReloadState = true;
        ChangeState(EPlayerState::Reloading);
    }
}

#pragma region Animation 변경 이벤트 모음
void CPlayerObject::IdleAnimation()
{
    mAnimation->ChangeAnimation("PlayerIdle");
}

void CPlayerObject::AttackAnimation()
{
    if(mPlayerState == EPlayerState::Reloading)
        return;

    mAnimation->SetLoop("PlayerAttack", true);
    mAnimation->ChangeAnimation("PlayerAttack");
}

void CPlayerObject::ReloadingAnimation()
{
    mAnimation->ChangeAnimation("PlayerReloading");
}

void CPlayerObject::CoverHitAnimation()
{
    mAnimation->ChangeAnimation("PlayerCoverHit");
}

void CPlayerObject::StanceHitAnimation()
{
    mAnimation->ChangeAnimation("PlayerStanceHit");
}

void CPlayerObject::CoverToStanceAnimation()
{
    mAnimation->ChangeAnimation("PlayerCoverToStance");
}

void CPlayerObject::StanceToCoverAnimation()
{
    mAnimation->ChangeAnimation("PlayerStanceToCover");
}
#pragma endregion

/// <summary>
/// 공격 애니메이션 실행시 동시실행하는 함수
/// (총알의 생성, 이동)
/// </summary>
void CPlayerObject::AttackNotify()
{
    // 왼쪽 클릭 안하고 있거나,
    // 총알이 다떨어진 상태면,
    // 대기모션으로 변경 후 종료
    if (!mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton) ||
        mAmmo <= 0)
    {
        mAnimation->SetLoop("PlayerAttack", false);
        ChangeState(EPlayerState::StanceToCover);

        return;
    }
    
    // 왼쪽클릭하고 있고, 총알이 1발 이상 있을 경우
    // 1발 사용
    --mAmmo;

    // 왼쪽 버튼을 누르고 있다면
    // 총알을 생성.
    CHitScanBullet* HitScan = mScene->CreateObj<CHitScanBullet>("HitScan");
    HitScan->SetBulletCollisionProfile("PlayerAttack");

    CSceneComponent* Root = HitScan->GetRootComponent();

    // 마우스 좌표값을 받음
    FVector2D Pos = mScene->GetInput()->GetMouseWorldPos2D();

    // 크기 조정은 HitScan Init에서 하는 중.
    //Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos.x, Pos.y);
    HitScan->SetLifeTime(0.25f);

    // 출력
    //std::string str;
    //str += "<Mouse Position> x : ";
    //str += std::to_string(Pos.x);
    //str += ", y : ";
    //str += std::to_string(Pos.y);
    //CLog::PrintLog(str);
    //
}


/// <summary>
/// 대기 상태에서 피격 애니메이션이 끝난 후 실행
/// </summary>
void CPlayerObject::CoverHitEnd()
{
    ChangeState(mAmmo == 0 ? EPlayerState::Reloading : EPlayerState::Idle);

    //// 왼쪽클릭 안하고 있다면 대기상태로
    //if(!mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton))
    //    ChangeState(EPlayerState::Idle);
    //// 왼쪽 클릭을 하고 있다면 공격상태로
    //else
    //    if(mAmmo > 0)
    //        ChangeState(EPlayerState::Attack);

    CLog::PrintLog("커버 자세의 피격 애니메이션 종료");
}

/// <summary>
/// 공격 자세에서 피격 애니메이션이 끝난 후 실행
/// </summary>
void CPlayerObject::StanceHitEnd()
{
    // 왼쪽 클릭을 하고 있고 총알이 남아있으면 공격 상태로
    if (mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton) && mAmmo > 0)
    {
        //mAttackState = true;
        ChangeState(EPlayerState::Attack);
    }
    // 왼쪽 클릭을 안하고 있으면 대기 상태로
    else
    {
        //mAttackState = false;
        ChangeState(EPlayerState::StanceToCover);
    }
    
    CLog::PrintLog("사격 자세의 피격 애니메이션 종료");
    //PostureChange(EPostureState::Stance);
}

void CPlayerObject::CoverToStanceEnd()
{
    // 커버상태에서 스탠스 상태로 가는 애니메이션이 끝나고
    // 왼클 하고 있는 상태면
    // Attack Animation이 실행되도록 설정
    if (mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton) &&
        mAmmo > 0)
    {
        ChangeState(EPlayerState::Attack);
    }
    // 만약 마우스가 올라가있는 상태면 다시 대기 애니메이션으로 설정
    else
    {
        //mAttackState = false;
        ChangeState(EPlayerState::StanceToCover);
    }

    //if (mHP <= 0)
    //    Destroy();
}

void CPlayerObject::StanceToCoverEnd()
{
    // 스탠스상태에서 커버 상태로 가는 애니메이션이 끝났을 때
    // 현재 탄창이 0발일경우 Reloading으로 설정
    if (mAmmo <= 0)
    {
        CLog::PrintLog("재장전을 활성화 합니다.");

        mReloadState = true;
        ChangeState(EPlayerState::Reloading);
    }
    // 탄창이 남아있다면
    // Idle Animation이 실행되도록 설정
    else
    {
        ChangeState(EPlayerState::Idle);
    }

}

void CPlayerObject::ReloadingEnd()
{
    mAmmo = mAmmoMax;
    mReloadState = false;

    ChangeState(EPlayerState::Idle);
}

std::string CPlayerObject::DebugState()
{
    switch (mPlayerState)
    {
    case EPlayerState::Idle:
        return "Idle 상태";
    case EPlayerState::Attack:
        return "Attack 상태";
    case EPlayerState::Reloading:
        return "Reloading 상태";
        break;
    case EPlayerState::CoverToStance:
        return "CoverToStance 상태";
        break;
    case EPlayerState::StanceToCover:
        return "StanceToCover 상태";
        break;
    case EPlayerState::CoverHit:
        return "CoverHit 상태";
        break;
    case EPlayerState::StanceHit:
        return "StanceHit 상태";
        break;
    default:
        break;
    }
}
