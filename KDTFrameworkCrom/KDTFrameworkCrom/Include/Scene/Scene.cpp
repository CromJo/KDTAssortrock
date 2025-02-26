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
		// 지워야될 오브젝트는 동작이 불필요,
		// 동작하기전에 Release로 최적화
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 
			// 다음 iterator를 반환하게 된다.
			// 그렇기에 자동으로 iter++이 아닌
			// for문이 끝날때 수동으로 ++되도록
			// 하면된다.
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
			// 지워야될 오브젝트는 동작이 불필요,
			// 동작하기전에 Release로 최적화
			if (!(*iter)->IsActive())
			{
				// erase를 하면 지운 iterator의 
				// 다음 iterator를 반환하게 된다.
				// 그렇기에 자동으로 iter++이 아닌
				// for문이 끝날때 수동으로 ++되도록
				// 하면된다.
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
		// 지워야될 오브젝트는 동작이 불필요,
		// 동작하기전에 Release로 최적화
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 
			// 다음 iterator를 반환하게 된다.
			// 그렇기에 자동으로 iter++이 아닌
			// for문이 끝날때 수동으로 ++되도록
			// 하면된다.
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
		// 지워야될 오브젝트는 동작이 불필요,
		// 동작하기전에 Release로 최적화
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 
			// 다음 iterator를 반환하게 된다.
			// 그렇기에 자동으로 iter++이 아닌
			// for문이 끝날때 수동으로 ++되도록
			// 하면된다.
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
		// 지워야될 오브젝트는 동작이 불필요,
		// 동작하기전에 Release로 최적화
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 
			// 다음 iterator를 반환하게 된다.
			// 그렇기에 자동으로 iter++이 아닌
			// for문이 끝날때 수동으로 ++되도록
			// 하면된다.
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
		// 지워야될 오브젝트는 동작이 불필요,
		// 동작하기전에 Release로 최적화
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 
			// 다음 iterator를 반환하게 된다.
			// 그렇기에 자동으로 iter++이 아닌
			// for문이 끝날때 수동으로 ++되도록
			// 하면된다.
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
