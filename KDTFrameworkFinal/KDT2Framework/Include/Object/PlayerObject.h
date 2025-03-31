#pragma once

#include "SceneObject.h"

enum class EPlayerState
{
    Idle,
    Attack,
    Reloading,
    CoverHit,
    StanceHit
};

enum class EPostureState
{
    Cover,          // 커버 중일 때
    Stance,         // 공격 중일 때
    End
};

enum class EReloadingState
{
    Check,      // 장전 조건
    Animation,  // 애니메이션 불러오기
    Complete    // 완료 후 값 세팅 
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
    bool                mAutoBasePose = true;   // 디폴트 (아이들)모션이 아닌지 체크

    int             mHP = 10;

    int             mAmmoMax = 60;      // 최대 60발
    int             mAmmo = mAmmoMax;   // 초기 60발
    bool            isReloading = false;// 재장전중인가?
    EReloadingState mReloadingState = EReloadingState::Check;

    EPlayerState mPlayerState = EPlayerState::Idle;
    EPlayerState mPlayerStatePrev = mPlayerState;
    EPostureState mPostureState = EPostureState::Cover;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render();
    virtual void Damage(int Dmg);
    virtual float Damage(float Attack, CSceneObject* Obj);
    
private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);

    void MovePoint(float DeltaTime);

    void RotationZ(float DeltaTime);
    void RotationZInv(float DeltaTime);

    void MoveRight(float DeltaTime);
    void MoveLeft(float DeltaTime);

    void Fire(float DeltaTime);
    void MouseFire(float DeltaTime);

    void Reloading(float DeltaTime);

    void Skill8(float DeltaTime);
public:
    void ActionEnd();       // 모든 액션의 끝났을때 
    void AttackNotify();    // 공격 중일 때

    void CoverHitEnd();  // 공격 받았을 때
    void StanceHitEnd(); // 공격 받았을 때

    void ReloadingEnd();

private:
    void StateChange(EPlayerState State);
    void PostureChange(EPostureState State);
};

