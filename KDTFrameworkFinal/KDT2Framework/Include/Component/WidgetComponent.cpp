#include "WidgetComponent.h"

// ������ 
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

// ���� ������Ʈ (Update ���� X)
void CWidgetComponent::Update(float DeltaTime)
{
    CSceneComponent::Update(DeltaTime);

    if (mWidget)
        mWidget->Update(DeltaTime);
}

// ���� ���
void CWidgetComponent::Render()
{
    CSceneComponent::Render();
   
    if (mWidget)
        mWidget->Render(mWorldPos);
}
