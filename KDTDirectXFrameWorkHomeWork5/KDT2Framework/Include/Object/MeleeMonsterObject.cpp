#include "MeleeMonsterObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"


CMeleeMonsterObject::CMeleeMonsterObject()
{
}

CMeleeMonsterObject::CMeleeMonsterObject(const CMeleeMonsterObject& Obj)
	: CSceneObject(Obj)
{
}

CMeleeMonsterObject::CMeleeMonsterObject(CMeleeMonsterObject&& Obj)
	: CSceneObject(Obj) 
{
}

CMeleeMonsterObject::~CMeleeMonsterObject()
{
}

bool CMeleeMonsterObject::Init()
{
    // ������Ʈ
    mRoot = CreateComponent<CStaticMeshComponent>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);

    return true;
}

void CMeleeMonsterObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);            // �� ������Ʈ ������Ʈ

    // Ÿ���� �����ϴ��� üũ
    if (!mTarget->IsActive())
        mTarget = nullptr;

    // Ÿ���� Ȱ��ȭ �Ǿ��ִ��� üũ
    else if (mTarget->IsEnable())
    {
        /*FVector3D   ViewDir = mTarget->GetWorldPosition() -
            GetWorldPosition();
        ViewDir.Normalize();

        float Angle = FVector3D::Axis[EAxis::Y].GetAngle(ViewDir);*/
        float Angle = GetWorldPosition().GetViewTargetAngle(
            mTarget->GetWorldPosition());

        SetWorldRotationZ(Angle);
    }

    mFireTime -= DeltaTime;

    if (mFireTime <= 0.f)
    {
        mFireTime += 0.5f;                              // ���� ��Ÿ��

        CBulletObject* MeleeAttack = mScene->CreateObj<CBulletObject>("Bullet");

        CSceneComponent* Root = MeleeAttack->GetRootComponent();    // ���� ��� ����

        FVector3D Pos = mRoot->GetWorldPosition();                  // �������� ������ ����
        FVector3D Dir = mRoot->GetAxis(EAxis::Y);                   // �������� 

        Root->SetWorldScale(100.f, 35.f);                           // ���� ũ�� ����
        Root->SetWorldRotation(mRoot->GetWorldRotation());          // ���� ȸ���� �������Ϳ� �����ϰ� ����
        Root->SetWorldPos(Pos + Dir * 75.f);                        // ���� ��ġ �������� ���� ������ ����

        MeleeAttack->SetLifeTime(0.5f);                             // ���ݸ��� ����Ʈ �ð�
    }
}
