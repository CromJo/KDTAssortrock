#include "PlayerObject.h"
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

bool CPlayerObject::Init()
{
    //__super::Init();
    CSceneObject::Init();

    //mRoot = CreateComponent<CStaticMeshComponent>();
    mRoot = CreateComponent<CSpriteComponent>("Player");
    //mBody = CreateComponent<CColliderAABB2D>();
    //mBody = CreateComponent<CColliderSphere2D>();
    mBody = CreateComponent<CColliderOBB2D>();
    mLine = CreateComponent<CColliderLine2D>();
    mRotationPivot = CreateComponent<CSceneComponent>();
    mSub = CreateComponent<CSpriteComponent>();
    mSub2 = CreateComponent<CSpriteComponent>();
    mCamera = CreateComponent<CCameraComponent>();
    mHPBar = CreateComponent<CWidgetComponent>();

    mHPBar->SetRelativePos(-75.f, 150.f);
    CHeadInfo* HeadInfo = mScene->GetUIManager()->CreateWidget<CHeadInfo>("HeadInfo");
    mHPBar->SetWidget(HeadInfo);

    mRoot->AddChild(mHPBar);

    mMovement = CreateComponent<CMovementComponent>();
    mRotation = CreateComponent<CRotationComponent>();
    mInventory = CreateComponent<CInventoryComponent>();

    mRoot->SetTexture("Teemo", TEXT("Texture/teemo.png"));
    mRoot->SetPivot(0.5f, 0.5f);

    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

    mAnimation->AddSequence("PlayerIdle", 2.5f, 1.f, true, false);
    mAnimation->AddSequence("PlayerAttack", 0.1f, 1.f, false, false);
    mAnimation->AddSequence("PlayerReloading", 1.2f, 1.f, false, false);

    // 애니메이션의 마지막 프레임 동작 후 부가적인 이벤트 실행 (부가적 이벤트 : AttackEnd)
    //mAnimation->SetEndFunction<CPlayerObject>("PlayerAttack",
    //    this, &CPlayerObject::ActionEnd);
    // 애니메이션의 부가적인 이벤트를 추가 및 실행. (부가적 이벤트 : AttackNotify함수)
    mAnimation->SetLoop("PlayerAttack", true);
    mAnimation->AddNotify<CPlayerObject>("PlayerAttack",
        1, this, &CPlayerObject::AttackNotify);
    
    // 장전 모션 끝난 후 이벤트 설정
    mAnimation->SetEndFunction<CPlayerObject>("PlayerReloading",
        this, &CPlayerObject::ReloadingEnd);

    mRoot->SetWorldPos(0.f, -200.f, 0.f);
    mRoot->SetWorldScale(300.f, 300.f, 1.f);

    SetRootComponent(mRoot);
    
    mBody->SetCollisionProfile("Player");
    mBody->SetBoxSize(200.f, 300.f);
    //mBody->SetRadius(50.f);

    mRoot->AddChild(mBody);

    mRoot->AddChild(mLine);

    mRoot->SetRenderLayerName("Object");

    // Default
    mLine->SetCollisionProfile("Player");
    mLine->SetRelativePos(0.f, 50.f);
    mLine->SetLineDistance(300.f);

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

    mScene->GetInput()->AddBindKey("Fire", VK_SPACE);
    mScene->GetInput()->AddBindKey("MouseFire", VK_LBUTTON);

    mScene->GetInput()->AddBindKey("Reloading", 'R');
    mScene->GetInput()->AddBindKey("Skill8", '8');

    /*
    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveUp",
        EInputType::Hold, this, &CPlayerObject::MoveUp);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveDown",
        EInputType::Hold, this, &CPlayerObject::MoveDown);
    
    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveRight",
        EInputType::Hold, this, &CPlayerObject::MoveRight);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveLeft",
        EInputType::Hold, this, &CPlayerObject::MoveLeft);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MovePoint",
        EInputType::Down, this, &CPlayerObject::MovePoint);
        
    mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZ",
        EInputType::Hold, this, &CPlayerObject::RotationZ);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZInv",
        EInputType::Hold, this, &CPlayerObject::RotationZInv);*/

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MouseFire",
        EInputType::Hold, this, &CPlayerObject::MouseFire);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Fire",
        EInputType::Down, this, &CPlayerObject::Fire);
    
    mScene->GetInput()->AddBindFunction<CPlayerObject>("Reloading",
        EInputType::Down, this, &CPlayerObject::Reloading);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill8",
        EInputType::Down, this, &CPlayerObject::Skill8);

    return true;
}

void CPlayerObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    // 총알이 0발이고 대기모션인지 체크
    if (mAmmo <= 0 && mAutoBasePose)
    {
        //mAnimation->ChangeAnimation("PlayerReloading");
        Reloading(DeltaTime);

        //UpdateReloading(DeltaTime);
    }
    // 움직이지 않고, 디폴트 자세로 돌아가는 것이 켜져있다면, 
    // 기본자세로 돌려라
    else if (mMovement->GetVelocityLength() == 0.f && mAutoBasePose)
        ActionEnd();

    static bool ItemTest = false;

    // 엔터키 누르면 아이템 추가 테스트 ON
    if (GetAsyncKeyState(VK_RETURN) & 0x8000)
    {
        ItemTest = true;
    }

    // 만약 아이템 추가 기능이 켜진 상태면
    else if (ItemTest)
    {
        // 초기화해주고,
        ItemTest = false;
        // 두개의 이름을 데이터에 담는다.
        std::string NameArray[2] =
        {
            "IconSword",
            "IconShield"
        };
        // 랜덤번호를 대입해준다.
        int RandIndex = rand() % 2;
        // 데이터를 생성 및 대입해주고,
        FItemData* Data = new FItemData;

        // 랜덤한 번호의 아이템 이름을 데이터 이름에 대입해주고,
        Data->Name = NameArray[RandIndex];

        // 랜덤번호가 0번이라면 무기를,
        if (RandIndex == 0)
            Data->Type = EItemType::Weapon;
        // 1번이라면 방어구의 타입을 넣어준다.
        else if (RandIndex == 1)
            Data->Type = EItemType::Armor;

        // 씬이 null이 아니면 (존재한다면)
        // 아이템 타입에 맞는 이미지를 넣어준다.
        if (mScene)
            Data->Icon = mScene->GetAssetManager()->FindTexture(NameArray[RandIndex]);
        // 씬이 null이면 "응 어떻게든 넣을꺼야~"
        else
            Data->Icon = CAssetManager::GetInst()->GetTextureManager()->FindTexture(NameArray[RandIndex]);

        // 인벤토리에 데이터를 추가해준다.
        mInventory->AddItem(Data);
    }

    static bool ItemTest1 = false;

    // 0번 누르면 테스트 기능 활성화
    if (GetAsyncKeyState('0') & 0x8000)
    {
        ItemTest1 = true;
    }

    // 테스트 기능이 활성화 되었다면 인벤토리 1~10번째까지의 아이템중
    // 한개의 아이템을 제거한다.
    else if (ItemTest1)
    {
        ItemTest1 = false;

        mInventory->RemoveItem(rand() % 10);
    }
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

    // 공격 값을 반환
    return Attack;
}

void CPlayerObject::MoveUp(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y));

    mAnimation->ChangeAnimation("PlayerIdle");

    mAutoBasePose = true;
}

void CPlayerObject::MoveDown(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * -1.f);

    mAnimation->ChangeAnimation("PlayerIdle");

    mAutoBasePose = true;
}

void CPlayerObject::MovePoint(float DeltaTime)
{
    mMovement->SetMovePoint(
        mScene->GetInput()->GetMouseWorldPos2D());
}

void CPlayerObject::RotationZ(float DeltaTime)
{
    //FVector3D   Rot = mRootComponent->GetWorldRotation();
    //mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * -90.f);

    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X));

    mAnimation->ChangeAnimation("PlayerIdle");

    mAutoBasePose = true;

}

void CPlayerObject::RotationZInv(float DeltaTime)
{
    //FVector3D   Rot = mRootComponent->GetWorldRotation();
    //mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * 90.f);

    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1.f);

    mAnimation->ChangeAnimation("PlayerIdle");
    mAutoBasePose = true;
}

void CPlayerObject::MoveRight(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X));

    mAnimation->ChangeAnimation("PlayerIdle");

    mAnimation->SetAnimationReverseX(false);

    mAutoBasePose = true;
}

void CPlayerObject::MoveLeft(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1);

    mAnimation->ChangeAnimation("PlayerIdle");

    mAnimation->SetAnimationReverseX(true);

    mAutoBasePose = true;
}

// 공격 기능
void CPlayerObject::Fire(float DeltaTime)
{
    // PlayerAttack 애니메이션으로 변경
    mAnimation->ChangeAnimation("PlayerAttack");

    mAutoBasePose = false;
}

/// <summary>
/// 공격 기능
/// </summary>
/// <param name="DeltaTime"></param>
void CPlayerObject::MouseFire(float DeltaTime)
{
    // 왼쪽 클릭 안하고 있거나,
    // 총알이 다떨어진 상태면,
    // 대기모션으로 변경 후 종료
    // !mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton) ||
    if (mAmmo <= 0)
    {
        Reloading(DeltaTime);

        return;
    }


    // PlayerAttack 애니메이션으로 변경
    mAnimation->ChangeAnimation("PlayerAttack");

    mAutoBasePose = false;
}

/// <summary>
/// 재장전 기능 
/// 1. R버튼을 누를 때 실행
/// 2. 탄알이 0발 남았을 때 실행.
/// </summary>
/// <param name="DeltaTime"></param>
void CPlayerObject::Reloading(float DeltaTime)
{
    if (mAmmo == mAmmoMax)
        return;

    CLog::PrintLog("리로딩!!!");

    // 모든 조건이 부합하면 재장전 애니메이션을 실행
    mAnimation->ChangeAnimation("PlayerReloading");

    mAutoBasePose = false;              
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

/// <summary>
/// 모든 행동이 끝날 경우 실행되는 기능
/// 1. 대기모션으로 되돌립니다.
/// </summary>
void CPlayerObject::ActionEnd()
{
    // 애니메이션 변경 및 로그 남김 
    CLog::PrintLog("Action End");
    mAnimation->ChangeAnimation("PlayerIdle");

    mAutoBasePose = true;
}

/// <summary>
/// 공격 애니메이션 실행시 동시실행하는 함수
/// (총알의 생성, 이동)
/// </summary>
void CPlayerObject::AttackNotify()
{
    if (!mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton) ||
        mAmmo <= 0)
    {
        ActionEnd();

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

void CPlayerObject::ReloadingEnd()
{
    mAmmo = mAmmoMax;

    ActionEnd();
}
