#include "MouseWidget.h"
#include "../Common/Image.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Input.h"
#include "../../Scene/SceneUIManager.h"
#include "../../Scene/SceneManager.h"

CMouseWidget::CMouseWidget()
{
}

CMouseWidget::~CMouseWidget()
{
}

/// <summary>
/// 마우스 초기화
/// </summary>
/// <returns></returns>
bool CMouseWidget::Init()
{
    CUserWidget::Init();

    // 마우스 이미지 데이터 생성
    mImage = CSceneUIManager::CreateWidgetStatic<CImage>("Mouse");

    // 마우스 이미지 설정
    mImage->SetTexture("MouseDefault", 
        TEXT("Texture\\Mouse\\Default\\0.png"));

    // 이미지 크기 설정
    mImage->SetSize(32.f, 32.f);

    AddWidget(mImage);

    return true;
}

void CMouseWidget::Update(float DeltaTime)
{
    CUserWidget::Update(DeltaTime);

	CInput* Input = 
		CSceneManager::GetInst()->GetCurrentScene()->GetInput();

	FVector2D MousePos = Input->GetMousePos();

	SetPos(MousePos.x, MousePos.y - 32.f);
}
