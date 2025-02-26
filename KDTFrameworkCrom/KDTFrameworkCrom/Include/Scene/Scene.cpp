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
	return false;
}

bool CScene::Init(const char* FileName)
{
	return true;
}

void CScene::PreUpdate(float DeltaTime)
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd;)
	{
		// �����ߵ� ������Ʈ�� ������ ���ʿ�,
		// �����ϱ����� Release�� ����ȭ
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� 
			// ���� iterator�� ��ȯ�ϰ� �ȴ�.
			// �׷��⿡ �ڵ����� iter++�� �ƴ�
			// for���� ������ �������� ++�ǵ���
			// �ϸ�ȴ�.
			iter = mObjectList.erase(iter);
		}

		else if ((*iter)->IsEnable())
		{
			++iter;

			continue;
		}

		(*iter)->PreUpdate(DeltaTime);

		++iter;
	}
}

void CScene::Update(float DeltaTime)
{
		std::list<CSharedPointer<CSceneObject>>::iterator iter;
		std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

		for (iter = mObjectList.begin(); iter != iterEnd;)
		{
			// �����ߵ� ������Ʈ�� ������ ���ʿ�,
			// �����ϱ����� Release�� ����ȭ
			if (!(*iter)->IsActive())
			{
				// erase�� �ϸ� ���� iterator�� 
				// ���� iterator�� ��ȯ�ϰ� �ȴ�.
				// �׷��⿡ �ڵ����� iter++�� �ƴ�
				// for���� ������ �������� ++�ǵ���
				// �ϸ�ȴ�.
				iter = mObjectList.erase(iter);
			}

			else if ((*iter)->IsEnable())
			{
				++iter;

				continue;
			}

			(*iter)->Update(DeltaTime);

			++iter;
		}
}

void CScene::PostUpdate(float DeltaTime)
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd;)
	{
		// �����ߵ� ������Ʈ�� ������ ���ʿ�,
		// �����ϱ����� Release�� ����ȭ
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� 
			// ���� iterator�� ��ȯ�ϰ� �ȴ�.
			// �׷��⿡ �ڵ����� iter++�� �ƴ�
			// for���� ������ �������� ++�ǵ���
			// �ϸ�ȴ�.
			iter = mObjectList.erase(iter);
		}

		else if ((*iter)->IsEnable())
		{
			++iter;

			continue;
		}

		(*iter)->PostUpdate(DeltaTime);

		++iter;
	}
}

void CScene::Collision(float DeltaTime)
{
}

void CScene::PreRender()
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd;)
	{
		// �����ߵ� ������Ʈ�� ������ ���ʿ�,
		// �����ϱ����� Release�� ����ȭ
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� 
			// ���� iterator�� ��ȯ�ϰ� �ȴ�.
			// �׷��⿡ �ڵ����� iter++�� �ƴ�
			// for���� ������ �������� ++�ǵ���
			// �ϸ�ȴ�.
			iter = mObjectList.erase(iter);
		}

		else if ((*iter)->IsEnable())
		{
			++iter;

			continue;
		}

		(*iter)->PreRender();

		++iter;
	}
}

void CScene::Render()
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd;)
	{
		// �����ߵ� ������Ʈ�� ������ ���ʿ�,
		// �����ϱ����� Release�� ����ȭ
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� 
			// ���� iterator�� ��ȯ�ϰ� �ȴ�.
			// �׷��⿡ �ڵ����� iter++�� �ƴ�
			// for���� ������ �������� ++�ǵ���
			// �ϸ�ȴ�.
			iter = mObjectList.erase(iter);
		}

		else if ((*iter)->IsEnable())
		{
			++iter;

			continue;
		}

		(*iter)->Render();

		++iter;
	}
}

void CScene::PostRender()
{
	std::list<CSharedPointer<CSceneObject>>::iterator iter;
	std::list<CSharedPointer<CSceneObject>>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd;)
	{
		// �����ߵ� ������Ʈ�� ������ ���ʿ�,
		// �����ϱ����� Release�� ����ȭ
		if (!(*iter)->IsActive())
		{
			// erase�� �ϸ� ���� iterator�� 
			// ���� iterator�� ��ȯ�ϰ� �ȴ�.
			// �׷��⿡ �ڵ����� iter++�� �ƴ�
			// for���� ������ �������� ++�ǵ���
			// �ϸ�ȴ�.
			iter = mObjectList.erase(iter);
		}

		else if ((*iter)->IsEnable())
		{
			++iter;

			continue;
		}

		(*iter)->PostRender();

		++iter;
	}
}
