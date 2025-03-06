#include "CameraManager.h"
#include "../Component/CameraComponent.h"

CCameraManager::CCameraManager()
{
}

CCameraManager::~CCameraManager()
{
}

/// <summary>
/// 카메라 월드 포지션 받아오는 함수
/// </summary>
/// <returns></returns>
const FVector3D& CCameraManager::GetCameraWorldPos() const
{
	if (!mViewTarget)
		return FVector3D::Zero;

	return mViewTarget->GetWorldPosition();
}

/// <summary>
/// 행렬 값 반환 함수
/// </summary>
/// <returns></returns>
const FMatrix& CCameraManager::GetViewMatrix() const
{
	if (!mViewTarget)
		return mIdentity;

	return mViewTarget->GetViewMatrix();
}

/// <summary>
/// 투영 값 반환 함수
/// </summary>
/// <returns></returns>
const FMatrix& CCameraManager::GetProjMatrix() const
{
	// 바라볼 타겟이 없으면 기본 행렬값 반환
	if (!mViewTarget)
		return mIdentity;

	// 타겟이 존재하면 타겟의 투영행렬값 반환
	return mViewTarget->GetProjMatrix();
}

/// <summary>
/// 카메라 렌더 설정
/// </summary>
/// <param name="ViewTarget"></param>
void CCameraManager::SetViewTarget(CCameraComponent* ViewTarget)
{
	mViewTarget = ViewTarget;
}

bool CCameraManager::Init()
{
	mIdentity = FMatrix::StaticIdentity();

	return true;
}

void CCameraManager::Update(float DeltaTime)
{
	if (mViewTarget)
	{
		if (!mViewTarget->IsActive())
			mViewTarget = nullptr;
	}
}
