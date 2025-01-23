#include "BulletObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"

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
    // 총알 생성 초기화
    mRoot = CreateComponent<CStaticMeshComponent>();

    // 
    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");
    
    mRoot->SetWorldScale(0.5f, 0.5f, 1.f);

    SetRootComponent(mRoot);

    return true;
}

void CBulletObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
    Movement(DeltaTime);
}

void CBulletObject::Movement(float DeltaTime)
{
    FVector3D Pos = mRoot->GetWorldPosition();

    Pos += mRoot->GetAxis(EAxis::Y) * mSpeed * DeltaTime;

    mRoot->SetWorldPos(Pos);
}
