#pragma once

#include "SceneObject.h"

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

    CSharedPtr<class CBulletObject> mSkill1Object;

    bool            mSkill2Enable = false;
    float           mSkill2Time = 3.f;
    float           mSkill2TimeAcc = 0.f;
    float           mSkill2TimeInterval = 0.2f;
    
    bool            mSkill4Enable = false;
    float           mSkill4RotationSpeed = 2.f; // 스킬4 회전 속도
    float           mSkill4Range = 2.f;         // 회전의 범위 증가
    float           mSkill4Duration = 5.f;      // 스킬4 지속시간

    bool            mSkill5Enable = false;
    //std::vector<CSharedPtr<class StaticMeshComponent>> mSkill5새끼;
    int             mSkill5새끼Size = 8;
    float           mSkill5Move = 4.f;
    float           mSkill5Rotation = 2.f;


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
    void UpdateSkill5(float DeltaTime);
};

