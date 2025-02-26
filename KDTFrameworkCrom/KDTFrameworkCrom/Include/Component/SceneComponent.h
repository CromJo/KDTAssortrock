#pragma once
#include "Component.h"

// ���������� �� ������Ʈ

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
	// �����Ϳ� �ʱ�ȭ ���
	virtual bool Init(const char* FileName);
	// ������Ʈ �� ó��
	virtual void PreUpdate(float DeltaTime);
	// ������Ʈ ���
	virtual void Update(float DeltaTime);
	// ������Ʈ �� ó��
	virtual void PostUpdate(float DeltaTime);
	// ���� �� ó��
	virtual void PreRender();
	// ��� ���
	virtual void Render();
	// ���� �� ó��
	virtual void PostRender();
	// ����
	virtual CSceneComponent* Clone();

protected:
	// �����(Local) Transform ����ǰ
	FVector3D mRelativeScale;
	FVector3D mRelativeRotation;
	FVector3D mRelativePosition;

	FVector3D mWorldScale;
	FVector3D mWorldRotation;
	FVector3D mWorldPosition;
	
	// ȭ�鿡 Transform�� ����ϱ� ���ؼ� 
	// ���(Matrix)�� �������� �Ѵ�.
	FMatrix mMatrixScale;
	FMatrix mMatrixRotation;
	FMatrix mMatrixTranslate;
	FMatrix mMatrixWorld;

public:
	// ũ��
	void SetRelativeScale(const FVector3D& Scale);
	void SetRelativeScale(float x, float y, float z);
	void SetRelativeScale(const FVector2D& Scale);
	void SetRelativeScale(float x, float y);

	// ȸ��
	void SetRelativeRotation(const FVector3D& Rotation);
	void SetRelativeRotation(float x, float y, float z);
	void SetRelativeRotation(const FVector2D& Rotation);
	void SetRelativeRotation(float x, float y);
	void SetRelativeRotationX(float x);
	void SetRelativeRotationY(float y);
	void SetRelativeRotationZ(float z);
	void SetRelativeRotationAxis(float Angle, const FVector3D& Axis);
	
	// ��ġ(��ǥ)
	void SetRelativePosition(const FVector3D& Position);
	void SetRelativePosition(float x, float y, float z);
	void SetRelativePosition(const FVector2D& Position);
	void SetRelativePosition(float x, float y);

	// ������ ũ��
	void SetWorldScale(const FVector3D& Scale);
	void SetWorldScale(float x, float y, float z);
	void SetWorldScale(const FVector2D& Scale);
	void SetWorldScale(float x, float y);

	// ���� ȸ��
	void SetWorldRotation(const FVector3D& Rotation);
	void SetWorldRotation(float x, float y, float z);
	void SetWorldRotation(const FVector2D& Rotation);
	void SetWorldRotation(float x, float y);
	void SetWorldRotationX(float x);
	void SetWorldRotationY(float y);
	void SetWorldRotationZ(float z);
	void SetWorldRotationAxis(float Angle, const FVector3D& Axis);

	// ���� ��ġ(��ǥ)
	void SetWorldPosition(const FVector3D& Position);
	void SetWorldPosition(float x, float y, float z);
	void SetWorldPosition(const FVector2D& Position);
	void SetWorldPosition(float x, float y);

};

