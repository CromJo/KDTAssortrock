#include "FloorDotBullet.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "MonsterObject.h"
#include "../Scene/Scene.h"
#include "../Share/Log.h"

CFloorDotBullet::CFloorDotBullet()
{
}

CFloorDotBullet::CFloorDotBullet(const CFloorDotBullet& Obj):
    CSceneObject(Obj)
{
}

CFloorDotBullet::CFloorDotBullet(CFloorDotBullet&& Obj) :
    CSceneObject(Obj)
{
}

CFloorDotBullet::~CFloorDotBullet()
{
}

bool CFloorDotBullet::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    mMovement = CreateComponent<CMovementComponent>();
    
    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(300.f, 300.f, 1.f);    // ũ�� ����
    
    SetRootComponent(mRoot);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveAxis(EAxis::Y);
    mMovement->SetMoveSpeed(300.f);
    
    return true;
}

void CFloorDotBullet::Update(float DeltaTime)
{
    // �� ������Ʈ ����
    CSceneObject::Update(DeltaTime);

    mDistance -= mMovement->GetMoveDistance();

    if (mDistance <= 0.f)
    {
        mDuration -= DeltaTime;

        if (mDuration <= 0.f)
            Destroy();

        mMovement->SetEnable(false);

        std::list<CSharedPtr<CMonsterObject>> MonsterList;

        mScene->FindObjectsFromType<CMonsterObject>(MonsterList);

        auto iter = MonsterList.begin();
        auto iterEnd = MonsterList.end();

        for (; iter != iterEnd; ++iter)
        {
            // ���� ������ ��ġ �� �޾ƿ���
            FVector3D Pos = (*iter)->GetWorldPosition();
            // ���� ��ġ���� Floor Bullet�� �Ÿ��� ���
            float Distance = Pos.Distance(GetWorldPosition());

            // Floor Bullet �����ȿ� ������ ����
            if (Distance <= mRange)
            {
                switch (mBulletType)
                {
                case EFloorType::Floor:
                    mDuration -= DeltaTime;

                    if (mDuration <= 0)
                    {
                        mDuration += 1.f;

                        (*iter)->Damage(1.f, this);

                        CLog::PrintLog("1Damage! \tMonster Current HP : " + (*iter)->GetHP());
                    }

                    break;
                }
            }
        }
    }

}
