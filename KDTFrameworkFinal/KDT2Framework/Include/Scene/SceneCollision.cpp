#include "SceneCollision.h"
#include "../Component/ColliderBase.h"
#include "CollisionQuadTree.h"
#include "SceneUIManager.h"
#include "Input.h"

CSceneCollision::CSceneCollision()
{
}

CSceneCollision::~CSceneCollision()
{
    SAFE_DELETE(mQuadTree);
}

/// <summary>
/// 씬 충돌체를 추가하는 기능.
/// 1. 추가할 때 2D인지 3D인지 구분한다.
/// </summary>
/// <param name="Collider"></param>
void CSceneCollision::AddCollider(CColliderBase* Collider)
{
    // 만약 2D충돌체를 받아왔다면
    // 2D 충돌체 목록에 추가하라.
    if (Collider->GetColliderType() == EColliderType::Colider2D)
        mColliderList2D.emplace_back(Collider);
    // 2D 충돌체를 못받아왔다면,
    // 3D 충돌체 목록에 추가하라.
    else
        mColliderList3D.emplace_back(Collider);
}

/// <summary>
/// 씬 충돌체를 초기화.
/// </summary>
/// <returns></returns>
bool CSceneCollision::Init()
{
    // 쿼드트리를 생성한다.
    mQuadTree = new CCollisionQuadTree;

    // 쿼드트리의 씬을 현재씬으로 한다.
    mQuadTree->mScene = mScene;

    // 쿼드트리를 초기화한다.
    mQuadTree->Init();

    // 이그젝틀리
    return true;
}

/// <summary>
/// 씬충돌체를 업데이트한다.
/// 
/// </summary>
/// <param name="DeltaTime"></param>
/// <param name="UIManager"></param>
/// <param name="Input"></param>
void CSceneCollision::Update(float DeltaTime, CSceneUIManager* UIManager,
    CInput* Input)
{
    // 
    if (mInterval > 0.f)
    {
        // 흐른시간을 재서
        mIntervalTime += DeltaTime;

        // 흐른시간이 작동 간격을 못넘겼을 경우 종료
        if (mIntervalTime < mInterval)
            return;

        // 작동 간격을 넘겼다면 간격만큼 빼주고 하위 실행
        mIntervalTime -= mInterval;
    }

    // 쿼드트리 업데이트
    mQuadTree->Update(DeltaTime);

    // 2D충돌체 갯수를 받아온다.
    size_t Size = mColliderList2D.size();

    // 2D 충돌체 갯수만큼 실행
    for (size_t i = 0; i < Size;)
    {
        // 2D 충돌체들 중 활성화 되지 않은 객체는 
        // 갯수를 빼준다.
        if (!mColliderList2D[i]->IsActive())
        {
            if (i < Size - 1)
            {
                /*CSharedPtr<CColliderBase> Temp = mColliderList2D[i];
                mColliderList2D[i] = mColliderList2D[Size - 1];
                mColliderList2D[Size - 1] = Temp;*/
                mColliderList2D[i] = mColliderList2D[Size - 1];
            }
            mColliderList2D.pop_back();
            --Size;
            continue;
        }
        // 2D 충돌체 중 그려지지(?) 않은 것들은
        // 살려는 드릴께
        else if (!mColliderList2D[i]->IsEnable())
        {
            ++i;
            continue;
        }

        // 쿼드트리에 추가한다.
        mQuadTree->AddCollider(mColliderList2D[i]);

        // 다음으로 진행시켜
        ++i;
    }

    // 마우스와 UI의 충돌을 진행한다.
    FVector2D   MousePos = Input->GetMousePos();
    bool Result = UIManager->CollisionMouse(DeltaTime, MousePos);

    // 마우스 월드 위치값을 받아온다.
    FVector2D   MouseWorldPos = Input->GetMouseWorldPos2D();

    // 모든 충돌체가 쿼드트리의 노드에 추가되었기 때문에
    // 충돌처리를 진행한다.
    mQuadTree->Collision(DeltaTime);
}

/// <summary>
/// 씬의 충돌체를 그려준다.
/// </summary>
void CSceneCollision::Render()
{
    mQuadTree->Render();
}

/// <summary>
/// 씬 충돌체의 쿼드트리를 4분할 기능을 작동시킵니다.
/// </summary>
void CSceneCollision::ReturnNodePool()
{
    mQuadTree->ReturnNodePool();
}
