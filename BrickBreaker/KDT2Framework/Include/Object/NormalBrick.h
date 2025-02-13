#pragma once
#include "BrickObject.h"
class CNormalBrick :
    public CBrickObject
{
    friend class CScene;

protected:
    CNormalBrick();
    CNormalBrick(const CNormalBrick& Obj);
    CNormalBrick(CNormalBrick&& Obj);
    virtual ~CNormalBrick();

protected:
    float       mFireTime = 1.f;
    int         mFireCount = 0;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

