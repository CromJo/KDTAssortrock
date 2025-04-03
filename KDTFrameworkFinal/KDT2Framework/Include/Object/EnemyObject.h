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
    CSharedPtr<class CWidgetComponent>        mHPBar;
    CSharedPtr<CSceneObject>  mTarget;
    class CAnimation2D* mAnimation = nullptr;
    EEnemyAI          mAI = EEnemyAI::Idle;
    std::string         mAIAnimationName[(int)EEnemyAI::End];

    float           mDetectDistance = 0.f;

    int             mHP = 5;
    float           mLogicTime = 0.f;    // 로직 랜덤 체인지를 위한 시간

    CSharedPtr<class CMovementComponent>    mMovement;
    float           mSpeed = 200.f;
    FVector3D       mSaveMoveData = FVector3D::Zero;

private:
    // 화면 범위 지정 데이터
    float ScreenMinX = 0.f;
    float ScreenMaxX = 0.f;
    float ScreenMinY = 0.f;
    float ScreenMaxY = 0.f;
    float mFirstMoveMinX = 200.f;
    float mFirstMoveMaxX = 200.f;

private:
    void SetLimitScreen();

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
    // Once : ChageState 함수에서 한번만 실행 될 함수
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
    virtual void IdleAnimation();
    virtual void MoveAnimation();
    virtual void AttackAnimation();
    virtual void DeathAnimation();

    //virtual FVector3D Test() { return FVector3D::Zero; }
};

