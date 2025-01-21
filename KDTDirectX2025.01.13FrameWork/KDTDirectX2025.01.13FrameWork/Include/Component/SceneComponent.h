#pragma once
#include "Component.h"

class CSceneComponent : public CComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CSceneComponent();
	// 복사생성자
	CSceneComponent(const CSceneComponent& Com);
	// 이동생성자
	CSceneComponent(CSceneComponent&& Com);
	virtual ~CSceneComponent();

protected:
	CSceneComponent* mParent = nullptr;
	std::vector<CSharedPointer<CSceneComponent>> mChildList;

public:
	void AddChild(CSceneComponent* Child);

public:
	// 에디터 만들때는 FileName을 Init에 추가하도록 하자.
	virtual bool Init();
	virtual bool Init(const char* FileName);

	// 업데이트 전에 업데이트 할 내용을 PreUpdate에서 할 것.
	virtual void PreUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	// 업데이트 후에 업데이트 할 내용을 PostUpdate에서 할 것.
	virtual void PostUpdate(float deltaTime);
	virtual void Collision(float deltaTime);

	// Render 이전에 업데이트 할 내용을 PreRender에서 하고,
	// Render 이후에 업데이트 할 내용을 PostRender에서 할 것.
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	// 복제 함수
	virtual CSceneComponent* Clone();

protected:
	FVector3D mRelativeScale = FVector3D(1.f, 1.f, 1.f);		// 상대적 정보
	FVector3D mRelativeRotation;	// 상대적 정보
	FVector3D mRelativePosition;	// 상대적 정보
	
	FVector3D mWorldScale = FVector3D(1.f, 1.f, 1.f);		// 최종 월드 정보
	FVector3D mWorldRotation;	// 최종 월드 정보
	FVector3D mWorldPosition;	// 최종 월드 정보

	FVector3D mAxis[EAxis::End] =
	{
		FVector3D(1.f, 0.f, 0.f),
		FVector3D(0.f, 1.f, 0.f),
		FVector3D(0.f, 0.f, 1.f),
	};

	FMatrix mMatrixScale;		// 크기
	FMatrix mMatrixRotation;	// 회전
	FMatrix mMatrixTranslate;	// 이동
	FMatrix mMatrixWorld;		// 총합 월드

public:
	const FVector3D& GetAxis(EAxis::Type Axis)
	{
		return mAxis[Axis];
	}

	const FVector3D& GetRelativeScale() const
	{
		return mRelativeScale;
	}
	const FVector3D& GetRelativeRotation() const
	{
		return mRelativeRotation;
	}
	const FVector3D& GetRelativePosition() const
	{
		return mRelativePosition;
	}

	const FVector3D& GetWorldScale() const
	{
		return mWorldScale;
	}
	const FVector3D& GetWorldRotation() const
	{
		return mWorldRotation;
	}
	const FVector3D& GetWorldPosition() const
	{
		return mWorldPosition;
	}

public:
	void SetRelativeScale(const FVector3D& Scale);
	void SetRelativeScale(float x, float y, float z);
	void SetRelativeScale(const FVector2D& Scale);
	void SetRelativeScale(float x, float y);

	void SetRelativeRotation(const FVector3D& Rotation);
	void SetRelativeRotation(float x, float y, float z);
	void SetRelativeRotation(const FVector2D& Rotation);
	void SetRelativeRotation(float x, float y);
	void SetRelativeRotationX(float x);
	void SetRelativeRotationY(float y);
	void SetRelativeRotationZ(float z);
	// 각도 및 축 설정
	void SetRelativeRotationAxis(float angle, const FVector3D& Axis);

	void SetRelativePosition(const FVector3D& Position);
	void SetRelativePosition(float x, float y, float z);
	void SetRelativePosition(const FVector2D& Position);
	void SetRelativePosition(float x, float y);

	// 월드 스케일
	void SetWorldScale(const FVector3D& Scale);
	void SetWorldScale(float x, float y, float z);
	void SetWorldScale(const FVector2D& Scale);
	void SetWorldScale(float x, float y);

	void SetWorldRotation(const FVector3D& Rotation);
	void SetWorldRotation(float x, float y, float z);
	void SetWorldRotation(const FVector2D& Rotation);
	void SetWorldRotation(float x, float y);
	void SetWorldRotationX(float x);
	void SetWorldRotationY(float y);
	void SetWorldRotationZ(float z);
	// 각도 및 축 설정
	void SetWorldRotationAxis(float angle, const FVector3D& Axis);

	void SetWorldPosition(const FVector3D& Position);
	void SetWorldPosition(float x, float y, float z);
	void SetWorldPosition(const FVector2D& Position);
	void SetWorldPosition(float x, float y);

};

