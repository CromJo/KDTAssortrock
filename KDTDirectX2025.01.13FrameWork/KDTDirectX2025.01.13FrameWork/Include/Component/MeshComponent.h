#pragma once
#include "SceneComponent.h"

class CMeshComponent : public CSceneComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CMeshComponent();
	// 복사생성자
	CMeshComponent(const CMeshComponent& Com);
	// 이동생성자
	CMeshComponent(CMeshComponent&& Com);
	virtual ~CMeshComponent();

protected:
	class CTransformCBuffer* mTransformCBuffer;

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
	virtual CMeshComponent* Clone();

};

