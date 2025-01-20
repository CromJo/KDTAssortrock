#pragma once
#include "MeshComponent.h"

class CStaticMeshComponent : public CMeshComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CStaticMeshComponent();
	// ���������
	CStaticMeshComponent(const CStaticMeshComponent& Com);
	// �̵�������
	CStaticMeshComponent(CStaticMeshComponent&& Com);
	virtual ~CStaticMeshComponent();

protected:
	CSharedPointer<class CStaticMesh> mMesh;
	CSharedPointer<class CShader> mShader;

public:
	void SetShader(const std::string& Name);
	void SetShader(class CShader* Shader);
	void SetMesh(const std::string& Name);
	void SetMesh(class CMesh* Mesh);

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
	virtual CStaticMeshComponent* Clone();

};

