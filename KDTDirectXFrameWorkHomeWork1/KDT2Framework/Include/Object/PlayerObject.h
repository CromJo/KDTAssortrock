#pragma once

#include "SceneObject.h"

class CPlayerObject :
    public CSceneObject
{
    friend class CScene;

protected:
    CPlayerObject();
    CPlayerObject(const CPlayerObject& Obj);
    CPlayerObject(CPlayerObject&& Obj);
    virtual ~CPlayerObject();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<class CSceneComponent>       mRotationPivot;
    CSharedPtr<class CStaticMeshComponent>  mSub;
    CSharedPtr<class CStaticMeshComponent>  mSub2;

    CSharedPtr<class CBulletObject> mSkill1Object;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    const CSharedPtr<class CStaticMeshComponent>& GetRoot()    const
    {
        return mRoot;
    }

private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);

    void RotationZ(float DeltaTime);
    void RotationZInv(float DeltaTime);

    void Fire(float DeltaTime);

    void Skill1(float DeltaTime);
    void Skill1Fire(float DeltaTime);
};