#pragma once
#include "GameInfo.h"

enum class ESpawnDirect
{
	Down,
	Right,
	Left
};

struct FStageInfo
{
	int Time;
	ESpawnType Type;
	int X;
	int Y;
	ESpawnDirect Direct;
};

class CStage
{
public:
	CStage();
	~CStage();

private:
	std::list<FStageInfo> mInfoList;
	int mCountX = 15;
	int mCountY = 15;
	// 현재값
	LARGE_INTEGER mTime;
	// 초당 흐를 값
	LARGE_INTEGER mSecond;
	// 더블 버퍼 (그림그리기용)
	char* mOutputBuffer;
	// 그리기 순서상 스코어는 Stage에 있는 것이 더 안정적.
	int mScore = 0;

	// 계산할 값
	float mDeltaTime = 0.f;
	float mStageTime = 0.f;

public:
	int GetStageCountX()
	{
		return mCountX;
	}
	int GetStageCountY()
	{
		return mCountY;
	}

	void AddScore(int Score)
	{
		mScore += Score;
	}

public:
	bool Init(const char* FileName);
	void Run();

private:
	void ComputeStageInfo();
};