#pragma once
#include "Component.h"

class CSceneComponent : public CComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CSceneComponent();
	// ���������
	CSceneComponent(const CSceneComponent& Com);
	// �̵�������
	CSceneComponent(CSceneComponent&& Com);
	virtual ~CSceneComponent();

protected:
	CSceneComponent* mParent = nullptr;
	std::vector<CSharedPointer<CSceneComponent>> mChildList;

public:
	void AddChild(CSceneComponent* Child);

public:
	// ������ ���鶧�� FileName�� Init�� �߰��ϵ��� ����.
	virtual bool Init();
	virtual bool Init(const char* FileName);

	// ������Ʈ ���� ������Ʈ �� ������ PreUpdate���� �� ��.
	virtual void PreUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	// ������Ʈ �Ŀ� ������Ʈ �� ������ PostUpdate���� �� ��.
	virtual void PostUpdate(float deltaTime);
	virtual void Collision(float deltaTime);

	// Render ������ ������Ʈ �� ������ PreRender���� �ϰ�,
	// Render ���Ŀ� ������Ʈ �� ������ PostRender���� �� ��.
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	// ���� �Լ�
	virtual CSceneComponent* Clone();

protected:
	FVector3D mRelativeScale = FVector3D(1.f, 1.f, 1.f);		// ����� ����
	FVector3D mRelativeRotation;	// ����� ����
	FVector3D mRelativePosition;	// ����� ����
	
	FVector3D mWorldScale = FVector3D(1.f, 1.f, 1.f);		// ���� ���� ����
	FVector3D mWorldRotation;	// ���� ���� ����
	FVector3D mWorldPosition;	// ���� ���� ����

	FMatrix mMatrixScale;		// ũ��
	FMatrix mMatrixRotation;	// ȸ��
	FMatrix mMatrixTranslate;	// �̵�
	FMatrix mMatrixWorld;		// ���� ����

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
	// ���� �� �� ����
	void SetRelativeRotationAxis(float angle, const FVector3D& Axis);

	void SetRelativePosition(const FVector3D& Position);
	void SetRelativePosition(float x, float y, float z);
	void SetRelativePosition(const FVector2D& Position);
	void SetRelativePosition(float x, float y);

	// ���� ������
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
	// ���� �� �� ����
	void SetWorldRotationAxis(float angle, const FVector3D& Axis);

	void SetWorldPosition(const FVector3D& Position);
	void SetWorldPosition(float x, float y, float z);
	void SetWorldPosition(const FVector2D& Position);
	void SetWorldPosition(float x, float y);

};

