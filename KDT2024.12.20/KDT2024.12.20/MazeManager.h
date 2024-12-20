#pragma once

#include "GameInfo.h"

class CMazeManager
{
private:
	class CMaze** mMazeArray = nullptr;
	int		mMazeCount = 0;

	FScore	mScoreArray[5] = {};
	int		mScoreCount = 0;

private:
	int Menu();

public:
	bool Init();
	void Run();
	void RunScore();

	DECLARE_SINGLE(CMazeManager)
};

