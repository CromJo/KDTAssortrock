#pragma once
#include "GameInfo.h"

class CMazeManager
{
private:
	class CMaze** mMazeArray = nullptr;
	int mMazeCount = 0;

public:
	bool Init();
	void Run();

	DECLARE_SINGLE(CMazeManager);
};

