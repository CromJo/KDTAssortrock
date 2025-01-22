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
    // ��ų������Ʈ�� nullptr�� ���
    if (!mSkill1Object)
    {
        // Bullet�̶� �̸����� ���� (�ӵ��� 0���� �ʱ�ȭ)
        mSkill1Object = mScene->CreateObj<CBulletObject>("Bullet");
        mSkill1Object->SetSpeed(0.f);
    }
    // �θ��� �����ǰ� ���� ������ �´�.
    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);
    // ��ų������Ʈ�� �θ��� ȸ���� �������� �־��ش�. 
    mSkill1Object->GetRootComponent()->SetWorldRotation(mRoot->GetWorldRotation());
    mSkill1Object->GetRootComponent()->SetWorldPos(Pos + Dir);
    // ������� ũ�⸦ Ű���ֱ� ���� ������ ���� ������´�.
    FVector3D   Scale = mSkill1Object->GetRootComponent()->GetWorldScale();
    // �������� �����ش�.
    Scale.x += DeltaTime * 0.5f;
    Scale.y += DeltaTime * 0.5f;
    // ������ �ִ�ġ�� �����Ѵ�.
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
