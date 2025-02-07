#include "TeleportLine.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"

#include "../Component/ColliderLine2D.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Share/Log.h"

CTeleportLine::CTeleportLine()
{
}

CTeleportLine::CTeleportLine(const CTeleportLine& Obj) :
    CSceneObject(Obj)
{
}

CTeleportLine::CTeleportLine(CTeleportLine&& Obj) :
    CSceneObject(Obj)
{
}

CTeleportLine::~CTeleportLine()
{
}

bool CTeleportLine::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    //mLine = CreateComponent<CColliderLine2D>();
    mBody = CreateComponent<CColliderLine2D>();
    mSub = CreateComponent<CStaticMeshComponent>();
    mSub2 = CreateComponent<CStaticMeshComponent>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);

    mBody->SetCollisionProfile("TeleportLine");
    //mBody->SetLineAxis(EAxis::Y);
    mBody->SetLineDistance(20.f);

    return true;
}

void CTeleportLine::Update(float DeltaTime)
{
}

void CTeleportLine::Damage(int Dmg)
{
}
