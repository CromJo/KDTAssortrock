#include "SceneManager.h"
#include "SceneMain.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager()
{

}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(mCurrentScene);
}

bool CSceneManager::Init()
{
	mCurrentScene = CreateScene<CSceneMain>();

	return true;
}

void CSceneManager::Update(float deltaTime)
{
	mCurrentScene->PreUpdate(deltaTime);
	mCurrentScene->Update(deltaTime);
	mCurrentScene->PostUpdate(deltaTime);
}

void CSceneManager::Collision(float deltaTime)
{
	mCurrentScene->Collision(deltaTime);
}

void CSceneManager::Render()
{
	mCurrentScene->PreRender();
	mCurrentScene->Render();
	mCurrentScene->PostRender();
}

void CSceneManager::Input(float deltaTime)
{
}
