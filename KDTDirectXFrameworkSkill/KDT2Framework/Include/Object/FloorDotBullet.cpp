#include "FloorDotBullet.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "MonsterObject.h"
#include "../Scene/Scene.h"
#include "../Share/Log.h"

CFloorDotBullet::CFloorDotBullet()
{
}

CFloorDotBullet::CFloorDotBullet(const CFloorDotBullet& Obj) :
    CBulletObject(Obj)
{
}

CFloorDotBullet::CFloorDotBullet(CFloorDotBullet&& Obj) :
    CBulletObject(Obj)
{
}

CFloorDotBullet::~CFloorDotBullet()
{
}

bool CFloorDotBullet::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    mBody = CreateComponent<CColliderOBB2D>();
    mMovement = CreateComponent<CMovementComponent>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    //mRoot->SetWorldScale(300.f, 300.f, 1.f);    // 크기 설정

    SetRootComponent(mRoot);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveAxis(EAxis::Y);
    mMovement->SetMoveSpeed(300.f);

    return true;
}

void CFloorDotBullet::Update(float DeltaTime)
{
    // 씬 업데이트 실행
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
            // 현재 몬스터의 위치 값 받아오기
            FVector3D Pos = (*iter)->GetWorldPosition();
            // 몬스터 위치값과 Floor Bullet의 거리를 계산
            float Distance = Pos.Distance(GetWorldPosition());

            // Floor Bullet 범위안에 들어오면 실행
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
                        std::string ErrMSG = "1Damage! \tMonster Current HP : ";
                        ErrMSG += std::to_string((*iter)->GetHP());
                        CLog::PrintLog(ErrMSG);
                    }

                    break;
                }
            }
        }
    }

}
