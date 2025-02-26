#pragma once

#include "../GameInfo.h"

/*
	다양한 물체들이 배치되고,
	에디터로 배치를 했다면,
	어떤 물체가, 어느 위치에, 어느크기에
	어떤 회전정보를 가지고 배치가 되었다는
	정보를 Scene File로 만들 것이다.

	파일에 저장을 한다음, 씬이 필요할 때,
	정보를 불러와 그대로 구성될 수 있도록 Load를
	할 예정이다.

	만들 기능
	1. 코드를 이용해 원하는 물체 생성, 배치 기능
	
	주의점
	1. 업데이트, 렌더 등 나중에 실행 순서가 꼬일 수 있다.
		다른 물체에게 영향을 받게된다면, 
		그 물체가 먼저 업데이트되고,
		영향을 받는 물체가 그 다음에 업데이트 되어야한다.

*/

class CScene abstract
{
	// 자식이 부모의 생성자/소멸자는 접근이 가능해야하므로,
	// private이 아닌 protected로 한다.
protected:
	CScene();
	virtual ~CScene();

protected:
	// 중간 추가/삽입이 빈번 할 수 있기에
	// Vector는 부적격 List는 적격
	std::list<CSharedPointer<class CSceneObject>> mObjectList;

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

	virtual void Collision(float DeltaTime);
	// 렌더 전 처리
	virtual void PreRender();
	// 출력 기능
	virtual void Render();
	// 렌더 후 처리
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

