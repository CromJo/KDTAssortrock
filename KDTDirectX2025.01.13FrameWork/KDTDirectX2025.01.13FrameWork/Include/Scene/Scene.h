#pragma once
#include "../GameInfo.h"

class CScene abstract
{
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene();
	// 클래스 구조설계를 할 때 원하는 오브젝트를 생성 및 배치를 할 수 있어야한다.
	
protected:
	class CInput* mInput = nullptr;
	std::list<CSharedPointer<class CSceneObject>> mObjectList;

public:
	virtual CInput* GetInput()	const
	{
		return mInput;
	}

	virtual void Input(float deltaTime);
	// 에디터 만들때는 FileName을 Init에 추가하도록 하자.
	virtual bool Init();
	virtual bool Init(const char* FileName);
	
	// 업데이트 전에 업데이트 할 내용을 PreUpdate에서 할 것.
	// 업데이트 후에 업데이트 할 내용을 PostUpdate에서 할 것.
	virtual void PreUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	
	virtual void Collision(float deltaTime);
	
	// Render 이전에 업데이트 할 내용을 PreRender에서 하고,
	// Render 이후에 업데이트 할 내용을 PostRender에서 할 것.
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

public:
	template <typename T>
	T* CreateObject(const std::string& Name)
	{
		T* Obj = new T;
		
		Obj->mScene = this;
		Obj->SetName(Name);

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);

			return nullptr;
		}

		mObjectList.push_back(Obj);

		return Obj;
	}
};

