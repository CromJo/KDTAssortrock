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
	float mRatio = 0.f;			// Index Max�� ���� ���� 0~1 �Դٸ� ���ٸ�

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

	// ��Ƽ���� Max��ŭ ������
	// ��Ƽ���� ���� ���� ������ Index�� �ҷ����� ����� ������ ��.

	void AddCurrentIndex();
	// ������ ���� ����� �ؽ�ó�� ����
	void PercentRatio();
};
