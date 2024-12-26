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
	EObjectType Type;
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
	// ����� ��
	float mDeltaTime = 0.f;
	float mStageTime = 0.f;

public:
	bool Init(const char* FileName);
	void Run();

private:
	void ComputeStageInfo();
};

