#include "GuageInfo.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"
#include "../../Animation/Animation2D.h"

CGuageInfo::CGuageInfo()
{
}

CGuageInfo::~CGuageInfo()
{
}

bool CGuageInfo::Init()
{
    mGuageBar = mScene->GetUIManager()->CreateWidget<CImage>
        ("GuageBar");
    
    mGuageBar->SetSize(150.f, 20.f);
    mGuageBar->SetPivot(0.5f, 0.5f);
    //mGuageBar->SetTint(EProgressBarImageType::Back, 0.3f, 0.3f, 0.3f);
    //mGuageBar->SetTexture(EProgressBarImageType::Fill, "Guage",
    //    TEXT("Texture\\UI\\Attack_Guage_0.png"));
    mGuageBar->SetTexture("AttackGuage", TEXT("Texture\\UI\\Attack_Guage_0.png"));
    AddWidget(mGuageBar);

    return true;
}

void CGuageInfo::Render()
{
    CUserWidget::Render();
}

void CGuageInfo::Render(const FVector3D& Pos)
{
    CUserWidget::Render(Pos);
}

void CGuageInfo::SetCurrentIndex(int current)
{
    mCurrentImageIndex = current;
}

void CGuageInfo::SetIndexMax(int max)
{
    mImageIndexMax = max;
}

void CGuageInfo::SetRatio(float ratio)
{
    mRatio = ratio;
    PercentRatio();
}

void CGuageInfo::AddCurrentIndex()
{
    mCurrentImageIndex++;
}

void CGuageInfo::PercentRatio()
{
    // Index가 아닌 Count로
    // TODO: +1 빼도 의미 없으면 빼자

    // ex) mImageIndexMax = 10;
    int ImageCountMax = mImageIndexMax + 1;
    // 내림
    int Frame = floorf(mRatio * (float)ImageCountMax);
    
    mRatio /= ImageCountMax;

}
