#pragma once
#include "SceneObject.h"

class CHitScanBullet :
    public CSceneObject
{
    friend class CScene;

protected:
    CHitScanBullet();
    CHitScanBullet(const CHitScanBullet& Obj);
    CHitScanBullet(CHitScanBullet&& Obj);
    virtual ~CHitScanBullet();

protected:
    CSharedPtr<class CSpriteComponent>  mRoot;
    CSharedPtr<class CColliderAABB2D>       mBody;

    void SetBulletCollisionProfile(const std::string& Name);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void CollisionBullet(const FVector3D& HitPoint,
        class CColliderBase* Dest);
};

