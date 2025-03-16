#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "BulletObject.h"
#include "TornadoBullet.h"
#include "TalonR.h"
#include "GravityBullet.h"
#include "HitScanBullet.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "BulletDot.h"
#include "PenetrationBullet.h"
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

    mHPBar->SetRelativePos(-50.f, 50.f);

    //CProgressBar* HPBar = mScene->GetUIManager()->CreateWidget<CProgressBar>("HPBar");

    ////HPBar->SetPos(0.f, 100.f);
    ////HPBar->SetSize(50.f, 200.f);
    //HPBar->SetSize(200.f, 50.f);
    //HPBar->SetTint(EProgressBarImageType::Back, 0.3f, 0.3f, 0.3f);
    ////HPBar->SetOpacity(EProgressBarImageType::Fill, 0.4f);
    //HPBar->SetTexture(EProgressBarImageType::Fill, "HPBar",
    //    TEXT("Texture\\HPBar.png"));
    ////HPBar->SetBarDir(EProgressBarDir::TopToBottom);

    //HPBar->SetPercent(0.7f);

    //mHPBar->SetWidget(HPBar);
    CHeadInfo* HeadInfo = mScene->GetUIManager()->CreateWidget<CHeadInfo>("HeadInfo");

    mHPBar->SetWidget(HeadInfo);

    mRoot->AddChild(mHPBar);

    mMovement = CreateComponent<CMovementComponent>();
    mRotation = CreateComponent<CRotationComponent>();
    mInventory = CreateComponent<CInventoryComponent>();

    mRoot->SetTexture("Teemo", TEXT("Texture/teemo.png"));
    mRoot->SetPivot(0.5f, 0.5f);
    //mRoot->SetTint(1.f, 0.f, 0.f);
    //mRoot->SetMesh("CenterTexRect");
    //mRoot->AddTexture(0, "Teemo", TEXT("Texture/teemo.png"), 0);
    //mRoot->SetOpacity(0, 0.5f);
    //mRoot->SetBaseColor(0, 1.f, 0.f, 0.f, 1.f);
    //mRoot->SetShader("ColorMeshShader");

    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

    mAnimation->AddSequence("PlayerIdle", 1.f, 1.f, true, false);
    mAnimation->AddSequence("PlayerRun", 0.7f, 1.f, true, false);
    mAnimation->AddSequence("PlayerWalk", 0.7f, 1.f, true, false);
    mAnimation->AddSequence("PlayerAttack", 0.1f, 1.f, false, false);
    mAnimation->AddSequence("PlayerReloading", 1.2f, 1.f, false, false);

    // 애니메이션의 마지막 프레임 동작 후 부가적인 이벤트 실행 (부가적 이벤트 : AttackEnd)
    //mAnimation->SetEndFunction<CPlayerObject>("PlayerAttack",
    //    this, &CPlayerObject::AttackEnd);
    // 애니메이션의 부가적인 이벤트를 추가 및 실행. (부가적 이벤트 : AttackNotify함수)
    mAnimation->SetLoop("PlayerAttack", true);
    mAnimation->AddNotify<CPlayerObject>("PlayerAttack",
        2, this, &CPlayerObject::AttackNotify);
    // 반복 실행

    // 장전 모션 끝난 후 이벤트 설정
    mAnimation->SetEndFunction<CPlayerObject>("PlayerReloading",
        this, &CPlayerObject::AttackEnd);

    mRoot->SetWorldPos(0.f, 0.f, 0.f);
    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);
    
    mBody->SetCollisionProfile("Player");
    mBody->SetBoxSize(100.f, 100.f);
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
    mCamera->SetRelativePos(0.f, 0.f, 0.f);

    mRoot->AddChild(mCamera);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(200.f);

    mRotation->SetUpdateComponent(mRotationPivot);

    mRotation->SetVelocityInit(false);

    mRotation->SetMoveZ(360.f);

    mRoot->AddChild(mRotationPivot);
    mRotationPivot->AddChild(mSub);
    mRotationPivot->AddChild(mSub2);

    /*mSub->SetMesh("CenterRect");
    mSub->SetShader("ColorMeshShader");*/
    mSub->SetTexture("Teemo", TEXT("Texture/teemo.png"));
    mSub->SetPivot(0.5f, 0.5f);

    //mSub->SetRelativeScale(0.5f, 0.5f, 1.f);
    mSub->SetWorldScale(50.f, 50.f, 1.f);
    mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);

    mSub2->SetTexture("Teemo", TEXT("Texture/teemo.png"));
    mSub2->SetPivot(0.5f, 0.5f);
    /*mSub2->SetMesh("CenterRect");
    mSub2->SetShader("ColorMeshShader");*/

    mSub2->SetRelativeScale(0.5f, 0.5f, 1.f);
    mSub2->SetRelativePos(mSkill4Range, 0.f, 0.f);

    mScene->GetInput()->AddBindKey("MoveUp", 'W');
    mScene->GetInput()->AddBindKey("MoveDown", 'S');

    /*mScene->GetInput()->AddBindKey("RotationZ", 'D');
    mScene->GetInput()->AddBindKey("RotationZInv", 'A');*/

    mScene->GetInput()->AddBindKey("MoveRight", 'D');
    mScene->GetInput()->AddBindKey("MoveLeft", 'A');;
    mScene->GetInput()->AddBindKey("MovePoint", VK_RBUTTON);

    mScene->GetInput()->AddBindKey("Fire", VK_SPACE);
    mScene->GetInput()->AddBindKey("MouseFire", VK_LBUTTON);

    mScene->GetInput()->AddBindKey("Reloading", 'R');

    mScene->GetInput()->AddBindKey("Skill1", '1');
    mScene->GetInput()->ChangeKeyCtrl("Skill1", true);
    mScene->GetInput()->ChangeKeyShift("Skill1", true);

    mScene->GetInput()->AddBindKey("Skill2", '2');
    mScene->GetInput()->AddBindKey("Skill3", '3');
    mScene->GetInput()->AddBindKey("Skill4", '4');
    mScene->GetInput()->AddBindKey("Skill5", '5');
    mScene->GetInput()->AddBindKey("Skill6", '6');
    mScene->GetInput()->AddBindKey("Skill7", '7');
    mScene->GetInput()->AddBindKey("Skill8", '8');
    mScene->GetInput()->AddBindKey("Skill9", '9');

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



   /* mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZ",
        EInputType::Hold, this, &CPlayerObject::RotationZ);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZInv",
        EInputType::Hold, this, &CPlayerObject::RotationZInv);*/

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MouseFire",
        EInputType::Down, this, &CPlayerObject::MouseFire);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Fire",
        EInputType::Down, this, &CPlayerObject::Fire);
    
    mScene->GetInput()->AddBindFunction<CPlayerObject>("Reloading",
        EInputType::Down, this, &CPlayerObject::Reloading);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill1",
        EInputType::Hold, this, &CPlayerObject::Skill1);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill1",
        EInputType::Up, this, &CPlayerObject::Skill1Fire);


    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill2",
        EInputType::Down, this, &CPlayerObject::Skill2);


    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill3",
        EInputType::Down, this, &CPlayerObject::Skill3);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill4",
        EInputType::Down, this, &CPlayerObject::Skill4);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill5",
        EInputType::Down, this, &CPlayerObject::Skill5);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill6",
        EInputType::Down, this, &CPlayerObject::Skill6);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill7",
        EInputType::Down, this, &CPlayerObject::Skill7);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill8",
        EInputType::Down, this, &CPlayerObject::Skill8);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill9",
        EInputType::Down, this, &CPlayerObject::Skill9);

    return true;
}

void CPlayerObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    /*FVector3D Rot = mRotationPivot->GetRelativeRotation();

    Rot.z += DeltaTime * mPivotRotationSpeed;

    mRotationPivot->SetRelativeRotationZ(Rot.z);*/

    if (mSkill2Enable)
    {
        UpdateSkill2(DeltaTime);
    }

    if (mSkill4Enable)
    {
        UpdateSkill4(DeltaTime);
    }

    // 움직이지 않고, 디폴트 자세로 돌아가는 것이 켜져있다면, 
    // 기본자세로 돌려라
    if (mMovement->GetVelocityLength() == 0.f && mAutoBasePose)
        mAnimation->ChangeAnimation("PlayerIdle");

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

    mAnimation->ChangeAnimation("PlayerWalk");

    mAutoBasePose = true;
}

void CPlayerObject::MoveDown(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * -1.f);

    mAnimation->ChangeAnimation("PlayerWalk");

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

    mAnimation->ChangeAnimation("PlayerWalk");

    mAutoBasePose = true;

}

void CPlayerObject::RotationZInv(float DeltaTime)
{
    //FVector3D   Rot = mRootComponent->GetWorldRotation();
    //mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * 90.f);

    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1.f);

    mAnimation->ChangeAnimation("PlayerWalk");
    mAutoBasePose = true;
}

void CPlayerObject::MoveRight(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X));

    mAnimation->ChangeAnimation("PlayerWalk");

    mAnimation->SetAnimationReverseX(false);

    mAutoBasePose = true;
}

void CPlayerObject::MoveLeft(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1);

    mAnimation->ChangeAnimation("PlayerWalk");

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
    // PlayerAttack 애니메이션으로 변경
    mAnimation->ChangeAnimation("PlayerAttack");

    mAutoBasePose = false;
}

void CPlayerObject::Reloading(float DeltaTime)
{
    mAnimation->ChangeAnimation("PlayerReloading");

    mAutoBasePose = false;
}

void CPlayerObject::Skill1(float DeltaTime)
{
    if (!mSkill1Object)
    {
        mSkill1Object = mScene->CreateObj<CBulletObject>("Bullet");
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

    Bullet->SetBulletCollisionProfile("PlayerAttack");

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

    Bullet->SetBulletCollisionProfile("PlayerAttack");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 75.f);
}

void CPlayerObject::UpdateSkill2(float DeltaTime)
{
    mSkill2TimeAcc += DeltaTime;

    if (mSkill2TimeAcc >= mSkill2TimeInterval)
    {
        mSkill2TimeAcc -= mSkill2TimeInterval;

        CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

        CSceneComponent* Root = Bullet->GetRootComponent();

        FVector3D Pos = mSub->GetWorldPosition();
        FVector3D   Dir = mSub->GetAxis(EAxis::Y);

        Root->SetWorldRotation(mRoot->GetWorldRotation());
        Root->SetWorldPos(Pos + Dir);

        Bullet->SetLifeTime(1.f);

        Bullet = mScene->CreateObj<CBulletObject>("Bullet");

        Root = Bullet->GetRootComponent();

        Pos = mSub2->GetWorldPosition();
        Dir = mSub2->GetAxis(EAxis::Y);

        Root->SetWorldRotation(mRoot->GetWorldRotation());
        Root->SetWorldPos(Pos + Dir);

        Bullet->SetLifeTime(1.f);
    }

    mSkill2Time -= DeltaTime;

    if (mSkill2Time <= 0.f)
    {
        mSkill2Enable = false;
    }
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

        mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);

        mSub2->SetRelativePos(mSkill4Range, 0.f, 0.f);
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

        mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);

        mSub2->SetRelativePos(mSkill4Range, 0.f, 0.f);
        break;
    }

}

/// <summary>
/// 공격이 끝날 경우 실행되는 기능
/// </summary>
void CPlayerObject::AttackEnd()
{
    // 애니메이션 변경 및 로그 남김 
    CLog::PrintLog("AttackEnd");
    mAnimation->ChangeAnimation("PlayerIdle");
}

/// <summary>
/// 공격 애니메이션 실행시 동시실행하는 함수
/// (총알의 생성, 이동)
/// </summary>
void CPlayerObject::AttackNotify()
{
    // 콜라이더 생성 말고 그냥 클릭한 곳에 Collider 존재 시 대미지를 주도록 하면 될까?

    //CLog::PrintLog("Attack");
    //CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");
    //
    //// 불렛에 콜라이더 설정
    //Bullet->SetBulletCollisionProfile("PlayerAttack");
    //
    //// 불렛의 상위 컴포넌트는 이 씬의 컴포넌트로 만들고
    //CSceneComponent* Root = Bullet->GetRootComponent();
    //// 플레이어의 위치와 좌표값을 받아서
    //FVector3D Pos = mRoot->GetWorldPosition();
    //FVector3D Dir = mRoot->GetAxis(EAxis::Y);
    //
    //// 불렛의 이미지 트랜스폼값을 설정함
    //Root->SetWorldScale(250.f, 250.f);
    //Root->SetWorldRotation(mRoot->GetWorldRotation());
    //Root->SetWorldPos(Pos + Dir * 75.f);
    //
    //// N초 뒤 제거
    //Bullet->SetLifeTime(2.f);
    
    // 왼쪽 클릭 안하고 있으면 대기모션으로 변경 후 종료
    if(!mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton))
    {
        AttackEnd();

        return;
    }

    // 왼쪽 버튼을 누르고 있다면
    // 총알을 생성.
    CHitScanBullet* HitScan = mScene->CreateObj<CHitScanBullet>("HitScan");
    
    CSceneComponent* Root = HitScan->GetRootComponent();
    
    // 마우스 좌표값을 받음
    FVector2D Pos = mScene->GetInput()->GetMouseWorldPos2D();
    
    // 크기 조정은 HitScan Init에서 하는 중.
    //Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos.x, Pos.y);
    HitScan->SetLifeTime(0.1f);
    
    //
    //std::string str;
    //str += "<Mouse Position> x : ";
    //str += std::to_string(Pos.x);
    //str += ", y : ";
    //str += std::to_string(Pos.y);
    //CLog::PrintLog(str);
    //
}