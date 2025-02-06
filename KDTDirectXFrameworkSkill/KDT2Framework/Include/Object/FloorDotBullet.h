#pragma once
#include "BulletObject.h"

enum class EFloorType
{
    Floor       // ���� ����� ����
};

class CFloorDotBullet :
    public CBulletObject
{
    friend class CScene;

protected:
    CFloorDotBullet();
    CFloorDotBullet(const CFloorDotBullet& Obj);
    CFloorDotBullet(CFloorDotBullet&& Obj);
    virtual ~CFloorDotBullet();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<class CColliderOBB2D>        mBody;
    CSharedPtr<class CMovementComponent>    mMovement;
    EFloorType       mBulletType = EFloorType::Floor;
    float   mSpeed = 400.f;         // �Ѿ� �ӵ�
    float   mDistance = 400.f;      // �Ÿ�
    float   mRange = 500.f;         // ���� ����
    float   mDuration = 1.f;        // �����ð�

public:
    void SetSpeed(float Speed)
    {
        mSpeed = Speed;
    }

    void SetBulletType(EFloorType Type)
    {
        mBulletType = Type;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};
