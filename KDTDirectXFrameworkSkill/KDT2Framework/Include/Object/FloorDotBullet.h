#pragma once
#include "BulletObject.h"

enum class EFloorType
{
    Floor       // 장판 대미지 실행
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
    float   mSpeed = 400.f;         // 총알 속도
    float   mDistance = 400.f;      // 거리
    float   mRange = 500.f;         // 장판 범위
    float   mDuration = 1.f;        // 지연시간

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
