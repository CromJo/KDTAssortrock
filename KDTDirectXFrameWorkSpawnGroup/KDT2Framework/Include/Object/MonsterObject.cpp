#include "MonsterObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "../Component/ColliderAABB2D.h"

CMonsterObject::CMonsterObject()
{
}

CMonsterObject::CMonsterObject(const CMonsterObject& Obj)   :
    CSceneObject(Obj)
{
}

CMonsterObject::CMonsterObject(CMonsterObject&& Obj) :
    CSceneObject(Obj)
{
}

CMonsterObject::~CMonsterObject()
{
}

bool CMonsterObject::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    mBody = CreateComponent<CColliderAABB2D>();

    // 몬스터 렌더링 객체 생성
    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");
    // 크기 설정
    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);

    // 충돌용 객체 생성
    mBody->SetCollisionProfile("Monster");
    mBody->SetBoxSize(100.f, 100.f);
    // 충돌이벤트 추가.
    mBody->SetCollisionBeginFunc<CMonsterObject>(this,
        &CMonsterObject::CollisionMonster);
    // 몬스터 객체로 충돌용 객체 추가.
    mRoot->AddChild(mBody);

    return true;
}

void CMonsterObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
    // 타겟이 있으면
    if (mTarget)
    {
        if (!mTarget->IsActive())
            mTarget = nullptr;
    }
}

float CMonsterObject::Damage(float Attack,
    CSceneObject* Obj)
{
    float Dmg = CSceneObject::Damage(Attack, Obj);

    mHP -= (int)Dmg;

    if (mHP <= 0)
        Destroy();

    return Dmg;
}

void CMonsterObject::CollisionMonster(
    const FVector3D& HitPoint, CColliderBase* Dest)
{
}
