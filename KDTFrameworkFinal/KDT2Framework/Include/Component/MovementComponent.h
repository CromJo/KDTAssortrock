#pragma once

#include "Component.h"
#include "NavAgent.h"

class CMovementComponent :
    public CComponent,
	public CNavAgent
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
	std::vector<CSharedPtr<CMovementComponent>>	mMovementList;
	EAxis::Type		mMoveAxis = EAxis::None;

protected:
	FVector3D		mVelocity;
	FVector3D		mMoveStep;
	float			mSpeed = 1.f;
	bool			mVelocityInit = true;

	float			mTargetDist = 0.f;

public:
	const FVector3D& GetMoveStep()	const
	{
		return mMoveStep;
	}

	const FVector3D& GetVelocity()	const
	{
		return mVelocity;
	}

	float GetVelocityLength()	const
	{
		return mVelocity.Length();
	}

	float GetMoveDistance()	const
	{
		return mMoveStep.Length();
	}

public:
	void SetUpdateComponent(class CSceneComponent* Target);
	void SetMoveSpeed(float Speed)
	{
		mSpeed = Speed;
	}

	/// <summary>
	/// 현재 좌표에서 특정 거리만큼 이동 위치를 추가해준다.
	/// </summary>
	/// <param name="Dir"></param>
	void AddMove(const FVector3D& Dir)
	{
		mVelocity += Dir;
	}

	/// <summary>
	/// 현재 좌표의 지정한 거리를 설정한다.
	/// </summary>
	/// <param name="Dir"></param>
	void SetMove(const FVector3D& Dir)
	{
		mVelocity = Dir;
	}

	/// <summary>
	/// 이동 불가한지 아닌지를 체크한다.
	/// </summary>
	void SetVelocityInit(bool VelocityInit)
	{
		mVelocityInit = VelocityInit;
	}

	void SetMoveAxis(EAxis::Type Axis)
	{
		mMoveAxis = Axis;
	}

	void SetMovePoint(const FVector2D& Pos);
	void SetMoveRandomPoint(const FVector3D& Pos);

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMovementComponent* Clone();
	virtual void EndFrame();
};


