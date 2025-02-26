#pragma once

#include "../GameInfo.h"

/*
	�پ��� ��ü���� ��ġ�ǰ�,
	�����ͷ� ��ġ�� �ߴٸ�,
	� ��ü��, ��� ��ġ��, ���ũ�⿡
	� ȸ�������� ������ ��ġ�� �Ǿ��ٴ�
	������ Scene File�� ���� ���̴�.

	���Ͽ� ������ �Ѵ���, ���� �ʿ��� ��,
	������ �ҷ��� �״�� ������ �� �ֵ��� Load��
	�� �����̴�.

	���� ���
	1. �ڵ带 �̿��� ���ϴ� ��ü ����, ��ġ ���
	
	������
	1. ������Ʈ, ���� �� ���߿� ���� ������ ���� �� �ִ�.
		�ٸ� ��ü���� ������ �ްԵȴٸ�, 
		�� ��ü�� ���� ������Ʈ�ǰ�,
		������ �޴� ��ü�� �� ������ ������Ʈ �Ǿ���Ѵ�.

*/

class CScene abstract
{
	// �ڽ��� �θ��� ������/�Ҹ��ڴ� ������ �����ؾ��ϹǷ�,
	// private�� �ƴ� protected�� �Ѵ�.
protected:
	CScene();
	virtual ~CScene();

protected:
	// �߰� �߰�/������ ��� �� �� �ֱ⿡
	// Vector�� ������ List�� ����
	std::list<CSharedPointer<class CSceneObject>> mObjectList;

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

	virtual void Collision(float DeltaTime);
	// ���� �� ó��
	virtual void PreRender();
	// ��� ���
	virtual void Render();
	// ���� �� ó��
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

