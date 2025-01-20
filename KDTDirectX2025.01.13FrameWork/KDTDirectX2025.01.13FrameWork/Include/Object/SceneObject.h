#pragma once
#include "../Share/Object.h"

// Scene�� ��ġ�� Object
// �׷��� Scene�� ���ؼ��� ������ �ǵ��� �Ѵ�.
class CSceneObject : public CObject
{
	friend class CScene;

protected:
	CSceneObject();
	// ���������
	CSceneObject(const CSceneObject& Obj);
	// �̵�������
	CSceneObject(CSceneObject&& Obj);
	virtual ~CSceneObject();

protected:
	// �Ѱ��� ���� ������ �����ϵ��� ����
	class CScene* mScene = nullptr;
	std::string mName;
	CSharedPointer<class CSceneComponent> mRootComponent;

public:
	class CScene* GetScene()	const
	{
		return mScene;
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

	void SetRootComponent(class CSceneComponent* Root);

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
	virtual CSceneObject* Clone();

public:
	template <typename T>
	T* CreateComponent()
	{
		T* Component = new T;

		if (!Component->Init())
		{
			SAFE_DELETE(Component);
			return nullptr;
		}
	}
};

