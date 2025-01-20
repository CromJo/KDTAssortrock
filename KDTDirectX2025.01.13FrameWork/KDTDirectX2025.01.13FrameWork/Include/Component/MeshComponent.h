#pragma once
#include "SceneComponent.h"

class CMeshComponent : public CSceneComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CMeshComponent();
	// ���������
	CMeshComponent(const CMeshComponent& Com);
	// �̵�������
	CMeshComponent(CMeshComponent&& Com);
	virtual ~CMeshComponent();

protected:
	class CTransformCBuffer* mTransformCBuffer;

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
	virtual CMeshComponent* Clone();

};

