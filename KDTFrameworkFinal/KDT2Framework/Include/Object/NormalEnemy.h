#pragma once
#include "EnemyObject.h"
class CNormalEnemy :
    public CEnemyObject
{
    friend class CScene;

private:
    EEnemyAI mMyAI = EEnemyAI::Idle;
    CSharedPtr<class CSpriteComponent>        mGuageBar;
    CSharedPtr<class CGuageInfo>            mGuageInfo;

    class CAnimation2D* mGuageAnimation = nullptr;

    float mControlRatio = 0;

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
    // Animation Notify 작성용 칸
    virtual void AIAttack();
    virtual void MovePointNotify();     // 디테일용이기 때문에 제거 하자.

    virtual void AttackLoop(float DeltaTime);
    

protected:
    void AttackNotify();
    void AttackGuageEnd();
    void AttackEnd();
    void SkillNotify();
    void MovePointEnd();
    //void SkillEnd();

    //virtual FVector3D MovePoint() override;
};

