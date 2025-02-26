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
	// MeshComponent종류면 무조건 만들어야하는 데이터
	class CTransformCBuffer* mTransformCBuffer;

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
	virtual CMeshComponent* Clone();
};

