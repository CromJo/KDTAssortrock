#include "SceneCollision.h"
#include "../Component/ColliderBase.h"
#include "CollisionQuadTree.h"

CSceneCollision::CSceneCollision()
{
}

CSceneCollision::~CSceneCollision()
{
    SAFE_DELETE(mQuadTree);
}

void CSceneCollision::AddCollider(CColliderBase* Collider)
{
    // 2D or 3D 체크 후 데이터 삽입
    if (Collider->GetColliderType() == EColliderType::Colider2D)
        mColliderList2D.emplace_back(Collider);

    else
        mColliderList3D.emplace_back(Collider);
}

bool CSceneCollision::Init()
{
    // 쿼드트리 메모리 할당
    mQuadTree = new CCollisionQuadTree;
    // 쿼드트리 씬을 현재씬으로 설정
    mQuadTree->mScene = mScene;
    // 쿼드트리 초기설정
    mQuadTree->Init();

    return true;
}

void CSceneCollision::Update(float DeltaTime)
{
    mQuadTree->Update(DeltaTime);

    size_t Size = mColliderList2D.size();

    for (size_t i = 0; i < Size;)
    {
        if (!mColliderList2D[i]->IsActive())
        {
            CColliderBase* Temp = mColliderList2D[i];
            mColliderList2D[i] = mColliderList2D[Size - 1];
            mColliderList2D[Size - 1] = Temp;
            mColliderList2D.pop_back();
            --Size;
            continue;
        }

        else if (!mColliderList2D[i]->IsEnable())
        {
            ++i;
            continue;
        }

        // 쿼드트리에 추가한다.
        mQuadTree->AddCollider(mColliderList2D[i]);

        ++i;
    }
}
