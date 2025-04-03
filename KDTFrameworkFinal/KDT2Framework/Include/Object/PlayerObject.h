﻿#pragma once

#include "SceneObject.h"

enum class EPlayerState
{
    Idle,
    Attack,
    Reloading,
    CoverToStance,
    StanceToCover,
    CoverHit,
    StanceHit,
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
    //CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<class CSpriteComponent>  mRoot;
    //CSharedPtr<class CColliderSphere2D>       mBody;
    CSharedPtr<class CColliderOBB2D>        mBody;
    CSharedPtr<class CColliderLine2D>       mLine;
    CSharedPtr<class CSceneComponent>       mRotationPivot;
    CSharedPtr<class CCameraComponent>      mCamera;
    CSharedPtr<class CWidgetComponent>    mHPBar;

    CSharedPtr<class CMovementComponent>    mMovement;
    CSharedPtr<class CRotationComponent>    mRotation;
    CSharedPtr<class CInventoryComponent>    mInventory;

    CSharedPtr<class CBulletObject> mSkill1Object;

    class CAnimation2D* mAnimation = nullptr;

    int             mHP = 10;

    int             mAmmoMax = 60;      // 최대 60발
    int             mAmmo = mAmmoMax;   // 초기 60발
    
    EPlayerState mPlayerState = EPlayerState::Idle;
    EPlayerState mPlayerStatePrev = mPlayerState;
    
private:
    UCHAR mAttackKey = VK_LBUTTON;            // 왼쪽 마우스버튼 할당
    UCHAR mReloadingKey = 'R';            // 왼쪽 마우스버튼 할당
    bool mReloadState = false;
    
public:
    bool KeyInput();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render();
    virtual void Damage(int Dmg);
    virtual float Damage(float Attack, CSceneObject* Obj);
    
private:
    void ChangeState(EPlayerState State);
    void LoopState(float DeltaTime);

    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);

    void MovePoint(float DeltaTime);

    void MoveRight(float DeltaTime);
    void MoveLeft(float DeltaTime);

    void Skill8(float DeltaTime);

    void Reloading(float DeltaTime);

    void IdleAnimation();
    void AttackAnimation();
    void ReloadingAnimation();
    void CoverHitAnimation();
    void StanceHitAnimation();
    void CoverToStanceAnimation();
    void StanceToCoverAnimation();

public:
    void AttackNotify();    // 공격 중일 때

    void CoverHitEnd();  // 공격 받았을 때
    void StanceHitEnd(); // 공격 받았을 때
    
    void CoverToStanceEnd();  // 스탠스자세로 이동하는 애니메이션이 끝 났을 때
    void StanceToCoverEnd(); // 커버자세로 이동하는 애니메이션이 끝 났을 때

    void ReloadingEnd();
    
    std::string DebugState();
};
