#pragma once
#include "SceneObject.h"

enum class EFloorType
{
    Floor       // ���� ����� ����
};

class CFloorDotBullet :
    public CSceneObject
{
    friend class CScene;

protected:
    CFloorDotBullet();
    CFloorDotBullet(const CFloorDotBullet& Obj);
    CFloorDotBullet(CFloorDotBullet&& Obj);
    virtual ~CFloorDotBullet();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<class CMovementComponent>    mMovement;
    EFloorType       mBulletType = EFloorType::Floor;
    float   mSpeed = 400.f;         // �Ѿ� �ӵ�
    float   mDistance = 150.f;      // �Ÿ�
    float   mRange = 500.f;         // ���� ����
    float   mDuration = 1.f;        // �����ð�

public:
    void SetSpeed(float Speed)
    {
        mSpeed = Speed;
    }

    void SetGravityType(EFloorType Type)
    {
        mBulletType = Type;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};
