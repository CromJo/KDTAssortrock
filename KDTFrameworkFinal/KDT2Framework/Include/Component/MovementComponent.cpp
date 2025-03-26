﻿#include "MovementComponent.h"
#include "SceneComponent.h"
#include "NavAgent.h"

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

void CMovementComponent::SetUpdateComponent(CSceneComponent* Target)
{
    mUpdateComponent = Target;
}

/// <summary>
/// 이동할 좌표를 설정
/// </summary>
/// <param name="Pos"></param>
void CMovementComponent::SetMovePoint(const FVector2D& Pos)
{
    // 업데이트 컴포넌트가 있는지 체크
    if (mUpdateComponent)
    {
        // 있다면
        // 현재 월드 좌표를 받아온다.
        FVector2D   WorldPos;
        WorldPos.x = mUpdateComponent->GetWorldPosition().x;
        WorldPos.y = mUpdateComponent->GetWorldPosition().y;
        // 위치를 찾는다.
        FindPath(WorldPos, Pos);

        if (!mPathList.empty())
        {
            mTargetDist = WorldPos.Distance(mPathList.front());
        }
    }
}

void CMovementComponent::SetMoveRandomPoint(const FVector3D& Pos)
{
    // 업데이트 컴포넌트가 있는지 체크
    if (mUpdateComponent)
    {
        // 있다면
        // 현재 월드 좌표를 받아온다.
        FVector3D   WorldPos = mUpdateComponent->GetWorldPosition();
        
        SetMove(Pos);
    }
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

    if (mUpdateComponent)
    {
        if (!mUpdateComponent->IsActive())
            mUpdateComponent = nullptr;
    }
}

void CMovementComponent::Update(float DeltaTime)
{
    CComponent::Update(DeltaTime);

    if (mUpdateComponent)
    {
        if (!mUpdateComponent->IsActive())
            mUpdateComponent = nullptr;

        else
        {
            // 이동경로 목록이 비어있고
            if (mPathList.empty())
            {
                // 이동 방향이 존재한다면
                if (mMoveAxis != EAxis::None)
                {
                    // 이동방향을 업데이트 하라.
                    mVelocity = mUpdateComponent->GetAxis(mMoveAxis);

                }

                // 이동거리를 정규화 시켜서
                mVelocity.Normalize();

                // 이동거리가 0이아니라면
                if (mVelocity.Length() > 0.f)
                {
                    // 거리 비례로 이동하라.
                    mMoveStep = mVelocity * mSpeed * DeltaTime;
                }

                // Old
                // 기존의 값에 이동값을 추가하는 기능
                mUpdateComponent->AddWorldPos(mMoveStep);
                //mUpdateComponent->SetWorldPos(mMoveStep);
            }
            // 이동경로목록이 존재한다면
            else
            {
                // 이동 경로 목록의 위치를 받아와,
                FVector3D   Target;
                Target.x = mPathList.front().x;
                Target.y = mPathList.front().y;

                // 수식을 돌려주고
                FVector3D   Dir = Target - 
                    mUpdateComponent->GetWorldPosition();
                Dir.Normalize();

                mMoveStep = Dir * mSpeed * DeltaTime;

                float   StepLength = mMoveStep.Length();

                if (StepLength >= mTargetDist)
                {
                    FVector2D   _Target = mPathList.front();

                    mPathList.pop_front();

                    if (!mPathList.empty())
                    {
                        mTargetDist = _Target.Distance(mPathList.front());
                    }

                    mUpdateComponent->SetWorldPos(Target);
                }

                else
                {
                    mTargetDist -= StepLength;

                    mUpdateComponent->AddWorldPos(mMoveStep);
                }
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
    }
}

CMovementComponent* CMovementComponent::Clone()
{
    return new CMovementComponent(*this);
}

void CMovementComponent::EndFrame()
{
    CComponent::EndFrame();

    if (mVelocityInit)
        mVelocity = FVector3D::Zero;

    mMoveStep = FVector3D::Zero;
}
