#include "ObjectSpawnPoint.h"
#include "../Component/SceneComponent.h"
#include "PlayerObject.h"
#include "BulletObject.h"
#include "GravityBullet.h"
#include "TalonR.h"
#include "TornadoBullet.h"
#include "NormalEnemy.h"
#include "NearingEnemy.h"
#include "../Scene/Scene.h"

CObjectSpawnPoint::CObjectSpawnPoint()
{
}

CObjectSpawnPoint::CObjectSpawnPoint(const CObjectSpawnPoint& Obj)  :
    CSceneObject(Obj)
{
}

CObjectSpawnPoint::CObjectSpawnPoint(CObjectSpawnPoint&& Obj) :
    CSceneObject(Obj)
{
}

CObjectSpawnPoint::~CObjectSpawnPoint()
{
}

bool CObjectSpawnPoint::Init()
{
    mRoot = CreateComponent<CSceneComponent>();

    SetRootComponent(mRoot);

    return true;
}

void CObjectSpawnPoint::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    if (mImmediateSpawn)
    {
        mImmediateSpawn = false;
        Spawn();
    }

    else
    {
        switch (mSpawnLoopType)
        {
        // 생성된 오브젝트가 없을 경우에만 생성
        case EObjectSpawnLoopType::Once:
            if (!mSpawnObject)
            {
                // 하나가 생성되고 시간이 지났다면
                if (ComputeSpawnTime(DeltaTime))
                {
                    mTime = 0.f;
                }
            }
            break;
        // 생성된 오브젝트 상관없이 계속 생성
        case EObjectSpawnLoopType::Loop:
            ComputeSpawnTime(DeltaTime);
            break;
        }
    }
}

bool CObjectSpawnPoint::ComputeSpawnTime(float DeltaTime)
{
    if (mSpawnTime == 0.f)
    {
        Spawn();

        return true;
    }

    mTime += DeltaTime;

    // 스폰해야 할 시간이 되었을 경우
    if (mTime >= mSpawnTime)
    {
        mTime -= mSpawnTime;

        Spawn();

        return true;
    }

    return false;
}

void CObjectSpawnPoint::ComputeSpawnCountType()
{
    switch (mSpawnCountType)
    {
    case EObjectSpawnCountType::OnceDestroy:
        Destroy();
        break;
    case EObjectSpawnCountType::CountDestroy:
        --mDestroySpawnCount;

        if (mDestroySpawnCount <= 0)
            Destroy();
        break;
    }
}

/// <summary>
/// 오브젝트 생성 기능
/// 1. 특정 오브젝트를 받아서,
///     그 오브젝트의 리스폰지점에
///     생성해주는 기능
/// 2. 위치, 회전, 그려줄 순위를 지정해준다.
/// </summary>
void CObjectSpawnPoint::Spawn()
{
    switch (mSpawnType)
    {
    case EObjectSpawnType::Player:
        mSpawnObject = mScene->CreateObj<CPlayerObject>("Player");
        break;
    case EObjectSpawnType::Bullet:
        mSpawnObject = mScene->CreateObj<CBulletObject>("Bullet");
        break;
    case EObjectSpawnType::GravityBullet:
        mSpawnObject = mScene->CreateObj<CGravityBullet>("GravityBullet");
        break;
    case EObjectSpawnType::TalonR:
        mSpawnObject = mScene->CreateObj<CTalonR>("TalonR");
        break;
    case EObjectSpawnType::TornadoBullet:
        mSpawnObject = mScene->CreateObj<CTornadoBullet>("TornadoBullet");
        break;
    case EObjectSpawnType::NormalEnemy:
        mSpawnObject = mScene->CreateObj<CNormalEnemy>("NormalEnemy");
        break;
    case EObjectSpawnType::NearingEnemy:
        mSpawnObject = mScene->CreateObj<CNearingEnemy>("NearingEnemy");
        break;
    }

    // Transform값 세팅 및 Layer 설정
    mSpawnObject->SetWorldRotation(GetWorldRotation());
    //mSpawnObject->SetWorldPos(0.f,0.f,-10.f);
    //FVector3D A = FVector3D(GetWorldPosition().x, GetWorldPosition().y, -200.f);
    mSpawnObject->SetWorldPos(GetWorldPosition());
    mSpawnObject->GetRootComponent()->SetRenderLayerName(mSpawnObject->GetName());
    
    mSpawnObject->SetSpawnPoint(this);

    ComputeSpawnCountType();
}
