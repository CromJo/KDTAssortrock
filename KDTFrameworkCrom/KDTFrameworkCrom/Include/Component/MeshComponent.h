#pragma once
#include "SceneComponent.h"

class CMeshComponent :
    public CSceneComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CMeshComponent();
	CMeshComponent(const CMeshComponent& Com);
	CMeshComponent(CMeshComponent&& Com);
	virtual ~CMeshComponent();

protected:
	// MeshComponent������ ������ �������ϴ� ������
	class CTransformCBuffer* mTransformCBuffer;

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
	virtual CMeshComponent* Clone();
};

