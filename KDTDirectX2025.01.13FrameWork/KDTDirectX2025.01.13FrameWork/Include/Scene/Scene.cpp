#include "Scene.h"
#include "../Object/SceneObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

bool CScene::Init()
{
	return true;
}

bool CScene::Init(const char* FileName)
{
	return true;
}

void CScene::PreUpdate(float deltaTime)
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd; iter++)
	{
		// Ȱ��ȭ �ȵǾ��ٸ�
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� ���� iterator�� ��ȯ.
			iter =mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// �����ϱ����� ������ �ϴ� ������Ʈ�� ���� ������ �ʿ����.
		(*iter)->PreUpdate(deltaTime);
		iter++;
	}
}

void CScene::Update(float deltaTime)
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd; iter++)
	{
		// Ȱ��ȭ �ȵǾ��ٸ�
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� ���� iterator�� ��ȯ.
			iter = mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// �����ϱ����� ������ �ϴ� ������Ʈ�� ���� ������ �ʿ����.
		(*iter)->Update(deltaTime);
		iter++;
	}
}

void CScene::PostUpdate(float deltaTime)
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd; iter++)
	{
		// Ȱ��ȭ �ȵǾ��ٸ�
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� ���� iterator�� ��ȯ.
			iter = mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// �����ϱ����� ������ �ϴ� ������Ʈ�� ���� ������ �ʿ����.
		(*iter)->PostUpdate(deltaTime);
		iter++;
	}
}

void CScene::Collision(float deltaTime)
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd; iter++)
	{
		// Ȱ��ȭ �ȵǾ��ٸ�
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� ���� iterator�� ��ȯ.
			iter = mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// �����ϱ����� ������ �ϴ� ������Ʈ�� ���� ������ �ʿ����.
		(*iter)->Collision(deltaTime);
		iter++;
	}
}

void CScene::PreRender()
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd; iter++)
	{
		// Ȱ��ȭ �ȵǾ��ٸ�
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� ���� iterator�� ��ȯ.
			iter = mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// �����ϱ����� ������ �ϴ� ������Ʈ�� ���� ������ �ʿ����.
		(*iter)->PreRender();
		iter++;
	}
}

void CScene::Render()
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd; iter++)
	{
		// Ȱ��ȭ �ȵǾ��ٸ�
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� ���� iterator�� ��ȯ.
			iter = mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// �����ϱ����� ������ �ϴ� ������Ʈ�� ���� ������ �ʿ����.
		(*iter)->Render();
		iter++;
	}
}

void CScene::PostRender()
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd; iter++)
	{
		// Ȱ��ȭ �ȵǾ��ٸ�
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� ���� iterator�� ��ȯ.
			iter = mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// �����ϱ����� ������ �ϴ� ������Ʈ�� ���� ������ �ʿ����.
		(*iter)->PostRender();
		iter++;
	}
}
