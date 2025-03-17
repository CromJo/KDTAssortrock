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

/// <summary>
/// 카메라 초기화
/// 1. 단위 행렬을 받아옵니다.
/// </summary>
/// <returns></returns>
bool CCameraManager::Init()
{
	// 단위 행렬을 받아옵니다.
	mIdentity = FMatrix::StaticIdentity();

	return true;
}

/// <summary>
/// 카메라 업데이트
/// </summary>
/// <param name="DeltaTime"></param>
void CCameraManager::Update(float DeltaTime)
{
	// 바라볼 타겟이 존재하지만,
	if (mViewTarget)
	{
		// 타겟이 활성화되어 있지 않다면,
		// 바라볼게 없음을 인지하라.
		if (!mViewTarget->IsActive())
			mViewTarget = nullptr;
	}
}
