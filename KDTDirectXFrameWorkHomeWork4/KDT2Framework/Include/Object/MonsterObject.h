#pragma once
#include "SceneObject.h"

class CStaticMeshComponent;
class CSceneComponent;
class CMovementComponent;

class CMonsterObject : public CSceneObject
{
    friend class CScene;

protected:
    CMonsterObject();
    CMonsterObject(const CMonsterObject& Obj);
    CMonsterObject(CMonsterObject&& Obj);
    virtual ~CMonsterObject();

protected:
    CSharedPtr<CStaticMeshComponent>  mRoot;
    CSharedPtr<CSceneComponent>       mRotationPivot;
    CSharedPtr<CMovementComponent>    mMovement;

    float           mPivotRotationSpeed = 180.f;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);

    void RotationZ(float DeltaTime);
    void RotationZInv(float DeltaTime);

    void Fire(float DeltaTime);
};
