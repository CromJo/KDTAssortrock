#pragma once
#include "../Share/Object.h"

// Scene�� ��ġ�� Object
// �׷��� Scene�� ���ؼ��� ������ �ǵ��� �Ѵ�.
class CComponent abstract : public CObject
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CComponent();
	// ���������
	CComponent(const CComponent& Com);
	// �̵�������
	CComponent(CComponent&& Com);
	virtual ~CComponent();

protected:
	// �Ѱ��� ���� ������ �����ϵ��� ����
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
		// c_str() �Լ��� string�� ������ �ִ� ���ڿ� �����͸� ��ȯ
		return mName.c_str();
	}

	void SetName(const std::string& Name)
	{
		mName = Name;
	}

public:
	// ������ ���鶧�� FileName�� Init�� �߰��ϵ��� ����.
	virtual bool Init();
	virtual bool Init(const char* FileName);

	// ������Ʈ ���� ������Ʈ �� ������ PreUpdate���� �� ��.
	virtual void PreUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	// ������Ʈ �Ŀ� ������Ʈ �� ������ PostUpdate���� �� ��.
	virtual void PostUpdate(float deltaTime);
	virtual void Collision(float deltaTime);

	// Render ������ ������Ʈ �� ������ PreRender���� �ϰ�,
	// Render ���Ŀ� ������Ʈ �� ������ PostRender���� �� ��.
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	// ���� �Լ�
	virtual CComponent* Clone();

};

