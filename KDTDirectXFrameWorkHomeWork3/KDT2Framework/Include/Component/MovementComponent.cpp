#include "MovementComponent.h"
#include "SceneComponent.h"

CMovementComponent::CMovementComponent()
{
}

CMovementComponent::CMovementComponent(
    const CMovementComponent& Com)  :
    CComponent(Com)
{
}

CMovementComponent::CMovementComponent(CMovementComponent&& Com) :
    CComponent(Com)
{
}

CMovementComponent::~CMovementComponent()
{
}

// Object를 받아온다.
void CMovementComponent::SetUpdateComponent(CSceneComponent* Target)
{
    mUpdateComponent = Target;
}

bool CMovementComponent::Init()
{
    if (!CComponent::Init())
        return false;

    return true;
}

bool CMovementComponent::Init(const char* FileName)
{
    if (!CComponent::Init(FileName))
        return false;

    return true;
}

void CMovementComponent::PreUpdate(float DeltaTime)
{
    CComponent::PreUpdate(DeltaTime);

    // Object가 받아와졌는지 체크
    if (mUpdateComponent)
    {
        // Object가 활성화되었는지 체크
        if (!mUpdateComponent->IsActive())
            mUpdateComponent = nullptr;

        else if (mUpdateComponent->IsEnable())
        {
        }
    }
}

void CMovementComponent::Update(float DeltaTime)
{
    CComponent::Update(DeltaTime);

    if (mUpdateComponent)
    {
        if (!mUpdateComponent->IsActive())
            mUpdateComponent = nullptr;

        // Object 활성화 된 상태면 
        // Scene에서 Object가 이동하는 것을 관장함.
        else if (mUpdateComponent->IsEnable())
        {
            // 평균화 작업
            mVelocity.Normalize();

            // 이동을 하고있다면
            if (mVelocity.Length() > 0.f)
            {
                // 방향에 속도값을 비례하여 대입
                mMoveStep = mVelocity * mSpeed * DeltaTime;
                // 이동
                mUpdateComponent->AddWorldPos(mMoveStep);
            }
        }
    }
}

void CMovementComponent::PostUpdate(float DeltaTime)
{
    CComponent::PostUpdate(DeltaTime);

    if (mUpdateComponent)
    {
        if (!mUpdateComponent->IsActive())
            mUpdateComponent = nullptr;

        else if (mUpdateComponent->IsEnable())
        {
        }
    }
}

void CMovementComponent::PostRender()
{
    CComponent::PostRender();

    mVelocity = FVector3D::Zero;
}

CMovementComponent* CMovementComponent::Clone()
{
    return new CMovementComponent(*this);
}
