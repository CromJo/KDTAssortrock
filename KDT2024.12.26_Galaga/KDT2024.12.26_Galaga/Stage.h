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
	// ���簪
	LARGE_INTEGER mTime;
	// �ʴ� �带 ��
	LARGE_INTEGER mSecond;
	// ���� ���� (�׸��׸����)
	char* mOutputBuffer;
	// �׸��� ������ ���ھ�� Stage�� �ִ� ���� �� ������.
	int mScore = 0;

	// ����� ��
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