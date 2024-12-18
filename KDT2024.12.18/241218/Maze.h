#pragma once
#include "GameInfo.h"

class CMaze
{
public:
	CMaze();
	~CMaze();

private:
	ETileType** mMazeArray = nullptr;
	int mCountX = 0;
	int mCountY = 0;

public:
	bool Init(const char* FileName);
	void Output();
};

