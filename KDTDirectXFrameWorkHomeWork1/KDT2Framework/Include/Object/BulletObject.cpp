#include "BulletObject.h"
#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"

CBulletObject::CBulletObject()
{
}

CBulletObject::CBulletObject(const CBulletObject& Obj)  :
    CSceneObject(Obj)
{
}

CBulletObject::CBulletObject(CBulletObject&& Obj) :
    CSceneObject(Obj)
{
}

CBulletObject::~CBulletObject()
{
}

bool CBulletObject::Init()
{
    mPlayer = CreateComponent<CPlayerObject>();

    mRoot = CreateComponent<CStaticMeshComponent>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(0.5f, 0.5f, 1.f);

    SetRootComponent(mRoot);

    return true;
}

void CBulletObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Rot = mRoot->GetWorldRotation();

    Pos.y += (mSpeed * DeltaTime);

    mRoot->SetWorldPos(Pos);
    mRoot->SetWorldRotation(Rot);
}
