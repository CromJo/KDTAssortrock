#pragma once

#include "SceneObject.h"

enum class ESkill4State
{
    Expansion,
    Maintain,
    Reduction
};

class CPlayerObject :
    public CSceneObject
{
    friend class CScene;

protected:
    CPlayerObject();
    CPlayerObject(const CPlayerObject& Obj);
    CPlayerObject(CPlayerObject&& Obj);
    virtual ~CPlayerObject();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<class CSceneComponent>       mRotationPivot;
    CSharedPtr<class CStaticMeshComponent>  mSub;
    CSharedPtr<class CStaticMeshComponent>  mSub2;
    CSharedPtr<class CCameraComponent>      mCamera;

    CSharedPtr<class CMovementComponent>    mMovement;

    CSharedPtr<class CBulletObject> mSkill1Object;

    bool            mSkill2Enable = false;
    float           mSkill2Time = 3.f;
    float           mSkill2TimeAcc = 0.f;
    float           mSkill2TimeInterval = 0.2f;

    bool            mSkill4Enable = false;
    float           mSkill4Time = 5.f;
    float           mSkill4TimeAcc = 0.f;
    float           mSkill4ReadyTime = 2.f;
    float           mSkill4MaxRange = 4.f;
    float           mSkill4Range = 100.f;
    float           mSkill4RangeLength = 2.f;
    float           mPivotRotationSpeed = 180.f;
    ESkill4State    mSkill4State = ESkill4State::Expansion;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);

    void RotationZ(float DeltaTime);
    void RotationZInv(float DeltaTime);

    void Fire(float DeltaTime);

    void Skill1(float DeltaTime);
    void Skill1Fire(float DeltaTime);

    void Skill2(float DeltaTime);

    void Skill3(float DeltaTime);

    void Skill4(float DeltaTime);

    void Skill5(float DeltaTime);

private:
    void UpdateSkill2(float DeltaTime);
    void UpdateSkill4(float DeltaTime);
};

