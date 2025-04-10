#pragma once

#include "Component.h"

class CMovementComponent :
    public CComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CMovementComponent();
	CMovementComponent(const CMovementComponent& Com);
	CMovementComponent(CMovementComponent&& Com);
	virtual ~CMovementComponent();

protected:
	CSharedPtr<class CSceneComponent>	mUpdateComponent;

protected:
	FVector3D		mVelocity;				// 방향 및 속도
	FVector3D		mMoveStep;				// 방향
	float			mSpeed = 1.f;			// 속도

public:
	const FVector3D& GetMoveStep()	const
	{
		return mMoveStep;
	}

	// 거리이동
	float GetMoveDistance()	const
	{
		return mMoveStep.Length();
	}

public:
	// SceneComponent를 상속받은 Object의 이동을 관리하는 기능
	void SetUpdateComponent(class CSceneComponent* Target);	
	void SetMoveSpeed(float Speed)
	{
		mSpeed = Speed;
	}

	void Move(const FVector3D& Dir)
	{
		mVelocity += Dir;
	}

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PostRender();
	virtual CMovementComponent* Clone();
};

