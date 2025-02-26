#pragma once
#include "MeshComponent.h"
class CStaticMeshComponent :
    public CMeshComponent
{

	friend class CScene;
	friend class CSceneObject;

protected:
	CStaticMeshComponent();
	CStaticMeshComponent(const CStaticMeshComponent& Com);
	CStaticMeshComponent(CStaticMeshComponent&& Com);
	virtual ~CStaticMeshComponent();

protected:
	// � Mesh�� ��������� ���� ������ ���� ����
	CSharedPointer<class CStaticMesh> mMesh;
	// � Shader�� ��������� ���� ������ ���� ����
	CSharedPointer<class CShader> mShader;

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
	virtual CStaticMeshComponent* Clone();
};

