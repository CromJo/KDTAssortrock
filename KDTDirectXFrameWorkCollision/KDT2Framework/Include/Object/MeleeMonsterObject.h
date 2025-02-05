#pragma once
#include "SceneObject.h"

class CMeleeMonsterObject : public CSceneObject
{
    friend class CScene;

protected:
    CMeleeMonsterObject();
    CMeleeMonsterObject(const CMeleeMonsterObject& Obj);
    CMeleeMonsterObject(CMeleeMonsterObject&& Obj);
    virtual ~CMeleeMonsterObject();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<CSceneObject>  mTarget;
    float       mFireTime = 1.f;

public:
    void SetTarget(class CSceneObject* Target)
    {
        mTarget = Target;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

