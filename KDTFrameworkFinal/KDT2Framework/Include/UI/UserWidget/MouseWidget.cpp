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

bool CMouseWidget::Init()
{
    CUserWidget::Init();

    // 마우스 이미지 데이터 추가
    mImage = CSceneUIManager::CreateWidgetStatic<CImage>("Mouse");

    // 마우스 이미지 변경
    mImage->SetTexture("MouseDefault", 
        TEXT("Texture\\Mouse\\Default\\MouseCrossHair.png"));

    // 마우스 이미지 및 중심 설정
    mImage->SetSize(32.f, 32.f);
    mImage->SetPivot(0.5f, -0.5f);

    // 마우스 이미지로 위젯 추가.
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
