#pragma once
#include "UserWidget.h"
#include "../Common/TextBlock.h"
#include "../Common/Image.h";

class CGuageInfo :
	public CUserWidget
{
	friend class CSceneUIManager;

private:
	int mCurrentImageIndex = 0;
	int mImageIndexMax = 0;
	float mRatio = 0.f;			// Index Max의 나눈 비율 0~1 왔다리 갔다리

protected:
	CGuageInfo();
	virtual ~CGuageInfo();

protected:
	CSharedPtr<CImage>	mGuageBar;
	class CAnimation2D* mAnimation = nullptr;

public:
	virtual bool Init();
	virtual void Render();
	virtual void Render(const FVector3D& Pos);

	void SetCurrentIndex(int current);
	void SetIndexMax(int max);
	void SetRatio(float ratio);

	// 라티오를 Max만큼 나눠서
	// 라티오의 값의 가장 근접한 Index를 불러오는 기능을 만들어야 함.

	void AddCurrentIndex();
	// 비율에 가장 가까운 텍스처로 갱신
	void PercentRatio();
};
