#include "BackgroundObject.h"
#include "../Component/SpriteComponent.h"

CBackgroundObject::CBackgroundObject()
{
}

CBackgroundObject::CBackgroundObject(const CBackgroundObject& Obj)
{
}

CBackgroundObject::CBackgroundObject(CBackgroundObject&& Obj)
{
}

CBackgroundObject::~CBackgroundObject()
{
}

bool CBackgroundObject::Init()
{
    CSceneObject::Init();

    mRoot = CreateComponent<CSpriteComponent>("Background");

    mRoot->SetTexture("Background", TEXT("Texture/Background/Nikke_Background.png"));

    mRoot->SetWorldPos(0.f, 0.f, 0.f);
    // 기본사이즈의 1.2배 해줌.
    mRoot->SetWorldScale(1280.f * 2.f, 640.f * 2.f, 1.f);
    mRoot->SetPivot(0.5f, 0.5f);
    SetRootComponent(mRoot);

    mRoot->SetRenderLayerName("BackGround");
    return true;
}
