#include "Button.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneAssetManager.h"
#include "../../Asset/AssetManager.h"
#include "../../Asset/Texture/Texture.h"
#include "../../Asset/Texture/TextureManager.h"
#include "../../Asset/Sound/Sound.h"
#include "../../Asset/Sound/SoundManager.h"
#include "../../Asset/Mesh/Mesh.h"
#include "../../Shader/UICBuffer.h"
#include "../../Shader/TransformCBuffer.h"
#include "../../Shader/Shader.h"
#include "../../Scene/Input.h"

CButton::CButton()
{
}

CButton::~CButton()
{
}

void CButton::SetTexture(EButtonState::Type State, const std::string& Name)
{
    if (mScene)
        mBrush[State].Texture = mScene->GetAssetManager()->FindTexture(Name);

    else
        mBrush[State].Texture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);
}

void CButton::SetTexture(EButtonState::Type State, 
    const std::string& Name, const TCHAR* FileName)
{
    if (mScene)
    {
        if (!mScene->GetAssetManager()->LoadTexture(Name, FileName))
            return;

        mBrush[State].Texture = mScene->GetAssetManager()->FindTexture(Name);
    }

    else
    {
        if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(Name, FileName))
            return;

        mBrush[State].Texture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);
    }
}

void CButton::SetTexture(EButtonState::Type State, CTexture* Texture)
{
    if (mScene)
        mBrush[State].Texture = Texture;

    else
        mBrush[State].Texture = Texture;
}

void CButton::SetTint(EButtonState::Type State, float r, float g, float b)
{
    mBrush[State].Tint.x = r;
    mBrush[State].Tint.y = g;
    mBrush[State].Tint.z = b;
}

void CButton::SetOpacity(EButtonState::Type State, float Opacity)
{
    mBrush[State].Tint.w = Opacity;
}

void CButton::SetBrushAnimation(EButtonState::Type State, bool Animation)
{
    mBrush[State].AnimationEnable = Animation;
}

void CButton::AddBrushFrame(EButtonState::Type State, 
    const FVector2D& Start, const FVector2D& Size)
{
    FAnimationFrame Frame;
    Frame.Start = Start;
    Frame.Size = Size;

    mBrush[State].Frames.emplace_back(Frame);

    mBrush[State].FrameTime = mBrush[State].PlayTime /
        mBrush[State].Frames.size();
}

void CButton::AddBrushFrame(EButtonState::Type State, 
    float StartX, float StartY, float SizeX, float SizeY)
{
    FAnimationFrame Frame;
    Frame.Start.x = StartX;
    Frame.Start.y = StartY;
    Frame.Size.x = SizeX;
    Frame.Size.y = SizeY;

    mBrush[State].Frames.emplace_back(Frame);

    mBrush[State].FrameTime = mBrush[State].PlayTime /
        mBrush[State].Frames.size();
}

void CButton::SetCurrentFrame(EButtonState::Type State, int Frame)
{
    mBrush[State].Frame = Frame;
}

void CButton::SetAnimationPlayTime(EButtonState::Type State, float PlayTime)
{
    mBrush[State].PlayTime = PlayTime;

    mBrush[State].FrameTime = mBrush[State].PlayTime /
        mBrush[State].Frames.size();
}

void CButton::SetAnimationPlayRate(EButtonState::Type State, float PlayRate)
{
    mBrush[State].PlayRate = PlayRate;
}

void CButton::SetSound(EButtonEventState::Type State,
    const std::string& Name)
{
    if (mScene)
        mSound[State] = mScene->GetAssetManager()->FindSound(Name);

    else
        mSound[State] = CAssetManager::GetInst()->GetSoundManager()->FindSound(Name);

}

void CButton::SetSound(EButtonEventState::Type State, 
    const std::string& Name, const char* FileName)
{
    if (mScene)
    {
        if (!mScene->GetAssetManager()->LoadSound(Name, "UI", 
            false, FileName))
            return;

        mSound[State] = mScene->GetAssetManager()->FindSound(Name);
    }

    else
    {
        if (!CAssetManager::GetInst()->GetSoundManager()->LoadSound(Name, 
            "UI", false, FileName))
            return;

        mSound[State] = CAssetManager::GetInst()->GetSoundManager()->FindSound(Name);
    }
}

bool CButton::Init()
{
    CWidget::Init();

    return true;
}

/// <summary>
/// 버튼 기능 업데이트
/// </summary>
/// <param name="DeltaTime"></param>
void CButton::Update(float DeltaTime)
{
    // 위젯 업데이트 돌린 후
    CWidget::Update(DeltaTime);

    // 현재 버튼이 비활성화 상태가 아니고,
    if (mState != EButtonState::Disable)
    {   
        // 마우스가 활성화 된 상태라면
        if (mMouseOn)
        {
            // 씬의 입력기능 중 마우스 왼쪽버튼을 눌렀을때에 기능이 존재하는지 체크한다.
            if (mScene->GetInput()->GetMouseDown(EMouseButtonType::LButton))
            {
                // 있다면 현재 버튼의 특성을 클릭을 받은것으로 바꾼다.
                mState = EButtonState::Click;
            }

            // if문이 실행안된 상태에서,
            // 내 마우스 특성이 클릭한 상태이고,
            // 씬의 입력기능 중 내 마우스 왼쪽 버튼을 방금 땐 상태라면,
            else if (mState == EButtonState::Click &&
                mScene->GetInput()->GetMouseUp(EMouseButtonType::LButton))
            {
                // 클릭 이벤트 사운드가 존재한다면 사운드 실행
                if (mSound[EButtonEventState::Click])
                    mSound[EButtonEventState::Click]->Play();
                // 클릭 이벤트 콜백이 존재한다면 콜백 함수 실행.
                if (mEventCallback[EButtonEventState::Click])
                    mEventCallback[EButtonEventState::Click]();
                // 현재 버튼 특성을 마우스 올려둔 상태로 변경함.
                mState = EButtonState::Hovered;
            }
            // 씬의 입력기능 중 마우스 왼쪽버튼을 홀드하는 기능이 있다면
            else if (mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton))
            {
                // 특성 : 클릭으로 변경
                mState = EButtonState::Click;
            }
        }
    }
}

void CButton::Render()
{
    CWidget::Render();

    FMatrix matScale, matRot, matTranslate, matWorld;

    matScale.Scaling(mSize);
    matRot.RotationZ(mRotation);
    matTranslate.Translation(mRenderPos);

    matWorld = matScale * matRot * matTranslate;

    mTransformCBuffer->SetWorldMatrix(matWorld);
    mTransformCBuffer->SetProjMatrix(mUIProj);
    mTransformCBuffer->SetPivot(mPivot);

    mTransformCBuffer->UpdateBuffer();

    mUICBuffer->SetWidgetColor(mColor);

    mUICBuffer->SetTint(mBrush[mState].Tint);

    if (mBrush[mState].Texture)
    {
        mUICBuffer->SetTextureEnable(true);

        mBrush[mState].Texture->SetShader(0, EShaderBufferType::Pixel,
            0);
    }

    else
        mUICBuffer->SetTextureEnable(false);

    if (mBrush[mState].AnimationEnable)
    {
        mUICBuffer->SetAnimationEnable(true);

        int Frame = mBrush[mState].Frame;

        FAnimationFrame FrameInfo = mBrush[mState].Frames[Frame];
        mUICBuffer->SetUV(FrameInfo.Start.x, FrameInfo.Start.y,
            FrameInfo.Start.x + FrameInfo.Size.x,
            FrameInfo.Start.y + FrameInfo.Size.y);
    }

    else
        mUICBuffer->SetAnimationEnable(false);


    mUICBuffer->UpdateBuffer();

    mShader->SetShader();

    mMesh->Render();

    if (mChild)
        mChild->Render();
}

void CButton::Render(const FVector3D& Pos)
{
    CWidget::Render(Pos);

    if (mChild)
        mChild->Render(Pos);
}

void CButton::MouseHovered()
{
    if (mState == EButtonState::Normal)
    {
        if (mSound[EButtonEventState::Hovered])
            mSound[EButtonEventState::Hovered]->Play();

        if (mEventCallback[EButtonEventState::Hovered])
            mEventCallback[EButtonEventState::Hovered]();

        mState = EButtonState::Hovered;
    }
}

void CButton::MouseUnHovered()
{
    if (mState != EButtonState::Disable)
        mState = EButtonState::Normal;
}
