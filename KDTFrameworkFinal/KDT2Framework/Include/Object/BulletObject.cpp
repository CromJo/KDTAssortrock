#include "BulletObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Share/Log.h"
#include "../Component/SpriteComponent.h"
#include "SpriteEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"

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

void CBulletObject::SetBulletCollisionProfile(
    const std::string& Name)
{
    mBody->SetCollisionProfile(Name);
}

bool CBulletObject::Init()
{
    mRoot = CreateComponent<CSpriteComponent>();
    mBody = CreateComponent<CColliderAABB2D>();

    mMovement = CreateComponent<CMovementComponent>();

    /*mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");*/

    // 이미지 및 중심 설정
    mRoot->SetTexture("Bullet", TEXT("Texture/block_ball.png"));
    mRoot->SetPivot(0.5f, 0.5f);

    mRoot->SetWorldScale(0.5f, 0.5f, 1.f);

    SetRootComponent(mRoot);

    // 총알의 실제 충돌 범위 설정
    mBody->SetBoxSize(50.f, 50.f);

    mBody->SetCollisionBeginFunc<CBulletObject>(this,
        &CBulletObject::CollisionBullet);

    mRoot->AddChild(mBody);

    // 총알의 움직임 추가 
    mMovement->SetUpdateComponent(mRoot);
    // 움직임 관련 설정 
    // (MoveAxis를 마우스의 위치 값으로 깊이를 넣어줘야함.)
    mMovement->SetMoveAxis(EAxis::Y);
    //FVector2D MoveBullet = mScene->GetInput()->GetMouseWorldPos2D();
    //mMovement->SetMovePointZ(MoveBullet);
    mMovement->SetMoveSpeed(500.f);

    return true;
}

void CBulletObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    /*FVector3D Pos = mRoot->GetWorldPosition();

    Pos += mRoot->GetAxis(EAxis::Y) * mSpeed * DeltaTime;

    mRoot->SetWorldPos(Pos);*/
}

void CBulletObject::CollisionBullet(const FVector3D& HitPoint,
    CColliderBase* Dest)
{
    CLog::PrintLog("Collision");

    Dest->GetOwner()->Damage(1.f, this);

    CSpriteEffect* Effect = mScene->CreateObj<CSpriteEffect>("HitEffect");

    Effect->SetAnimation("Explosion");

    Effect->SetWorldPos(HitPoint);
    Effect->SetWorldScale(100.f, 100.f);

    Destroy();
}
