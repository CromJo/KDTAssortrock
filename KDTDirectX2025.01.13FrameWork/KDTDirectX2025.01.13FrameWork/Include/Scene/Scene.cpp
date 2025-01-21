#include "Scene.h"
#include "../Object/SceneObject.h"
#include "Input.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	SAFE_DELETE(mInput);
}

void CScene::Input(float deltaTime)
{
	mInput->Update(deltaTime);
}

bool CScene::Init()
{
	mInput = new CInput;

	if (!mInput->Init())
		return false;

	return true;
}

bool CScene::Init(const char* FileName)
{
	mInput = new CInput;

	if (!mInput->Init())
		return false;

	return true;
}

void CScene::PreUpdate(float deltaTime)
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd;)
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

	for (iter = mObjectList.begin(); iter != iterEnd;)
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

	for (iter = mObjectList.begin(); iter != iterEnd;)
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

	for (iter = mObjectList.begin(); iter != iterEnd;)
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

	for (iter = mObjectList.begin(); iter != iterEnd;)
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

	for (iter = mObjectList.begin(); iter != iterEnd;)
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

	for (iter = mObjectList.begin(); iter != iterEnd;)
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
