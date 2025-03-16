#include "Animation2DSequence.h"
#include "../Asset/Animation/Animation2DData.h"
#include "../Share/Log.h"

CAnimation2DSequence::CAnimation2DSequence()
{
}

CAnimation2DSequence::CAnimation2DSequence(
	const CAnimation2DSequence& Anim)
{
	// 얕은복사를 한다.
	*this = Anim;

	mNotifyList.clear();
}

CAnimation2DSequence::~CAnimation2DSequence()
{
	size_t	Size = mNotifyList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(mNotifyList[i]);
	}
}

const std::string& CAnimation2DSequence::GetName() const
{
	return mAsset->GetName();
}

void CAnimation2DSequence::SetAsset(CAnimation2DData* Asset)
{
	mAsset = Asset;

	mFrameTime = mPlayTime / mAsset->GetFrameCount();
}

void CAnimation2DSequence::SetPlayTime(float PlayTime)
{
	mPlayTime = PlayTime;

	if (mAsset)
		mFrameTime = mPlayTime / mAsset->GetFrameCount();
}

/// <summary>
/// 애니메이션 시퀀스 업데이트 구문
/// </summary>
/// <param name="DeltaTime"></param>
void CAnimation2DSequence::Update(float DeltaTime)
{
	// 시간 증가
	mTime += DeltaTime * mPlayRate;

	// 시간 넘기면 실행
	if (mTime >= mFrameTime)
	{
		// 오차 분만큼 빼줌
		mTime -= mFrameTime;

		// 역방향 실행
		if (mReverse)
		{
			// 프레임 감소
			--mFrame;

			// 프레임이 
			if (mFrame < 0)
			{
				// 마지막 프레임이고, 
				// 마지막 프레임에 대한 이벤트가 활성화가 되어있으면 실행
				if (mEndFunction && mEndFunctionEnable)
				{
					// 이벤트가 반복 되지 않도록 끈 후, 이벤트 실행
					mEndFunctionEnable = false;
					mEndFunction();
				}
				// 반복 실행이 가능한 이벤트면
				if (mLoop)
				{	
					// 이벤트가 반복되도록 설정 후,
					// 전 프레임으로 돌려주기
					mEndFunctionEnable = true;
					mFrame = mAsset->GetFrameCount() - 1;
				}
				// 반복 실행이 불가능하면 끝내도록 설정
				else
					mFrame = 0;
			}
		}

		else
		{
			++mFrame;

			if (mFrame == mAsset->GetFrameCount())
			{
				if (mEndFunction && mEndFunctionEnable)
				{
					mEndFunctionEnable = false;
					mEndFunction();
				}

				if (mLoop)
				{
					mEndFunctionEnable = true;
					mFrame = 0;
				}

				else
					mFrame = mAsset->GetFrameCount() - 1;
			}
		}

		CallNotify();
	}
}

CAnimation2DSequence* CAnimation2DSequence::Clone()
{
	return new CAnimation2DSequence(*this);
}

void CAnimation2DSequence::CallNotify()
{
	size_t	Size = mNotifyList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (mNotifyList[i]->Frame == mFrame)
		{
			if (mNotifyList[i]->Function)
				mNotifyList[i]->Function();
		}
	}
}
