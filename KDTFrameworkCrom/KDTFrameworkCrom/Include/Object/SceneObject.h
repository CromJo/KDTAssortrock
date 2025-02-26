#pragma once

#include "../Share/Object.h"

/*
    Scene�� ��ġ �ɰ��̱� ������,
    Scene�� ���ؼ��� ������ �� �ֵ��� 
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
	// �޾ƿ� �������� �̸�
	std::string mName;
	// Root->AddChild�� �� ��������(Ʈ������)�� ������ �ȴ�. 
	CSharedPointer<class CSceneComponent> mRootComponent;

public:
	// �� �޾ƿ���
	class CScene* GetScene() const
	{
		return mScene;
	}

	const char* GetName() const
	{
		// c_str() �Լ��� string�� ������ �ִ� ���ڿ� ����Ʈ�� ��ȯ.
		return mName.c_str();
	}

	void SetName(const std::string& Name)
	{
		mName = Name;
	}

	void SetRootComponent(class CSceneComponent* Root);


public:
	virtual bool Init();
	// �����Ϳ� �ʱ�ȭ ���
	virtual bool Init(const char* FileName);
	// ������Ʈ �� ó��
	virtual void PreUpdate(float DeltaTime);
	// ������Ʈ ���
	virtual void Update(float DeltaTime);
	// ������Ʈ �� ó��
	virtual void PostUpdate(float DeltaTime);
	// ���� �� ó��
	virtual void PreRender();
	// ��� ���
	virtual void Render();
	// ���� �� ó��
	virtual void PostRender();



};

