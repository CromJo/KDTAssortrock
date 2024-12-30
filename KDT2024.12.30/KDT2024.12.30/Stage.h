#pragma once

#include "GameInfo.h"

enum class ESpawnDir
{
	Up,
	Down,
	Right,
	Left
};

struct FStageInfo
{
	int			x;
	int			y;
	ESpawnDir	Dir;
};

class CStage
{
public:
	CStage();
	~CStage();

private:
	std::list<FStageInfo>	mInfoList;

	int		mCountX = 15;
	int		mCountY = 15;
	// ���� ��
	LARGE_INTEGER	mTime;
	// �ʴ� �带 ��
	LARGE_INTEGER	mSecond;
	float			mDeltaTime = 0.f;
	float			mStageTime = 0.f;

	char* mOutputBuffer;

public:
	int GetStageCountX()
	{
		return mCountX;
	}

	int GetStageCountY()
	{
		return mCountY;
	}

public:
	bool Init(const char* FileName);
	void Run();

};

