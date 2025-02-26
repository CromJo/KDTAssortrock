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

	// �޾ƿ� �������� �̸�
	std::string mName;

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

