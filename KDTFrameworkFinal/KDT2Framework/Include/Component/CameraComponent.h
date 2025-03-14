#pragma once

#include "SceneComponent.h"

enum class ECameraProjectionType
{
	Perspective, // 다신 보지말자 시부레
	Ortho
};

class CCameraComponent :
    public CSceneComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CCameraComponent();
	CCameraComponent(const CCameraComponent& Com);
	CCameraComponent(CCameraComponent&& Com);
	virtual ~CCameraComponent();

protected:
	ECameraProjectionType	mProjType = ECameraProjectionType::Ortho;
	FMatrix		mmatView;
	FMatrix		mmatProj;
	
	float		mViewAngle = 90.f;
	float		mWidth = 1280.f;
	float		mHeight = 720.f;
	float		mViewDistance = 3000.f;	// 그려줄 이미지 최대 범위

public:
	// 현재 행렬 값 반환 함수
	const FMatrix& GetViewMatrix()	const
	{
		return mmatView;
	}

	/// <summary>
	/// 현재 투영행렬 값 반환 함수
	/// </summary>
	/// <returns></returns>
	const FMatrix& GetProjMatrix()	const
	{
		return mmatProj;
	}

public:
	void SetProjectionType(ECameraProjectionType Type);
	void SetViewAngle(float Angle)
	{
		mViewAngle = Angle;
	}

	void SetViewResolution(float Width, float Height)
	{
		mWidth = Width;
		mHeight = Height;
	}

	void SetViewDistance(float Dist)
	{
		mViewDistance = Dist;
	}

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual CCameraComponent* Clone();
};

