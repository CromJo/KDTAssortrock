#include "CameraComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/CameraManager.h"

CCameraComponent::CCameraComponent()
{
}

CCameraComponent::CCameraComponent(const CCameraComponent& Com) :
    CSceneComponent(Com)
{
}

CCameraComponent::CCameraComponent(CCameraComponent&& Com) :
    CSceneComponent(Com)
{
}

CCameraComponent::~CCameraComponent()
{
}

/// <summary>
/// 투영 타입 설정
/// </summary>
/// <param name="Type"></param>
void CCameraComponent::SetProjectionType(
    ECameraProjectionType Type)
{
    mProjType = Type;

    switch (mProjType)
    {
        // 원근 투영방식 :
        //  DirectX 왼손 좌표계 방식으로
        //  FovAngleY    : 수직 시야각을 라디안 단위로 지정 (화면에 그려지는 시야각도)
        //  AspectRatio  : 뷰포트의 가로 세로 비율
        //  NearZ        : 카메라의 시야에서 그릴 수 있는 최소단위 (0보다 커야함)
        //  FarZ         : 카메라의 시야에서 그릴 수 있는 최대단위 (0보다 커야함)
        //  기능 : 
        //      1. FOV버전 시야각과 종횡비 사용하여 투영 평면의 크기를 계산
        //      2. 생성한 행렬은 3D 객체로 2D화면의 투영할 때 원근감 제공
        //      3. 일반적으로 NearZ < FarZ로 설정하지만,
        //          반대로 NearZ > FarZ로 설정하면,
        //          역방향 z버퍼를 생성하여 부동소수점 정밀도를 향상
    case ECameraProjectionType::Perspective:
        mmatProj = DirectX::XMMatrixPerspectiveFovLH(
            DirectX::XMConvertToRadians(mViewAngle),
            mWidth / mHeight, 0.5f, mViewDistance);
        break;
        // 직교 투영 행렬 방식 :
        //  DirectXMath 라이브러리의 왼손좌표계 방식으로,
        //  ViewLeft    : 뷰 볼륨의 최소 x값
        //  ViewRight   : 뷰 볼륨의 최대 x값
        //  ViewBottom  : 뷰 볼륨의 최소 y값
        //  ViewTop     : 뷰 볼륨의 최대 y값
        //  NearZ       : 카메라 뷰의 그릴 수 있는 최소단위 (0보다 커야함)
        //  FarZ        : 카메라 뷰의 그릴 수 있는 최대단위 (0보다 커야함)
        //  기능  : 
        //      1. 직교 튜영 행렬을 반환
        //      2. NearZ와 FarZ는 서로 다른값이여야 하고, 둘다 0보다 커야함
        //      3. 일반적으로 NearZ < FarZ로 설정하지만,
        //          반대로 NearZ > FarZ로 설정하면,
        //          역방향 z버퍼를 생성하여 부동소수점 정밀도를 향상
        //      4. 이 함수의 모든 매개변수는 카메라 공간의 거리를 나타낸다.
    case ECameraProjectionType::Ortho:
        mmatProj = DirectX::XMMatrixOrthographicOffCenterLH(mWidth / -2.f,
            mWidth / 2.f, mHeight / -2.f, mHeight / 2.f,
            0.f, mViewDistance);
        /*mmatProj = DirectX::XMMatrixOrthographicOffCenterLH(0.f,
            mWidth, 0.f, mHeight,
            0.f, mViewDistance);*/
        break;
    }
}

// 카메라 초기화
bool CCameraComponent::Init()
{
    // 씬 컴포넌트 초기화 체크
    if (!CSceneComponent::Init())
        return false;

    // 카메라의 그림 방식을 설정해준다.
    SetProjectionType(ECameraProjectionType::Perspective);

    // 현재씬의 카메라 매니저를 불러와 카메라의 방향이 존재하는지 체크한다.
    // 현재씬의 카메라 매니저를 불러와 바라볼 방향을 이 카메라로 바꿔준다.
    if (!mScene->GetCameraManager()->GetViewTarget())
        mScene->GetCameraManager()->SetViewTarget(this);

    // 진실!
    return true;
}

bool CCameraComponent::Init(const char* FileName)
{
    if (!CSceneComponent::Init())
        return false;

    SetProjectionType(ECameraProjectionType::Perspective);

    if (!mScene->GetCameraManager()->GetViewTarget())
        mScene->GetCameraManager()->SetViewTarget(this);

    return true;
}

void CCameraComponent::PreUpdate(float DeltaTime)
{
    CSceneComponent::PreUpdate(DeltaTime);
}

void CCameraComponent::Update(float DeltaTime)
{
    CSceneComponent::Update(DeltaTime);
}

void CCameraComponent::PostUpdate(float DeltaTime)
{
    CSceneComponent::PostUpdate(DeltaTime);

    /*
    뷰공간 변환이 일어날 경우 카메라는 Z+ 방향을 바라보게
    회전이 된다.
    카메라가 뷰공간으로 변환되면 카메라를 구성하는 3개의 축은
    월드의 축과 정확하게 일치한다.

    카메라X축 * 뷰행렬 = 1, 0, 0
    카메라Y축 * 뷰행렬 = 0, 1, 0
    카메라Z축 * 뷰행렬 = 0, 0, 1

    Xx Xy Xz   11 12 13   1 0 0
    Yx Yy Yz * 21 22 23 = 0 1 0
    Zx Zy Zz   31 32 33   0 0 1

    카메라 축을 이용하여 행렬을 구성하고 이를 뷰행렬을 곱하면
    결과로 항등행렬이 나온다.
    A행렬에 B를 곱했을때 항등행렬이 나오게 되면 B는 A의 역행렬이다.

    행렬을 구성하는 각 축이 서로에 90도인 행렬을 직교행렬이라고 한다.
    직교행렬은 역행렬과 전치행렬이 같다.
    Xx Yx Zx 0
    Xy Yy Zy 0
    Xz Yz Zz 0
    0  0  0  1

    1   0  0 0
    0   1  0 0
    0   0  1 0
    -x -y -z 1

    1   0  0 0   Xx Yx Zx 0   Xx   Yx   Zx   0
    0   1  0 0 * Xy Yy Zy 0 = Xy   Yy   Zy   0
    0   0  1 0   Xz Yz Zz 0   Xz   Yz   Zz   0
    -x -y -z 1   0  0  0  1   -X.P -Y.P -Z.P 1
    */
    mmatView.Identity();

    for (int i = 0; i < EAxis::End; ++i)
    {
        FVector3D   Axis = mAxis[i];
        memcpy(&mmatView[i][0], &Axis, sizeof(FVector3D));
    }

    /*
    Xx Xy Xz 0
    Yx Yy Yz 0
    Zx Zy Zz 0
    0  0  0  1
    로 구성된 행렬을 전치하여
    Xx Yx Zx 0
    Xy Yy Zy 0
    Xz Yz Zz 0
    0  0  0  1
    로 만들어준다.
    */
    mmatView.Transpose();

    for (int i = 0; i < EAxis::End; ++i)
    {
        mmatView[3][i] = -mAxis[i].Dot(mWorldPos);
    }
}

void CCameraComponent::Collision(float DeltaTime)
{
    CSceneComponent::Collision(DeltaTime);
}

void CCameraComponent::PreRender()
{
    CSceneComponent::PreRender();
}

void CCameraComponent::Render()
{
    CSceneComponent::Render();
}

void CCameraComponent::PostRender()
{
    CSceneComponent::PostRender();
}

CCameraComponent* CCameraComponent::Clone()
{
    return new CCameraComponent(*this);
}
