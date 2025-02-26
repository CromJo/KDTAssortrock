#pragma once

#include "../Share/Object.h"

/*
    Scene에 배치 될것이기 떄문에,
    Scene을 통해서만 생성될 수 있도록 
*/

class CSceneObject :
    public CObject
{
protected:
    CSceneObject();
    CSceneObject(const CSceneObject& Object);
    CSceneObject(CSceneObject&& Object);
    virtual ~CSceneObject();

protected:
	// 
	class CScene* mScene = nullptr;
	// 받아올 데이터의 이름
	std::string mName;
	// Root->AddChild할 시 계층구조(트리구조)로 구성이 된다. 
	CSharedPointer<class CSceneComponent> mRootComponent;

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

	void SetRootComponent(class CSceneComponent* Root);


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

