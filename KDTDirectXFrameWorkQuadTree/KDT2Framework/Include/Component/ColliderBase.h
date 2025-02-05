#pragma once

#include "SceneComponent.h"

// 씬 컴포넌트의 데이터들을 포함하는 추상 클래스
class CColliderBase abstract :
    public CSceneComponent
{
	// Scene 및 SceneObject에서 
	// ColliderBase 데이터를 사용할 수 있도록 설정
	friend class CScene;
	friend class CSceneObject;

protected:
	CColliderBase();
	CColliderBase(const CColliderBase& Com);
	CColliderBase(CColliderBase&& Com);
	virtual ~CColliderBase();

protected:
	EColliderType	mColliderType;
	EColliderShape	mColliderShape;
	FVector3D		mMin;
	FVector3D		mMax;

public:
	EColliderType GetColliderType()	const
	{
		return mColliderType;
	}

	const FVector3D& GetMin()
	{
		return mMin;
	}

	const FVector3D& GetMax()
	{
		return mMax;
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
	virtual CColliderBase* Clone();
};

