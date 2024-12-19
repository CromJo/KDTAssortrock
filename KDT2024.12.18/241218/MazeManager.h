#pragma once
#include "GameInfo.h"

class CMazeManager
{
private:
	class CMaze** mMazeArray = nullptr;
	int mMazeCount = 0;

	__int64 mScoreArray[5] = {};	// 상위 5위권 점수판
	int mScoreCount = 0;

private:
	int Menu();

public:
	bool Init();
	void Run();
	void RunScore();

	DECLARE_SINGLE(CMazeManager);
};

