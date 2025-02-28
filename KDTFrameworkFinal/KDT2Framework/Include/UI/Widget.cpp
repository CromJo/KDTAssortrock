#include "Widget.h"
#include "../Shader/ShaderManager.h"
#include "../Shader/Shader.h"
#include "../Shader/UICBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneAssetManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Mesh/MeshManager.h"
#include "../Asset/Mesh/Mesh.h"
#include "../Shader/TransformCBuffer.h"

FMatrix CWidget::mUIProj;

CWidget::CWidget()
{
}

CWidget::~CWidget()
{
    SAFE_DELETE(mTransformCBuffer);
    SAFE_DELETE(mUICBuffer);
}

void CWidget::SetShader(const std::string& Name)
{
    mShader = CShaderManager::GetInst()->FindShader(Name);
}

void CWidget::SetShader(CShader* Shader)
{
    mShader = Shader;
}

bool CWidget::Init()
{
    SetShader("UIShader");
    
    // 씬이 존재하면, 씬의 메쉬 찾기
    if (mScene)
        mMesh = mScene->GetAssetManager()->FindMesh("SpriteRect");
    // 씬이 존재하지 않으면, 기본 메쉬 찾기
    else
        mMesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh("SpriteRect");

    mUICBuffer = new CUICBuffer;

    mUICBuffer->Init();

    mTransformCBuffer = new CTransformCBuffer;

    mTransformCBuffer->Init();

    return true;
}

void CWidget::Update(float DeltaTime)
{
}

// 출력
void CWidget::Render()
{
    // 상위 객체가 있으면
    if (mParent)
    {
        // 출력위치 = 상위객체위치 + 내 위치
        mRenderPos = mParent->GetRenderPos() + mPos;
    }
    // 상위 객체가 없으면
    else
    {
        // 출력위치 = 내 위치
        mRenderPos = mPos;
    }
}

void CWidget::Render(const FVector3D& Pos)
{
    if (mParent)
    {
        mRenderPos = mParent->GetRenderPos() + mPos;
    }

    else
    {
        mRenderPos = mPos;
    }

}

// 마우스 인터렉션 기능
bool CWidget::CollisionMouse(CWidget** Result, const FVector2D& MousePos)
{
    if (mParent)
    {
        mRenderPos = mParent->GetRenderPos() + mPos;
    }

    else
    {
        mRenderPos = mPos;
    }

    // 회전된 값이 완전 정방향이라면
    if (mRotation == 0.f || mRotation == 360.f)
    {
        // 사각형 정보를 만든다.
        FVector2D   Min = mRenderPos - mSize * mPivot;
        FVector2D   Max = Min + mSize;

        // 상자의 왼쪽 끝보다 더 왼쪽일경우
        if (MousePos.x < Min.x)
        {
            if (mMouseOn)
            {
                mMouseOn = false;
                MouseUnHovered();
            }

            return false;
        }
        // 상자의 오른쪽 끝보다 더 오른쪽일 경우
        else if (MousePos.x > Max.x)
        {
            if (mMouseOn)
            {
                mMouseOn = false;
                MouseUnHovered();
            }

            return false;
        }
        // 상자의 아래보다 더 아래일 경우
        else if (MousePos.y < Min.y)
        {
            if (mMouseOn)
            {
                mMouseOn = false;
                MouseUnHovered();
            }

            return false;
        }
        // 상자의 위보다 더 위일 경우
        else if (MousePos.y > Max.y)
        {
            if (mMouseOn)
            {
                mMouseOn = false;
                MouseUnHovered();
            }

            return false;
        }

        // 위조건들이 다 만족하지 않는다면,
        // 상자안에 마우스가 들어왔음을 암시한다.

        // 결과
        *Result = this;
        mMouseOn = true;
        MouseHovered();

        return true;
    }

    // 회전이 있을 경우 OBB로 처리한다.
    FVector3D   OriginAxis[2];
    FVector2D   Axis[2];
    FVector2D   HalfSize = mSize * 0.5f;
    FVector2D   Center = mRenderPos - mSize * mPivot + HalfSize;

    FMatrix matRot;
    matRot.RotationZ(mRotation);

    OriginAxis[0] = FVector3D::Axis[EAxis::X];
    OriginAxis[1] = FVector3D::Axis[EAxis::Y];

    OriginAxis[0] = OriginAxis[0].TransformNormal(matRot);
    OriginAxis[1] = OriginAxis[1].TransformNormal(matRot);

    Axis[0].x = OriginAxis[0].x;
    Axis[0].y = OriginAxis[0].y;
    Axis[1].x = OriginAxis[1].x;
    Axis[1].y = OriginAxis[1].y;

    Axis[0].Normalize();
    Axis[1].Normalize();

    // 위에서 준비한 OBB 정보를 이용해서 마우스 위치와 충돌처리를 한다.
    // 분리축 후보는 상자 축의 X, Y 축이다.
    FVector2D   CenterLine = Center - MousePos;

    float CenterProjectionDist = abs(CenterLine.Dot(Axis[0]));

    if (CenterProjectionDist > HalfSize.x)
    {
        if (mMouseOn)
        {
            mMouseOn = false;
            MouseUnHovered();
        }

        return false;
    }

    CenterProjectionDist = abs(CenterLine.Dot(Axis[1]));

    if (CenterProjectionDist > HalfSize.y)
    {
        if (mMouseOn)
        {
            mMouseOn = false;
            MouseUnHovered();
        }

        return false;
    }

    *Result = this;
    mMouseOn = true;
    MouseHovered();

    return true;
}

void CWidget::EndFrame()
{
}

void CWidget::MouseHovered()
{
}

void CWidget::MouseUnHovered()
{
}
