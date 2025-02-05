#include "SceneCollision.h"
#include "../Component/ColliderBase.h"
#include "CollisionQuadTree.h"

CSceneCollision::CSceneCollision()
{
}

CSceneCollision::~CSceneCollision()
{
    // 쿼드 트리 데이터 해제
    SAFE_DELETE(mQuadTree);
}

void CSceneCollision::AddCollider(CColliderBase* Collider)
{
    // 2D 충돌체를 벡터 맨뒷열에 추가.
    if (Collider->GetColliderType() == EColliderType::Colider2D)
        mColliderList2D.emplace_back(Collider);
    // 3D 충돌체를 벡터 맨 뒷열에 추가.
    else
        mColliderList3D.emplace_back(Collider);
}

bool CSceneCollision::Init()
{
    // 힙 메모리에 할당 후 객체 초기화 해줌
    mQuadTree = new CCollisionQuadTree;
    // 초기설정 해줌
    mQuadTree->Init();

    return true;
}

void CSceneCollision::Update(float DeltaTime)
{
    // 2D 객체 몇개인지 받아옴
    // ※ 현재 3D객체는 딱히 안세는 중
    size_t Size = mColliderList2D.size();

    // 2D 객체 갯수 만큼 체크
    for (size_t i = 0; i < Size;)
    {
        // 비활성화 되어있는지 체크
        if (!mColliderList2D[i]->IsActive())
        {
            CColliderBase* Temp = mColliderList2D[i];
            mColliderList2D[i] = mColliderList2D[Size - 1];
            mColliderList2D[Size - 1] = Temp;
            mColliderList2D.pop_back();
            --Size;
            continue;
        }
        // 활성화 되어있는지 체크
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
