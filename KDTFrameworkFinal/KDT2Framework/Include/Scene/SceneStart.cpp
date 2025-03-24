#include "SceneStart.h"
#include "../UI/UserWidget/StartWidget.h"
#include "SceneUIManager.h"

CSceneStart::CSceneStart()
{
}

CSceneStart::~CSceneStart()
{
}

/// <summary>
/// 메인메뉴 씬의 에셋을 초기화
/// 1. 현재 에셋불러올게 없음 
/// </summary>
/// <returns></returns>
bool CSceneStart::InitAsset()
{
    return true;
}

/// <summary>
/// 메인메뉴 씬의 오브젝트를 초기화
/// 1. 현재 오브젝트 배치가 없음
/// </summary>
/// <returns></returns>
bool CSceneStart::InitObject()
{
    return true;
}

/// <summary>
/// 메인메뉴 씬의 UI 위젯들을 초기화
/// 1. 스타트 위젯에 버튼들을 배치해놨음.
/// </summary>
/// <returns></returns>
bool CSceneStart::InitWidget()
{
    CStartWidget* Widget = mUIManager->CreateWidget<CStartWidget>("Start");

    // 초기 메인화면 설정
    mUIManager->AddToViewport(Widget);

    return true;
}
