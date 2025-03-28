#pragma once
#include "EnemyObject.h"
class CNormalEnemy :
    public CEnemyObject
{
    friend class CScene;

private:
    EEnemyAI mMyAI = EEnemyAI::Idle;

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
    virtual void PreUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);

protected:
    virtual void DetectTarget();
    virtual void Move();

protected:
    virtual void AIAttack();
    virtual void MovePoint();

protected:
    void AttackNotify();
    void AttackEnd();
    void SkillNotify();
    //void SkillEnd();

    //virtual FVector3D MovePoint() override;
};

