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
	// 어떤 Mesh를 사용할지에 대한 데이터 저장 변수
	CSharedPointer<class CStaticMesh> mMesh;
	// 어떤 Shader를 사용할지에 대한 데이터 저장 변수
	CSharedPointer<class CShader> mShader;

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
	virtual CStaticMeshComponent* Clone();
};

