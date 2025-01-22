#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "BulletObject.h"

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
    mRotationPivot = CreateComponent<CSceneComponent>();
    mSub = CreateComponent<CStaticMeshComponent>();
    mSub2 = CreateComponent<CStaticMeshComponent>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldPos(0.f, 0.f, 5.5f);

    SetRootComponent(mRoot);

    mRoot->AddChild(mRotationPivot);
    mRotationPivot->AddChild(mSub);
    mRotationPivot->AddChild(mSub2);

    mSub->SetMesh("CenterRect");
    mSub->SetShader("ColorMeshShader");

    mSub->SetRelativeScale(0.5f, 0.5f, 1.f);
    mSub->SetRelativePos(-2.f, 0.f, 0.f);

    mSub2->SetMesh("CenterRect");
    mSub2->SetShader("ColorMeshShader");

    mSub2->SetRelativeScale(0.5f, 0.5f, 1.f);
    mSub2->SetRelativePos(2.f, 0.f, 0.f);

    mScene->GetInput()->AddBindKey("MoveUp", 'W');
    mScene->GetInput()->AddBindKey("MoveDown", 'S');

    mScene->GetInput()->AddBindKey("RotationZ", 'D');
    mScene->GetInput()->AddBindKey("RotationZInv", 'A');

    mScene->GetInput()->AddBindKey("Fire", VK_SPACE);

    mScene->GetInput()->AddBindKey("Skill1", '1');

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveUp",
        EInputType::Hold, this, &CPlayerObject::MoveUp);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveDown",
        EInputType::Hold, this, &CPlayerObject::MoveDown);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZ",
        EInputType::Hold, this, &CPlayerObject::RotationZ);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZInv",
        EInputType::Hold, this, &CPlayerObject::RotationZInv);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Fire",
        EInputType::Down, this, &CPlayerObject::Fire);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill1",
        EInputType::Hold, this, &CPlayerObject::Skill1);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill1",
        EInputType::Up, this, &CPlayerObject::Skill1Fire);

    return true;
}

void CPlayerObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    FVector3D Rot = mRotationPivot->GetRelativeRotation();

    Rot.z += DeltaTime * 180.f;

    mRotationPivot->SetRelativeRotationZ(Rot.z);
}

void CPlayerObject::MoveUp(float DeltaTime)
{
    FVector3D   Pos = mRootComponent->GetWorldPosition();
    FVector3D   Dir = mRootComponent->GetAxis(EAxis::Y);

    mRootComponent->SetWorldPos(Pos + Dir * 3.f * DeltaTime);
}

void CPlayerObject::MoveDown(float DeltaTime)
{
    FVector3D   Pos = mRootComponent->GetWorldPosition();
    FVector3D   Dir = mRootComponent->GetAxis(EAxis::Y);

    mRootComponent->SetWorldPos(Pos + Dir * 3.f * -DeltaTime);
}

void CPlayerObject::RotationZ(float DeltaTime)
{
    FVector3D   Rot = mRootComponent->GetWorldRotation();
    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * 90.f);
}

void CPlayerObject::RotationZInv(float DeltaTime)
{
    FVector3D   Rot = mRootComponent->GetWorldRotation();
    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * -90.f);
}

void CPlayerObject::Fire(float DeltaTime)
{
    CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

    CSceneComponent* Root = Bullet->GetRootComponent();

    Root->SetWorldPos(mRoot->GetWorldPosition());

    Root->SetWorldRotation(mRoot->GetWorldRotation());
}

void CPlayerObject::Skill1(float DeltaTime)
{
    // 스킬오브젝트가 nullptr일 경우
    if (!mSkill1Object)
    {
        // Bullet이란 이름으로 생성 (속도는 0으로 초기화)
        mSkill1Object = mScene->CreateObj<CBulletObject>("Bullet");
        mSkill1Object->SetSpeed(0.f);
    }
    // 부모의 포지션과 축을 가지고 온다.
    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);
    // 스킬오브젝트에 부모의 회전과 포지션을 넣어준다. 
    mSkill1Object->GetRootComponent()->SetWorldRotation(mRoot->GetWorldRotation());
    mSkill1Object->GetRootComponent()->SetWorldPos(Pos + Dir);
    // 기모을때 크기를 키워주기 위한 스케일 값을 가지고온다.
    FVector3D   Scale = mSkill1Object->GetRootComponent()->GetWorldScale();
    // 스케일을 높여준다.
    Scale.x += DeltaTime * 0.5f;
    Scale.y += DeltaTime * 0.5f;
    // 스케일 최대치를 설정한다.
    if (Scale.x >= 4.f)
        Scale.x = 4.f;

    if (Scale.y >= 4.f)
        Scale.y = 4.f;

    mSkill1Object->GetRootComponent()->SetWorldScale(Scale);
    //mSkill1Object->GetRootComponent()->SetWorldRotationY(Dir.y);
}

void CPlayerObject::Skill1Fire(float DeltaTime)
{
    //FVector3D Rotation = mRoot->GetAxis(EAxis::Y);
    //mSkill1Object->GetRootComponent()->SetWorldRotationY(Rotation.y);
    mSkill1Object->SetSpeed(2.f);
    mSkill1Object = nullptr;
}
