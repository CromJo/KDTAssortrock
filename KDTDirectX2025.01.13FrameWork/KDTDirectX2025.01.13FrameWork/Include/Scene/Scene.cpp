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
		// 활성화 안되었다면
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환.
			iter =mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// 동작하기전에 지워야 하는 오브젝트는 굳이 실행할 필요없음.
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
		// 활성화 안되었다면
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환.
			iter = mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// 동작하기전에 지워야 하는 오브젝트는 굳이 실행할 필요없음.
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
		// 활성화 안되었다면
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환.
			iter = mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// 동작하기전에 지워야 하는 오브젝트는 굳이 실행할 필요없음.
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
		// 활성화 안되었다면
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환.
			iter = mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// 동작하기전에 지워야 하는 오브젝트는 굳이 실행할 필요없음.
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
		// 활성화 안되었다면
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환.
			iter = mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// 동작하기전에 지워야 하는 오브젝트는 굳이 실행할 필요없음.
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
		// 활성화 안되었다면
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환.
			iter = mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// 동작하기전에 지워야 하는 오브젝트는 굳이 실행할 필요없음.
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
		// 활성화 안되었다면
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환.
			iter = mObjectList.erase(iter);
			iterEnd = mObjectList.end();

			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;

			continue;
		}

		// 동작하기전에 지워야 하는 오브젝트는 굳이 실행할 필요없음.
		(*iter)->PostRender();
		iter++;
	}
}
