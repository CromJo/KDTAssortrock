#pragma once
#include "Component.h"

// 계층구조가 될 컴포넌트

class CSceneComponent :
    public CComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CSceneComponent();
	CSceneComponent(const CSceneComponent& Com);
	CSceneComponent(CSceneComponent&& Com);
	virtual ~CSceneComponent();

protected:
	CSceneComponent* mParent = nullptr;
	std::vector<CSharedPointer<CSceneComponent>> mChildList;

public:
	void AddChild(CSceneComponent* Child);

public:
	virtual bool Init();
	// 에디터용 초기화 기능
	virtual bool Init(const char* FileName);
	// 업데이트 전 처리
	virtual void PreUpdate(float DeltaTime);
	// 업데이트 기능
	virtual void Update(float DeltaTime);
	// 업데이트 후 처리
	virtual void PostUpdate(float DeltaTime);
	// 렌더 전 처리
	virtual void PreRender();
	// 출력 기능
	virtual void Render();
	// 렌더 후 처리
	virtual void PostRender();
	// 복제
	virtual CSceneComponent* Clone();

protected:
	// 상대적(Local) Transform 구성품
	FVector3D mRelativeScale;
	FVector3D mRelativeRotation;
	FVector3D mRelativePosition;

	FVector3D mWorldScale;
	FVector3D mWorldRotation;
	FVector3D mWorldPosition;
	
	// 화면에 Transform을 출력하기 위해선 
	// 행렬(Matrix)로 만들어줘야 한다.
	FMatrix mMatrixScale;
	FMatrix mMatrixRotation;
	FMatrix mMatrixTranslate;
	FMatrix mMatrixWorld;

public:
	// 크기
	void SetRelativeScale(const FVector3D& Scale);
	void SetRelativeScale(float x, float y, float z);
	void SetRelativeScale(const FVector2D& Scale);
	void SetRelativeScale(float x, float y);

	// 회전
	void SetRelativeRotation(const FVector3D& Rotation);
	void SetRelativeRotation(float x, float y, float z);
	void SetRelativeRotation(const FVector2D& Rotation);
	void SetRelativeRotation(float x, float y);
	void SetRelativeRotationX(float x);
	void SetRelativeRotationY(float y);
	void SetRelativeRotationZ(float z);
	void SetRelativeRotationAxis(float Angle, const FVector3D& Axis);
	
	// 위치(좌표)
	void SetRelativePosition(const FVector3D& Position);
	void SetRelativePosition(float x, float y, float z);
	void SetRelativePosition(const FVector2D& Position);
	void SetRelativePosition(float x, float y);

	// 월드의 크기
	void SetWorldScale(const FVector3D& Scale);
	void SetWorldScale(float x, float y, float z);
	void SetWorldScale(const FVector2D& Scale);
	void SetWorldScale(float x, float y);

	// 월드 회전
	void SetWorldRotation(const FVector3D& Rotation);
	void SetWorldRotation(float x, float y, float z);
	void SetWorldRotation(const FVector2D& Rotation);
	void SetWorldRotation(float x, float y);
	void SetWorldRotationX(float x);
	void SetWorldRotationY(float y);
	void SetWorldRotationZ(float z);
	void SetWorldRotationAxis(float Angle, const FVector3D& Axis);

	// 월드 위치(좌표)
	void SetWorldPosition(const FVector3D& Position);
	void SetWorldPosition(float x, float y, float z);
	void SetWorldPosition(const FVector2D& Position);
	void SetWorldPosition(float x, float y);

};

