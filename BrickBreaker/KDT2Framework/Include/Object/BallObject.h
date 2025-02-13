#pragma once

#include "SceneObject.h"
#include "../Component/MovementComponent.h"


class CBallObject :
    public CSceneObject
{
    friend class CScene;

protected:
    CBallObject();
    CBallObject(const CBallObject& Obj);
    CBallObject(CBallObject&& Obj);
    virtual ~CBallObject();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<class CColliderAABB2D>       mBody;
    CSharedPtr<CMovementComponent>    mMovement;

    float   mSpeed = 200.f;

    bool    isStart = false;        // 플레이어가 시작헀는지 체크

public:
    void SetSpeed(float Speed)
    {
        mSpeed = Speed;
    }

    void SetAlive(bool Alive)
    {
        isStart = Alive;
    }

    bool GetAlive()
    {
        return isStart;
    }

    void SetMovement(CSharedPtr<CMovementComponent> Movement)
    {
        mMovement = Movement;
    }

    CSharedPtr<CMovementComponent> GetMovement()
    {
        return mMovement;
    }

    void SetBallCollisionProfile(const std::string& Name);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);



private:
    void CollisionBall(const FVector3D& HitPoint,
        class CColliderBase* Dest);
};

