#pragma once
#include "EnemyObject.h"
class CNormalEnemy :
    public CEnemyObject
{
    friend class CScene;

protected:
    CNormalEnemy();
    CNormalEnemy(const CNormalEnemy& Obj);
    CNormalEnemy(CNormalEnemy&& Obj);
    virtual ~CNormalEnemy();

protected:
    float       mFireTime = 1.f;
    int         mFireCount = 0;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

protected:
    virtual void DetectTarget();

protected:
    virtual void AIAttack();

protected:
    void AttackNotify();
    void AttackEnd();
    void SkillNotify();
    void SkillEnd();

    virtual FVector3D MovePoint() override;
};

