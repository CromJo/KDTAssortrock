#pragma once
#include "SceneObject.h"

enum class EPullBulletState
{
    Movement,           // �Ѿ� �̵�
    Siegemode,          // ����
    Pull                // ��ܿ���
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
    CSharedPtr<CSceneObject> mTarget;       // Ÿ���� �������� �� ����

    bool            mSkill6Enable = false;
    //bool            mSkill6Pull = false;        // �Ѿ� ���߰� ��ܿ��� ��� Ȱ��ȭ
    float           mSkill6Time = 3.f;          // �Ѿ� ���ߴ� �ð�
    float           mSkill6Range = 500.f;       // ������ ����
    float           mSkill6MoveSpeed = 300.f;   // �Ѿ� �̵� �ӵ�
    float           mSkill6PullSpeed = 100.f;   // ������� �ӵ�

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
