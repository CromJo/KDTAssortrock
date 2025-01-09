#pragma once
#include "GameInfo.h"

class CBoard
{
private:
	CBoard() {}
	~CBoard() {}

private:
	static CBoard* Instance;

public:
	static CBoard* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new CBoard;
		}

		return Instance;
	}

private:
	char* mOutputBuffer;
	int mMapSizeX = 0;
	int mMapSizeY = 0;

public:
	bool Init(char* FileName);
	bool FileRead(const char* FileName);

	COORD mBoard;
};

