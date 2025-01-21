#pragma once
#include "../GameInfo.h"

class CScene abstract
{
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene();
	// Ŭ���� �������踦 �� �� ���ϴ� ������Ʈ�� ���� �� ��ġ�� �� �� �־���Ѵ�.
	
protected:
	class CInput* mInput = nullptr;
	std::list<CSharedPointer<class CSceneObject>> mObjectList;

public:
	virtual CInput* GetInput()	const
	{
		return mInput;
	}

	virtual void Input(float deltaTime);
	// ������ ���鶧�� FileName�� Init�� �߰��ϵ��� ����.
	virtual bool Init();
	virtual bool Init(const char* FileName);
	
	// ������Ʈ ���� ������Ʈ �� ������ PreUpdate���� �� ��.
	// ������Ʈ �Ŀ� ������Ʈ �� ������ PostUpdate���� �� ��.
	virtual void PreUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	
	virtual void Collision(float deltaTime);
	
	// Render ������ ������Ʈ �� ������ PreRender���� �ϰ�,
	// Render ���Ŀ� ������Ʈ �� ������ PostRender���� �� ��.
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

