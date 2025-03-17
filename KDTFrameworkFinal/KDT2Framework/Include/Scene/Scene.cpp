#include "Scene.h"
#include "../Object/SceneObject.h"
#include "Input.h"
#include "CameraManager.h"
#include "SceneCollision.h"
#include "../Share/Log.h"
#include "SceneAssetManager.h"
#include "../Render/RenderManager.h"
#include "SceneUIManager.h"
#include "Navigation.h"

CScene::CScene()
{
}

/// <summary>
/// 메모리 해제
/// </summary>
CScene::~CScene()
{
	//CRenderManager::GetInst()->ClearRenderList();
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	// 오브젝트 목록을 싹다 제거 시킴
	for (iter = mObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Destroy();
	}

	// 싹다 제거 시키는데 clear는 왜 하나?
	mObjList.clear();
	// 메모리해제
	SAFE_DELETE(mUIManager);		// UI 매니저		
	SAFE_DELETE(mAssetManager);		// Asset 매니저
	SAFE_DELETE(mCollision);		// 충돌체 오브젝트
	SAFE_DELETE(mCameraManager);	// 카메라(시야) 매니저
	SAFE_DELETE(mInput);			// 입력 기능
	SAFE_DELETE(mNavigation);		// 네비게이션 
}

/// <summary>
/// 기본 씬 초기화 함수
/// </summary>
/// <returns></returns>
bool CScene::Init()
{
#pragma region Input 초기화
	// 입력 데이터 생성
	mInput = new CInput;
	// 입력 데이터 씬을 현재씬으로 만듦
	mInput->mScene = this;
	
	// 입력 초기화 안되어있으면 종료
	if (!mInput->Init())
		return false;
#pragma endregion
#pragma region Camera Manager 초기화
	// 입력 초기화 되어있으면,
	// 카메라 매니저 데이터 생성
	mCameraManager = new CCameraManager;

	// 카메라 매니저 초기화가 안되어있으면 종료
	if (!mCameraManager->Init())
		return false;
#pragma endregion
#pragma region Collision Object 초기화
	// 카메라 매니저 초기화 되어있으면,
	// 충돌체 새로 생성
	mCollision = new CSceneCollision;

	// 충돌체를 현재씬으로 설정
	mCollision->mScene = this;

	// 충돌체 초기화가 안되었으면 종료
	if (!mCollision->Init())
		return false;
#pragma endregion
#pragma region 씬 에셋 매니저 초기세팅
	// 충돌체가 초기화가 되었으면,
	// 씬의 에셋 매니저 새로 생성
	mAssetManager = new CSceneAssetManager;

	// 에셋 매니저의 씬을 현재 씬으로 설정
	mAssetManager->mScene = this;

	// 씬에셋 매니저 초기화 실패시 종료
	if (!mAssetManager->Init())
		return false;
#pragma endregion
#pragma region UI 매니저 초기화
	mUIManager = new CSceneUIManager;

	mUIManager->mScene = this;

	if (!mUIManager->Init())
		return false;
#pragma endregion
#pragma region 네비게이션 초기세팅
	// 네비게이션 새로 생성
	mNavigation = new CNavigation;

	// 네비게이션을 현재씬으로 설정
	mNavigation->mScene = this;

	// 네비게이션 초기화 실패시 종료
	if (!mNavigation->Init())
		return false;
#pragma endregion 
#pragma region Asset & Widget & Object 초기화 (라고하지만 false로 다 설정되어있음)
	InitAsset();
	InitWidget();
	InitObject();
#pragma endregion
	
	// 씬 초기화 성공
	return true;
}

/// <summary>
/// 기본씬 파일데이터로 초기화하는 기능
///		※ 단 현재 사용처가 없음
///		※ 기능 자체는 Scene::Init()과 동일함
/// </summary>
/// <param name="FileName"></param>
/// <returns></returns>
bool CScene::Init(const char* FileName)
{
	mInput = new CInput;

	if (!mInput->Init())
		return false;

	mCameraManager = new CCameraManager;

	if (!mCameraManager->Init())
		return false;

	mCollision = new CSceneCollision;

	mCollision->mScene = this;

	if (!mCollision->Init())
		return false;

	mAssetManager = new CSceneAssetManager;

	mAssetManager->mScene = this;

	if (!mAssetManager->Init())
		return false;

	mUIManager = new CSceneUIManager;

	mUIManager->mScene = this;

	if (!mUIManager->Init())
		return false;

	InitAsset();
	InitWidget();
	InitObject();
	
	return true;
}

/// <summary>
/// 씬의 입력 기능
/// </summary>
/// <param name="DeltaTime"></param>
void CScene::Input(float DeltaTime)
{
	// 입력에 대한 업데이트를 처리합니다.
	mInput->Update(DeltaTime);
}

/// <summary>
/// 씬의 Update보다 한박자 빠른 Update를 처리합니다.
/// 씬에서 Active 및 Enable 되어있는 오브젝트의 
/// PreUpdate (초기 업데이트)를 실행시키기 위한 기능입니다.
/// ====순서====
/// 1. 오브젝트 목록
/// </summary>
/// <param name="DeltaTime"></param>
void CScene::PreUpdate(float DeltaTime)
{
	// 씬의 오브젝트 리스트들을 가지고 옵니다.
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	// 오브젝트 목록의 갯수만큼 반복합니다.
	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		// 현재 확인하는 오브젝트가
		// 활성화 되어있지 않으면,
		// 현재 오브젝트를 목록에서 지우고,
		// 목록을 1칸 당기고 다시 목록을 검사합니다.
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환한다.
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}

		// 현재 확인하는 오브젝트가
		// 활성화는 되어있으나 켜져있지(?)않으면,
		// 다음 오브젝트를 검사합니다.
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		// 현재 확인하는 오브젝트가
		// 활성화 및 켜져있는 상태면 초기 업데이트를 실행합니다.
		(*iter)->PreUpdate(DeltaTime);

		// 다음 오브젝트를 검사합니다.
		++iter;
	}
}

/// <summary>
/// 씬의 Update를 처리합니다.
/// 씬에서 Active 및 Enable 되어있는 오브젝트의 
/// Update (중기 업데이트)를 실행시키기 위한 기능입니다.
/// 업데이트 순서
/// 1. 오브젝트 목록들
/// 2. 카메라 매니저
/// 3. UI 매니저
/// 
/// </summary>
/// <param name="DeltaTime"></param>
void CScene::Update(float DeltaTime)
{
#pragma region 이 부분은 PreUpdate와 동일 합니다.
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환한다.
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);

		++iter;
	}
#pragma endregion

	// 씬에서 카메라 매니저를 업데이트 합니다.
	mCameraManager->Update(DeltaTime);
	// 씬에서 UI 매니저를 업데이트 합니다.
	mUIManager->Update(DeltaTime);

	// 오브젝트 목록의 총갯수를 확인합니다.
	int	Count = (int)mObjList.size();
	
	// 버퍼 오버플로우를 방지해주는
	// C++ → C로 문자열 포맷팅을 할때 사용합니다.
	// Text		: 최종 문자열 보관할 데이터
	// ObjCount : 바이트 단위
	// Count	: 포맷할 문자열
	// 즉 ObjCount : 에다가 Count를 붙여서 Text에 저장하겠다는 뜻임
	char	Text[64] = {};
	sprintf_s(Text, "ObjCount : %d", Count);

	// 의문 : Text가 0보다 아래면 오류를 표시하도록 
	//			안전한 설계를 하는게 맞지 않을까?
	//CLog::PrintLog(Text);
}

/// <summary>
/// 씬의 Update보다 한박자 느린 Update를 실행시킵니다.
/// 씬에서 Active 및 Enable 되어있는 오브젝트의 
/// PreUpdate (초기 업데이트)를 실행시키기 위한 기능입니다.
/// ====순서====
/// 1. 오브젝트 목록
/// </summary>
/// <param name="DeltaTime"></param>
void CScene::PostUpdate(float DeltaTime)
{
#pragma region PreUpdate와 동일합니다.
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			// erase를 하면 지운 iterator의 다음 iterator를 반환한다.
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);

		++iter;
	}
#pragma endregion
}

/// <summary>
/// 씬의 충돌체를 업데이트합니다.
/// </summary>
/// <param name="DeltaTime"></param>
void CScene::Collision(float DeltaTime)
{
	// UI와의 충돌도 Collision 안쪽에서 처리한다.
	mCollision->Update(DeltaTime, mUIManager, mInput);
}

/// <summary>
/// 씬의 출력 기능을 담당합니다.
/// 충돌체를 그려줍니다.
/// </summary>
void CScene::Render()
{
#ifdef _DEBUG

	// 디버그용 쿼드트리가 활성화되어있으면,
	// 충돌체 범위를 그려준다.
	if (mDebugQuadTree)
		mCollision->Render();

#endif // _DEBUG

	// 충돌체를 
	mCollision->ReturnNodePool();
}

/// <summary>
/// UI 출력 기능.
/// </summary>
void CScene::RenderUI()
{
	// UI Manager의 존재하는 오브젝트들을
	// 이 씬에 출력합니다.
	mUIManager->Render();
}

/// <summary>
/// 마지막 프레임 관련한 함수입니다.
/// 여기서의 프레임은 오브젝트의 프레임. 
/// 즉, 애니메이션 프레임입니다.
/// </summary>
void CScene::EndFrame()
{
	// 오브젝트 목록들을 불러옵니다.
	std::list<CSharedPtr<CSceneObject>>::iterator	iter;
	std::list<CSharedPtr<CSceneObject>>::iterator	iterEnd = mObjList.end();

	// 오브젝트 목록들을 반복합니다.
	for (iter = mObjList.begin(); iter != iterEnd; ++iter)
	{
		// 오브젝트의 마지막 프레임을 검사합니다.
		(*iter)->EndFrame();
	}
}

bool CScene::InitAsset()
{
	return false;
}

bool CScene::InitObject()
{
	return false;
}

bool CScene::InitWidget()
{
	return false;
}
