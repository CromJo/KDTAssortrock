#pragma once

#include "EnemyObject.h"

class CNearingEnemy :
    public CEnemyObject
{
    friend class CScene;

protected:
    CNearingEnemy();
    CNearingEnemy(const CNearingEnemy& Obj);
    CNearingEnemy(CNearingEnemy&& Obj);
    virtual ~CNearingEnemy();

protected:
    float       mAttackTime = 0.5f;
    float       mDetectAngle = 45.f;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

