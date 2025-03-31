#pragma once

#include "SceneObject.h"

enum class EEnemyAI : unsigned char
{
    Idle,
    //Trace,
    Move,
    //Patrol,
    Attack,
    //Death,
    //Skill,
    //Custom,
    End
};

enum class EEnemyMoveDirect : unsigned char
{
    None,       // 멈춘 상태
    Left,       // 왼쪽으로 이동 해야하는 상태
    Right       // 오른쪽으로 이동 해야하는 상태
};

class CEnemyObject :
    public CSceneObject
{
    friend class CScene;

protected:
    CEnemyObject();
    CEnemyObject(const CEnemyObject& Obj);
    CEnemyObject(CEnemyObject&& Obj);
    virtual ~CEnemyObject();

protected:

    CSharedPtr<class CSpriteComponent>  mRoot;
    //CSharedPtr<class CStaticMeshComponent>  mRoot;
    //CSharedPtr<class CColliderAABB2D>       mBody;
    CSharedPtr<class CColliderSphere2D>       mBody;
    //CSharedPtr<class CColliderOBB2D>       mBody;
    CSharedPtr<class CColliderSphere2D>       mDetect;
    CSharedPtr<CSceneObject>  mTarget;
    class CAnimation2D* mAnimation = nullptr;
    EEnemyAI          mAI = EEnemyAI::Idle;
    std::string         mAIAnimationName[(int)EEnemyAI::End];

    float           mDetectDistance = 0.f;

    int             mHP = 5;

    float           mLogicTime = 0.f;    // 로직 랜덤 체인지를 위한 시간

    CSharedPtr<class CMovementComponent>    mMovement;
    float           mSpeed = 200.f;
    EEnemyMoveDirect mMoveDirect = EEnemyMoveDirect::None;

    FVector3D       mSaveMoveData = FVector3D::Zero;

    
public:
    void SetTarget(class CSceneObject* Target)
    {
        mTarget = Target;
    }

public:
    virtual bool Init();
    virtual void PreUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);

public:
    virtual float Damage(float Attack, CSceneObject* Obj);

protected:
    virtual void DetectTarget();
    virtual void DetectTargetRelease();

private:
    void CollisionEnemy(const FVector3D& HitPoint,
        class CColliderBase* Dest);
    void CollisionEnemyEnd(class CColliderBase* Dest);

    void CollisionEnemyDetect(const FVector3D& HitPoint,
        class CColliderBase* Dest);
    void CollisionEnemyDetectEnd(class CColliderBase* Dest);

protected:
    // Loop : LoopState 함수에서 사용하는 함수
    // Once : ChageState 함수에서 사용하는 함수
    virtual void MovePointLoop(float DeltaTime);
    virtual void MovePointOnce();

    virtual void IdleLoop(float DeltaTime);
    virtual void IdleOnce();

    virtual void AttackLoop(float DeltaTime);
    virtual void AttackOnce();


    std::string EnumString(EEnemyAI ai);
    void ChangeState(EEnemyAI Type);
    void LoopState(float DeltaTime);
    
protected:  // ============ AI Virtual Function ===============
    virtual void AIIdle();
    virtual void AIPatrol();
    //virtual void AITrace();
    virtual void AIMove();
    virtual void AIAttack();
    virtual void AIDeath();
    //virtual void AISkill();
    virtual void AICustom();
    virtual void AIChangeMove();

    //virtual FVector3D Test() { return FVector3D::Zero; }
};

