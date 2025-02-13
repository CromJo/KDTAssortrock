#include "WallObject.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "../Component/StaticMeshComponent.h"

CWallObject::CWallObject()
{
}

CWallObject::CWallObject(const CWallObject& Obj) :
    CSceneObject(Obj)
{
}

CWallObject::CWallObject(CWallObject&& Obj) :
    CSceneObject(Obj)
{
}

CWallObject::~CWallObject()
{
}

bool CWallObject::Init()
{
    HWND hWnd = GetConsoleWindow();

    if (!hWnd)
        return false;

    mRoot = CreateComponent<CStaticMeshComponent>();
    mBody = CreateComponent<CColliderOBB2D>();
    mLine = CreateComponent<CColliderLine2D>();

    mRoot->SetMesh("CenterTexRect");
    mRoot->AddTexture(0, "Teemo", TEXT("Texture/teemo.png"), 0);
    mRoot->SetOpacity(0, 0.5f);
    mRoot->SetWorldPos(0.f, 0.f, 0.f);
    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    mLine->SetCollisionProfile("Player");
    //mLine->SetRelativePos(0.f, 50.f);
    //mLine->SetLineDistance(300.f);
    
    RECT rect;
    
    if (GetClientRect(hWnd, &rect))
    {
        mLine->SetLineDistance(rect.left);
        mLine->SetLineDistance(rect.right);
        mLine->SetLineDistance(rect.top);
    }

    return true;
}

void CWallObject::Update(float DeltaTime)
{
}

void CWallObject::Damage(int Dmg)
{
}
