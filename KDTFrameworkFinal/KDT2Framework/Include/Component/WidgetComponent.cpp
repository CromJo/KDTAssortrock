#include "WidgetComponent.h"

// 생성자 
CWidgetComponent::CWidgetComponent()
{
    mRenderType = EComponentRender::Render;
    mRenderLayerName = "Object";
}

CWidgetComponent::CWidgetComponent(const CWidgetComponent& Com) :
    CSceneComponent(Com)
{
}

CWidgetComponent::CWidgetComponent(CWidgetComponent&& Com) :
    CSceneComponent(Com)
{
}

CWidgetComponent::~CWidgetComponent()
{
}

bool CWidgetComponent::Init()
{
    CSceneComponent::Init();

    return true;
}

// 위젯 업데이트 (Update 구현 X)
void CWidgetComponent::Update(float DeltaTime)
{
    CSceneComponent::Update(DeltaTime);

    if (mWidget)
        mWidget->Update(DeltaTime);
}

// 위젯 출력
void CWidgetComponent::Render()
{
    CSceneComponent::Render();
   
    if (mWidget)
        mWidget->Render(mWorldPos);
}
