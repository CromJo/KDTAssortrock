#include "SceneManager.h"
#include "SceneStart.h"

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
	// 메인 메뉴 화면을 그려주는 기능을 실행
	mCurrentScene = CreateScene<CSceneStart>();
	

	return true;
}

void CSceneManager::Input(float DeltaTime)
{
	// 현재 씬의 입력기능을 관장합니다.
	mCurrentScene->Input(DeltaTime);
}

/// <summary>
/// 현재 씬을 순차적으로 업데이트 해줍니다.
/// </summary>
/// <param name="DeltaTime"></param>
/// <returns></returns>
bool CSceneManager::Update(float DeltaTime)
{
	mCurrentScene->PreUpdate(DeltaTime);

	mCurrentScene->Update(DeltaTime);

	mCurrentScene->PostUpdate(DeltaTime);

	// 씬을 불러왔다면
	if (mLoadScene)
	{
		// 기존 장면을 제거한다.
		SAFE_DELETE(mCurrentScene);

		// 불러온 씬을 현재씬으로 만들고
		mCurrentScene = mLoadScene;
		// 불러온씬을 비워주고,
		mLoadScene = nullptr;
		// 실행한다.
		return true;
	}

	// 씬을 못불러 왔으면 종료한다.
	return false;
}

void CSceneManager::Collision(float DeltaTime)
{
	mCurrentScene->Collision(DeltaTime);
}

void CSceneManager::Render()
{
	mCurrentScene->Render();
}

void CSceneManager::RenderUI()
{
	mCurrentScene->RenderUI();
}

void CSceneManager::EndFrame()
{
	mCurrentScene->EndFrame();
}
