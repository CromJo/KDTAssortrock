#pragma once
#include "../Share/Object.h"

class CComponent abstract :
    public CObject
{
	friend class CScene;;
	friend class CSceneObject;

protected:
    CComponent();
    CComponent(const CComponent& Com);
    CComponent(CComponent&& Com);
    virtual ~CComponent();

protected:
	// 
	class CScene* mScene = nullptr;
	class CSceneObject* mOwnerObject = nullptr;

	// 받아올 데이터의 이름
	std::string mName;

public:
	// 씬 받아오기
	class CScene* GetScene() const
	{
		return mScene;
	}

	const char* GetName() const
	{
		// c_str() 함수는 string이 가지고 있는 문자열 포인트를 반환.
		return mName.c_str();
	}

	void SetName(const std::string& Name)
	{
		mName = Name;
	}

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

};

