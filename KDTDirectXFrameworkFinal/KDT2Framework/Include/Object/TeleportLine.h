#pragma once
#include "SceneObject.h"

class CTeleportLine : public CSceneObject
{
    friend class CScene;

protected:
    CTeleportLine();
    CTeleportLine(const CTeleportLine& Obj);
    CTeleportLine(CTeleportLine&& Obj);
    virtual ~CTeleportLine();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<class CColliderLine2D>     mBody;
    //CSharedPtr<class CColliderLine2D>       mLine;
    CSharedPtr<class CStaticMeshComponent>  mSub;
    CSharedPtr<class CStaticMeshComponent>  mSub2;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Damage(int Dmg);
};

