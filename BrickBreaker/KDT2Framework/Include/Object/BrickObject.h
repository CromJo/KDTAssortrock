#pragma once

#include "SceneObject.h"

class CBrickObject :
    public CSceneObject
{
    friend class CScene;

protected:
    CBrickObject();
    CBrickObject(const CBrickObject& Obj);
    CBrickObject(CBrickObject&& Obj);
    virtual ~CBrickObject();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    //CSharedPtr<class CColliderAABB2D>       mBody;
    CSharedPtr<class CColliderSphere2D>       mBody;
    //CSharedPtr<class CColliderOBB2D>       mBody;
    CSharedPtr<CSceneObject>  mTarget;

    float           mDetectDistance = 0.f;

    int             mHP = 5;

public:
    void SetTarget(class CSceneObject* Target)
    {
        mTarget = Target;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    virtual float Damage(float Attack, CSceneObject* Obj);

private:
    void CollisionBrick(const FVector3D& HitPoint,
        class CColliderBase* Dest);
    void CollisionBrickEnd(class CColliderBase* Dest);
};

