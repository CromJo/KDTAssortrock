#pragma once
#include "../Share/Object.h"

// Scene에 배치될 Object
// 그래서 Scene을 통해서만 생성이 되도록 한다.
class CComponent abstract : public CObject
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CComponent();
	// 복사생성자
	CComponent(const CComponent& Com);
	// 이동생성자
	CComponent(CComponent&& Com);
	virtual ~CComponent();

protected:
	// 한개의 씬은 무조건 존재하도록 설정
	class CScene* mScene = nullptr;
	class CSceneObject* mOwnerObject = nullptr;
	std::string mName;

public:
	class CScene* GetScene()	const
	{
		return mScene;
	}

	class CSceneObject* GetOwner()	const
	{
		return mOwnerObject;
	}

	const char* GetName()	const
	{
		// c_str() 함수는 string이 가지고 있는 문자열 포인터를 반환
		return mName.c_str();
	}

	void SetName(const std::string& Name)
	{
		mName = Name;
	}

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
	virtual CComponent* Clone();

};

