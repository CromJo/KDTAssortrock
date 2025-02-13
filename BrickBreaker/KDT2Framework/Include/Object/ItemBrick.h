#pragma once

#include "BrickObject.h"

class CItemBrick :
    public CBrickObject
{
    friend class CScene;

protected:
    CItemBrick();
    CItemBrick(const CItemBrick& Obj);
    CItemBrick(CItemBrick&& Obj);
    virtual ~CItemBrick();

protected:
    float       mAttackTime = 0.5f;
    float       mDetectAngle = 45.f;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

