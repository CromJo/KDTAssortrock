#pragma once
#include "SceneObject.h"

enum class EPullBulletState
{
    Movement,           // 총알 이동
    Siegemode,          // 멈춤
    Pull                // 당겨오기
};

class CStaticMeshComponent;
class CMovementComponent;
class CRotationComponent;

class CPullBullet : public CSceneObject
{
    friend class CScene;

protected:
    CSharedPtr<CStaticMeshComponent> mMesh;
    CSharedPtr<CMovementComponent> mMovement;
    CSharedPtr<CRotationComponent> mRotation;
    CSharedPtr<CSceneObject> mTarget;       // 타겟이 여러명일 수 있음

    bool            mSkill6Enable = false;
    //bool            mSkill6Pull = false;        // 총알 멈추고 당겨오는 기능 활성화
    float           mSkill6Time = 3.f;          // 총알 멈추는 시간
    float           mSkill6Range = 500.f;       // 끌어당길 범위
    float           mSkill6MoveSpeed = 300.f;   // 총알 이동 속도
    float           mSkill6PullSpeed = 100.f;   // 끌어당기는 속도

    EPullBulletState mSkill6State = EPullBulletState::Movement;

protected:
    CPullBullet();
    CPullBullet(const CPullBullet& Obj);
    CPullBullet(CPullBullet&& Obj);
    virtual ~CPullBullet();

public:
    void SetTarget(CSceneObject* Target)
    {
        mTarget = Target;
    }

    void SetBulletState(EPullBulletState State)
    {
        mSkill6State = State;
    }

    void SetBulletSpeed(float Speed)
    {
        mSkill6PullSpeed = Speed;
    }

public:
    virtual bool Init();
    virtual void PreUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);
};
