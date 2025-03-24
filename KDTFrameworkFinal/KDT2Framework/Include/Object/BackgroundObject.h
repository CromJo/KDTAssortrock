#pragma once
#include "SceneObject.h"

class CBackgroundObject :
    public CSceneObject
{
    friend class CScene;

protected:
    CBackgroundObject();
    CBackgroundObject(const CBackgroundObject& Obj);
    CBackgroundObject(CBackgroundObject&& Obj);
    virtual ~CBackgroundObject();

protected:
    CSharedPtr<class CSpriteComponent>  mRoot;
public:
    virtual bool Init();
};

